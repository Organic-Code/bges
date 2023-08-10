#include <array>
#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "common/exchanged_types.h"
#include "common/export_symbol.h"

namespace {

constexpr std::array<std::uint16_t, sf::Keyboard::KeyCount> init_key_mapping() noexcept { // NOLINT(*-function-size)
	std::array<std::uint16_t, sf::Keyboard::KeyCount> array{};
	using namespace bges_ffi::key; // NOLINT(*-build-using-namespace)
	array[sf::Keyboard::A]         = A;
	array[sf::Keyboard::B]         = B;
	array[sf::Keyboard::C]         = C;
	array[sf::Keyboard::D]         = D;
	array[sf::Keyboard::E]         = E;
	array[sf::Keyboard::F]         = F;
	array[sf::Keyboard::G]         = G;
	array[sf::Keyboard::H]         = H;
	array[sf::Keyboard::I]         = I;
	array[sf::Keyboard::J]         = J;
	array[sf::Keyboard::K]         = K;
	array[sf::Keyboard::L]         = L;
	array[sf::Keyboard::M]         = M;
	array[sf::Keyboard::N]         = N;
	array[sf::Keyboard::O]         = O;
	array[sf::Keyboard::P]         = P;
	array[sf::Keyboard::Q]         = Q;
	array[sf::Keyboard::R]         = R;
	array[sf::Keyboard::S]         = S;
	array[sf::Keyboard::T]         = T;
	array[sf::Keyboard::U]         = U;
	array[sf::Keyboard::V]         = V;
	array[sf::Keyboard::W]         = W;
	array[sf::Keyboard::X]         = X;
	array[sf::Keyboard::Y]         = Y;
	array[sf::Keyboard::Z]         = Z;
	array[sf::Keyboard::Num0]      = KB_0;
	array[sf::Keyboard::Num1]      = KB_1;
	array[sf::Keyboard::Num2]      = KB_2;
	array[sf::Keyboard::Num3]      = KB_3;
	array[sf::Keyboard::Num4]      = KB_4;
	array[sf::Keyboard::Num5]      = KB_5;
	array[sf::Keyboard::Num6]      = KB_6;
	array[sf::Keyboard::Num7]      = KB_7;
	array[sf::Keyboard::Num8]      = KB_8;
	array[sf::Keyboard::Num9]      = KB_9;
	array[sf::Keyboard::Escape]    = ESCAPE;
	array[sf::Keyboard::LControl]  = LCTRL;
	array[sf::Keyboard::LShift]    = LSHIFT;
	array[sf::Keyboard::LAlt]      = LALT;
	array[sf::Keyboard::LSystem]   = LSYSTEM;
	array[sf::Keyboard::RControl]  = RCTRL;
	array[sf::Keyboard::RShift]    = RSHIFT;
	array[sf::Keyboard::RAlt]      = RALT;
	array[sf::Keyboard::RSystem]   = RSYSTEM;
	array[sf::Keyboard::Menu]      = MENU;
	array[sf::Keyboard::LBracket]  = UNLISTED_KEY_CODE;
	array[sf::Keyboard::RBracket]  = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Semicolon] = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Comma]     = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Period]    = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Quote]     = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Slash]     = SLASH;
	array[sf::Keyboard::Backslash] = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Tilde]     = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Equal]     = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Hyphen]    = UNLISTED_KEY_CODE;
	array[sf::Keyboard::Space]     = SPACE;
	array[sf::Keyboard::Enter]     = ENTER;
	array[sf::Keyboard::Backspace] = BACKSPACE;
	array[sf::Keyboard::Tab]       = TAB;
	array[sf::Keyboard::PageUp]    = PAGE_UP;
	array[sf::Keyboard::PageDown]  = PAGE_DOWN;
	array[sf::Keyboard::End]       = END;
	array[sf::Keyboard::Home]      = META;
	array[sf::Keyboard::Insert]    = INSERT;
	array[sf::Keyboard::Delete]    = DEL;
	array[sf::Keyboard::Add]       = PLUS;
	array[sf::Keyboard::Subtract]  = MINUS;
	array[sf::Keyboard::Multiply]  = STAR;
	array[sf::Keyboard::Divide]    = SLASH;
	array[sf::Keyboard::Left]      = LEFT;
	array[sf::Keyboard::Right]     = RIGHT;
	array[sf::Keyboard::Up]        = UP;
	array[sf::Keyboard::Down]      = DOWN;
	array[sf::Keyboard::Numpad0]   = NUM_0;
	array[sf::Keyboard::Numpad1]   = NUM_1;
	array[sf::Keyboard::Numpad2]   = NUM_2;
	array[sf::Keyboard::Numpad3]   = NUM_3;
	array[sf::Keyboard::Numpad4]   = NUM_4;
	array[sf::Keyboard::Numpad5]   = NUM_5;
	array[sf::Keyboard::Numpad6]   = NUM_6;
	array[sf::Keyboard::Numpad7]   = NUM_7;
	array[sf::Keyboard::Numpad8]   = NUM_8;
	array[sf::Keyboard::Numpad9]   = NUM_9;
	array[sf::Keyboard::F1]        = F1;
	array[sf::Keyboard::F2]        = F2;
	array[sf::Keyboard::F3]        = F3;
	array[sf::Keyboard::F4]        = F4;
	array[sf::Keyboard::F5]        = F5;
	array[sf::Keyboard::F6]        = F6;
	array[sf::Keyboard::F7]        = F7;
	array[sf::Keyboard::F8]        = F8;
	array[sf::Keyboard::F9]        = F9;
	array[sf::Keyboard::F10]       = F10;
	array[sf::Keyboard::F11]       = F11;
	array[sf::Keyboard::F12]       = F12;
	array[sf::Keyboard::F13]       = F13;
	array[sf::Keyboard::F14]       = F14;
	array[sf::Keyboard::F15]       = F15;
	array[sf::Keyboard::Pause]     = PAUSE;
	return array;
}

constexpr std::array sf2bges_key_code = init_key_mapping();

struct pdata {
	sf::RenderWindow window{};
	sf::Vector2u last_rendered_sz{};
	sf::Font font{};
};

std::int32_t x_from_pt(bges_ffi::point ptx) {
	return ptx.x / ptx.resolution;
}

std::int32_t y_from_pt(bges_ffi::point ptx) {
	return ptx.y / ptx.resolution;
}

float fx_from_pt(bges_ffi::point ptx) {
	return static_cast<float>(ptx.x) / static_cast<float>(ptx.resolution);
}

float fy_from_pt(bges_ffi::point ptx) {
	return static_cast<float>(ptx.y) / static_cast<float>(ptx.resolution);
}

void fix_viewport_on_win_resize(sf::RenderWindow &window, sf::Vector2u old_size) {
	sf::Vector2u new_size = window.getSize();
	if (new_size == old_size) {
		return;
	}

	auto delta = static_cast<sf::Vector2i>(new_size - old_size);
	auto view  = window.getView();
	sf::FloatRect computed_view{view.getCenter().x - view.getSize().x / 2.f, view.getCenter().y - view.getSize().y / 2.f,
	                            view.getSize().x + delta.x * view.getSize().x / old_size.x,
	                            view.getSize().y + delta.y * view.getSize().y / old_size.y};
	window.setView(sf::View{computed_view});
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

uint8_t open_window(bges_ffi::backend_win_ctx *ctx, const char *window_name) {
	constexpr unsigned int default_width  = 800; // fixme
	constexpr unsigned int default_height = 600; // fixme

	pdata &data = *get_pdata(ctx);
	data.window.create(sf::VideoMode{default_width, default_height}, window_name);
	if (!data.window.isOpen()) {
		set_error(ctx, "failed to open window");
		return 0;
	}

	data.window.setView(sf::View{{0.f, 0.f, static_cast<float>(default_width), static_cast<float>(default_height)}});
	return 1;
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

void move(bges_ffi::backend_win_ctx *ctx, bges_ffi::point delta) {
	auto pos = get_pdata(ctx)->window.getPosition();
	get_pdata(ctx)->window.setPosition({pos.x + x_from_pt(delta), pos.y + y_from_pt(delta)});
}

void get_position(bges_ffi::backend_win_ctx *ctx, bges_ffi::point *out) {
	auto pos        = get_pdata(ctx)->window.getPosition();
	out->x          = pos.x;
	out->y          = pos.y;
	out->resolution = 1;
}

void set_position(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos) {
	get_pdata(ctx)->window.setPosition({x_from_pt(pos), y_from_pt(pos)});
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

	sf::RenderWindow &window = get_pdata(ctx)->window;

	std::vector<sf::Event> events;
	for (sf::Event ev{}; window.pollEvent(ev);) {
		events.emplace_back(ev);
	}

	if (events.empty()) {
		events_out->begin = events_out->end = nullptr;
		return;
	}

	events_out->begin = new bges_ffi::event[events.size()];
	events_out->end   = events_out->begin + events.size();
	bool dirty_viewport{false};

	for (std::size_t i = 0; i < events.size(); ++i) {
		const sf::Event &ev  = events[i];
		bges_ffi::event &ptr = events_out->begin[i];

		switch (ev.type) {
			case sf::Event::Closed:
				ptr.type = event_type::CLOSE;
				break;
			case sf::Event::Resized:
				ptr.type               = event_type::RESIZE;
				ptr.window_size.width  = ev.size.width;
				ptr.window_size.height = ev.size.height;
				dirty_viewport         = true;
				break;
			case sf::Event::LostFocus:
				ptr.type = event_type::FOCUS_LOSE;
				break;
			case sf::Event::GainedFocus:
				ptr.type = event_type::FOCUS_GAIN;
				break;
			case sf::Event::KeyReleased:
			case sf::Event::KeyPressed:
				if (ev.type == sf::Event::KeyPressed) {
					ptr.type = event_type::KEY_PRESS;
				}
				else {
					ptr.type = event_type::KEY_RELEASE;
				}

				ptr.key.hw_key_code = ev.key.code;
				if (ev.key.code == -1) {
					ptr.key.key = key::UNLISTED_KEY_CODE;
				}
				else {
					ptr.key.key = sf2bges_key_code[ev.key.code];
				}
				ptr.key.is_meta_pressed    = ev.key.system;
				ptr.key.is_shift_pressed   = ev.key.shift;
				ptr.key.is_capslock_locked = false; // unsupported
				ptr.key.is_alt_pressed     = ev.key.alt;
				ptr.key.is_ctrl_pressed    = ev.key.control;
				break;
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				if (ev.type == sf::Event::MouseButtonPressed) {
					ptr.type = event_type::MOUSE_PRESS;
				}
				else {
					ptr.type = event_type::MOUSE_RELEASE;
				}
				switch (ev.mouseButton.button) {
					case sf::Mouse::Left:
						ptr.mouse_button.kind = mouse_button::LEFT;
						break;
					case sf::Mouse::Right:
						ptr.mouse_button.kind = mouse_button::RIGHT;
						break;
					case sf::Mouse::Middle:
						ptr.mouse_button.kind = mouse_button::MIDDLE;
						break;
					case sf::Mouse::XButton1:
						ptr.mouse_button.kind = mouse_button::PREVIOUS;
						break;
					case sf::Mouse::XButton2:
						ptr.mouse_button.kind = mouse_button::NEXT;
						break;
					default:
						ptr.mouse_button.kind = mouse_button::UNLISTED_BUTTON_CODE;
				}
				ptr.mouse_button.pos = {ev.mouseButton.x, ev.mouseButton.y, 1};
				break;

			case sf::Event::MouseWheelScrolled:
				ptr.type                           = event_type::MOUSE_SCROLL;
				ptr.mouse_scroll.delta             = static_cast<std::uint8_t>(std::abs(ev.mouseWheelScroll.delta));
				ptr.mouse_scroll.wheel_id          = 0;
				ptr.mouse_scroll.horizontal_scroll = ev.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel;
				ptr.mouse_scroll.upwards           = ev.mouseWheelScroll.delta > 0;
				ptr.mouse_scroll.pos.x             = ev.mouseWheelScroll.x;
				ptr.mouse_scroll.pos.y             = ev.mouseWheelScroll.y;
				break;
			case sf::Event::MouseMoved:
				ptr.type                      = event_type::MOUSE_MOVE;
				ptr.mouse_move.pos.x          = ev.mouseMove.x;
				ptr.mouse_move.pos.y          = ev.mouseMove.y;
				ptr.mouse_move.pos.resolution = 1;
				break;

				// unsuported vv
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
			case sf::Event::TextEntered:
			case sf::Event::Count:
				break;
		}
	}
	if (dirty_viewport) {
		fix_viewport_on_win_resize(window, get_pdata(ctx)->last_rendered_sz);
	}
}

void render_window(bges_ffi::backend_win_ctx *ctx) {
	get_pdata(ctx)->last_rendered_sz = get_pdata(ctx)->window.getSize();
	get_pdata(ctx)->window.display();
}

void clear_window(bges_ffi::backend_win_ctx *ctx) {
	get_pdata(ctx)->window.clear();
}

void draw_line(bges_ffi::backend_win_ctx *ctx, bges_ffi::point begin, bges_ffi::point end, bges_ffi::color color) {
	sf::Vertex line[] = {{{fx_from_pt(begin), fy_from_pt(begin)}, sfcolor(color)},
	                     {{fx_from_pt(end), fy_from_pt(end)}, sfcolor(color)}};
	get_pdata(ctx)->window.draw(line, std::size(line), sf::Lines);
}

void draw_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color color) {
	sf::RectangleShape rect{};
	rect.setPosition(fx_from_pt(pos), fy_from_pt(pos));
	rect.setSize(sf::Vector2f(size.width, size.height));
	rect.setFillColor(sfcolor(color));
	get_pdata(ctx)->window.draw(rect);
}

void draw_outlined_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color fill_color,
                             uint16_t outline_thickness, bges_ffi::color outline_color) {
	sf::RectangleShape rect{};
	rect.setPosition(fx_from_pt(pos), fy_from_pt(pos));
	rect.setSize(sf::Vector2f(size.width, size.height));
	rect.setOutlineThickness(outline_thickness);
	rect.setFillColor(sfcolor(fill_color));
	rect.setOutlineColor(sfcolor(outline_color));
	get_pdata(ctx)->window.draw(rect);
}

void draw_text_line(bges_ffi::bges_backend_win_ctx *ctx, bges_ffi::bges_point coord, const char *text) {
	// TODO: proper impl
	sf::Text stext;
	stext.setString(text);
	stext.setFont(get_pdata(ctx)->font);
	stext.setCharacterSize(24);
	stext.setFillColor(sf::Color::Blue);
	stext.setPosition(fx_from_pt(coord), fy_from_pt(coord));

	get_pdata(ctx)->window.draw(stext);
}
const char *draw_text_lenlim(bges_ffi::bges_backend_win_ctx *ctx, bges_ffi::bges_point coord, const char *text, uint32_t px_len) {
	// TODO
	return text;
}
uint32_t text_px_size(bges_ffi::bges_backend_win_ctx *ctx, const char *text) {
	sf::Text stext;
	stext.setFont(get_pdata(ctx)->font);
	stext.setCharacterSize(24);

	auto bounds = stext.getLocalBounds();
	return static_cast<uint32_t>(bounds.getSize().x);
} // TODO: proper impl
} // namespace

BGES_PUBLIC_API void bgesbe_init_ctx(bges_ffi::version /*front_end_version*/, /* out */ bges_ffi::backend_win_ctx *ctx) {
	ctx->data = new pdata;

	ctx->open                    = &open_window;
	ctx->resize                  = &set_window_size;
	ctx->move                    = &move;
	ctx->get_position            = &get_position;
	ctx->set_position            = &set_position;
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

	if (get_pdata(ctx)->font.loadFromFile("Helvetica.ttf")) {
		ctx->draw_text_line   = &draw_text_line;
		ctx->draw_text_lenlim = &draw_text_lenlim;
		ctx->text_px_size     = &text_px_size;
	}
}

BGES_PUBLIC_API void bgesbe_destroy_ctx(bges_ffi::version /*front_end_version*/, /* out */ bges_ffi::backend_win_ctx *ctx) {
	delete[] ctx->error_str;
	delete get_pdata(ctx);
	ctx->data = nullptr;
}
