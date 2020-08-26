#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "common/exchanged_types.h"
#include "common/export_symbol.h"

namespace {
struct pdata {
	sf::RenderWindow window{};
};

void fix_viewport_on_win_resize(sf::RenderWindow& window, sf::Vector2u old_size) {
	sf::Vector2u new_size = window.getSize();

    auto view                = window.getView();
    float win2view_x_ratio = view.getSize().x / old_size.x;
    float win2view_y_ratio = view.getSize().y / old_size.y;

    float new_view_width  = win2view_x_ratio * new_size.x;
    float new_view_height = win2view_y_ratio * new_size.y;

    float view_x = view.getCenter().x - view.getSize().x / 2;
    float view_y = view.getCenter().y - view.getSize().y / 2;

    window.setSize(sf::Vector2u{new_size.x, new_size.y});
    window.setView(sf::View{{view_x, view_y, new_view_width, new_view_height}});
}

pdata *get_pdata(bges_ffi::backend_win_ctx *ctx) {
	return reinterpret_cast<pdata *>(ctx->data);
}

void set_error(bges_ffi::backend_win_ctx *ctx, std::string_view str) {
	delete[] ctx->error_str;
	ctx->error_str = new char[str.size() + 1];
	std::copy(str.data(), str.data() + str.size(), ctx->error_str);
	ctx->error_str[str.size()] = '\0';
}

sf::Color sfcolor(const bges_ffi::color &c) {
	return sf::Color(static_cast<sf::Uint8>(c.red * 255), static_cast<sf::Uint8>(c.green * 255), static_cast<sf::Uint8>(c.blue * 255),
	                 static_cast<sf::Uint8>(c.alpha * 255));
}

bool open_window(bges_ffi::backend_win_ctx *ctx, const char *window_name) {
	constexpr unsigned int default_width  = 800;
	constexpr unsigned int default_height = 600;

	pdata &data = *get_pdata(ctx);
	data.window.create(sf::VideoMode{default_width, default_height}, window_name);
	if (!data.window.isOpen()) {
		set_error(ctx, "failed to open window");
		return false;
	}

	data.window.setView(sf::View{{0.f, 0.f, static_cast<float>(default_width), static_cast<float>(default_height)}});
	return true;
}

void set_window_size(bges_ffi::backend_win_ctx *ctx, bges_ffi::size new_size) {
	sf::RenderWindow &window = get_pdata(ctx)->window;
	auto size                = window.getSize();
	window.setSize(sf::Vector2u{new_size.width, new_size.height});
    fix_viewport_on_win_resize(window, size);
}

bges_ffi::bges_size get_window_size(bges_ffi::backend_win_ctx *ctx) {
	auto sz = get_pdata(ctx)->window.getSize();
	return {sz.x, sz.y};
}

void close_window(bges_ffi::backend_win_ctx *ctx) {
	get_pdata(ctx)->window.close();
}

bool is_window_open(bges_ffi::backend_win_ctx *ctx) {
	return get_pdata(ctx)->window.isOpen();
}

void set_window_viewport(bges_ffi::backend_win_ctx *ctx, bges_ffi::viewport viewport) {
	get_pdata(ctx)->window.setView(sf::View{{viewport.x, viewport.y, viewport.width, viewport.height}});
}

void free_events(bges_ffi::backend_win_ctx *ctx, bges_ffi::event_list *events_out) {
	delete[] events_out->begin;
	events_out->begin = events_out->end = nullptr;
}

void retrieve_window_events(bges_ffi::backend_win_ctx *ctx, bges_ffi::event_list *events_out) {
	namespace event_type   = bges_ffi::event_type;
	namespace key          = bges_ffi::key;
	namespace mouse_button = bges_ffi::mouse_button;

    sf::RenderWindow& window = get_pdata(ctx)->window;
    auto win_sz = window.getSize();

	std::vector<sf::Event> events;
	for (sf::Event ev{}; window.pollEvent(ev);) {
		events.emplace_back(ev);
	}

	events_out->begin = new bges_ffi::event[events.size()];
	events_out->end   = events_out->begin + events.size();

	auto *ptr = events_out->begin;
	for (const auto &ev : events) {
		switch (ev.type) {
			case sf::Event::Closed:
				ptr->type = event_type::CLOSE;
				break;
			case sf::Event::Resized:
                ptr->type = event_type::RESIZE;
				ptr->window_size.width = ev.size.width;
				ptr->window_size.height = ev.size.height;
				fix_viewport_on_win_resize(window, win_sz);
				break;
			case sf::Event::LostFocus:
				ptr->type = event_type::FOCUS_LOSE;
				break;
			case sf::Event::GainedFocus:
                ptr->type = event_type::FOCUS_GAIN;
				break;
            case sf::Event::KeyReleased:
			case sf::Event::KeyPressed:
				if (ev.type == sf::Event::KeyPressed) {
					ptr->type = event_type::KEY_PRESS;
				} else {
					ptr->type = event_type::KEY_RELEASE;
				}

                ptr->key.hw_key_code = ev.key.code;
				ptr->key.key = key::UNLISTED_KEY_CODE; // unsupported
				ptr->key.is_meta_pressed = ev.key.system;
				ptr->key.is_shift_pressed = ev.key.shift;
				ptr->key.is_capslock_locked = false; // unsupported
				ptr->key.is_alt_pressed = ev.key.alt;
				ptr->key.is_ctrl_pressed = ev.key.control;
				break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
				if (ev.type == sf::Event::MouseButtonPressed) {
					ptr->type = event_type::MOUSE_PRESS;
				} else {
                    ptr->type = event_type::MOUSE_RELEASE;
				}
				switch (ev.mouseButton.button) {
					case sf::Mouse::Left:
                        ptr->mouse_button.kind = mouse_button::LEFT;
						break;
					case sf::Mouse::Right:
                        ptr->mouse_button.kind = mouse_button::RIGHT;
						break;
					case sf::Mouse::Middle:
                        ptr->mouse_button.kind = mouse_button::MIDDLE;
						break;
					case sf::Mouse::XButton1:
                        ptr->mouse_button.kind = mouse_button::PREVIOUS;
						break;
					case sf::Mouse::XButton2:
                        ptr->mouse_button.kind = mouse_button::NEXT;
						break;
					default:
						ptr->mouse_button.kind = mouse_button::UNLISTED_BUTTON_CODE;
				}
				ptr->mouse_button.pos = {ev.mouseButton.x, ev.mouseButton.y};
                break;

				// unsuported vv
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseWheelScrolled:
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;


			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickConnected:
			case sf::Event::JoystickDisconnected:
			case sf::Event::TouchBegan:
			case sf::Event::TouchMoved:
			case sf::Event::TouchEnded:
			case sf::Event::SensorChanged:
				break;
		}
	}
}

void render_window(bges_ffi::backend_win_ctx *ctx) {
	get_pdata(ctx)->window.display();
}

void clear_window(bges_ffi::backend_win_ctx *ctx) {
	get_pdata(ctx)->window.clear();
}

void draw_line(bges_ffi::backend_win_ctx *ctx, bges_ffi::point begin, bges_ffi::point end, bges_ffi::color color) {
	sf::Vertex line[] = {{{static_cast<float>(begin.x), static_cast<float>(begin.y)}, sfcolor(color)},
	                     {{static_cast<float>(end.x), static_cast<float>(end.y)}, sfcolor(color)}};
	get_pdata(ctx)->window.draw(line, std::size(line), sf::Lines);
}

void draw_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color color) {
	sf::RectangleShape rect{};
	rect.setPosition(pos.x, pos.y);
	rect.setSize(sf::Vector2f(size.width, size.height));
	rect.setFillColor(sfcolor(color));
	get_pdata(ctx)->window.draw(rect);
}

void draw_outlined_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color fill_color,
                             uint16_t outline_thickness, bges_ffi::color outline_color) {
	sf::RectangleShape rect{};
	rect.setPosition(pos.x, pos.y);
	rect.setSize(sf::Vector2f(size.width, size.height));
	rect.setOutlineThickness(outline_thickness);
	rect.setFillColor(sfcolor(fill_color));
	rect.setOutlineColor(sfcolor(outline_color));
	get_pdata(ctx)->window.draw(rect);
}
} // namespace

BGES_PUBLIC_API void bgesbe_init_ctx(bges_ffi::version front_end_version, /* out */ bges_ffi::backend_win_ctx *ctx) {
	ctx->data = new pdata;

	ctx->open                    = &open_window;
	ctx->resize                  = &set_window_size;
	ctx->close                   = &close_window;
	ctx->is_open                 = &is_window_open;
	ctx->set_viewport            = &set_window_viewport;
	ctx->retrieve_events         = &retrieve_window_events;
	ctx->free_events             = &free_events;
	ctx->render                  = &render_window;
	ctx->clear                   = &clear_window;
	ctx->draw_line               = &draw_line;
	ctx->draw_rectangle          = &draw_rectangle;
	ctx->draw_outlined_rectangle = &draw_outlined_rectangle;
}

BGES_PUBLIC_API void bgesbe_destroy_ctx(bges_ffi::version front_end_version, /* out */ bges_ffi::backend_win_ctx *ctx) {
	delete[] ctx->error_str;
	delete get_pdata(ctx);
	ctx->data = nullptr;
}
