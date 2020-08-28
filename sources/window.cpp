#include <cassert>
#include <memory>

#include <bges/events.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>
#include <bges/viewport.hpp>
#include <bges/window.hpp>

#include "backend_context.hpp"
#include "utils.hpp"

static_assert(bges_ffi::mouse_button::LEFT == static_cast<int>(bges::MouseButton::left));
static_assert(bges_ffi::mouse_button::RIGHT == static_cast<int>(bges::MouseButton::right));
static_assert(bges_ffi::mouse_button::MIDDLE == static_cast<int>(bges::MouseButton::middle));
static_assert(bges_ffi::mouse_button::PREVIOUS == static_cast<int>(bges::MouseButton::prev));
static_assert(bges_ffi::mouse_button::NEXT == static_cast<int>(bges::MouseButton::next));
static_assert(bges_ffi::mouse_button::UNLISTED_BUTTON_CODE == static_cast<int>(bges::MouseButton::unlisted));

static_assert(bges_ffi::key::KB_0 == static_cast<unsigned int>(bges::Key::keyboard0));
static_assert(bges_ffi::key::KB_1 == static_cast<unsigned int>(bges::Key::keyboard1));
static_assert(bges_ffi::key::KB_2 == static_cast<unsigned int>(bges::Key::keyboard2));
static_assert(bges_ffi::key::KB_3 == static_cast<unsigned int>(bges::Key::keyboard3));
static_assert(bges_ffi::key::KB_4 == static_cast<unsigned int>(bges::Key::keyboard4));
static_assert(bges_ffi::key::KB_5 == static_cast<unsigned int>(bges::Key::keyboard5));
static_assert(bges_ffi::key::KB_6 == static_cast<unsigned int>(bges::Key::keyboard6));
static_assert(bges_ffi::key::KB_7 == static_cast<unsigned int>(bges::Key::keyboard7));
static_assert(bges_ffi::key::KB_8 == static_cast<unsigned int>(bges::Key::keyboard8));
static_assert(bges_ffi::key::KB_9 == static_cast<unsigned int>(bges::Key::keyboard9));
static_assert(bges_ffi::key::NUM_0 == static_cast<unsigned int>(bges::Key::numpad0));
static_assert(bges_ffi::key::NUM_1 == static_cast<unsigned int>(bges::Key::numpad1));
static_assert(bges_ffi::key::NUM_2 == static_cast<unsigned int>(bges::Key::numpad2));
static_assert(bges_ffi::key::NUM_3 == static_cast<unsigned int>(bges::Key::numpad3));
static_assert(bges_ffi::key::NUM_4 == static_cast<unsigned int>(bges::Key::numpad4));
static_assert(bges_ffi::key::NUM_5 == static_cast<unsigned int>(bges::Key::numpad5));
static_assert(bges_ffi::key::NUM_6 == static_cast<unsigned int>(bges::Key::numpad6));
static_assert(bges_ffi::key::NUM_7 == static_cast<unsigned int>(bges::Key::numpad7));
static_assert(bges_ffi::key::NUM_8 == static_cast<unsigned int>(bges::Key::numpad8));
static_assert(bges_ffi::key::NUM_9 == static_cast<unsigned int>(bges::Key::numpad9));
static_assert(bges_ffi::key::NUM_DECIMAL_SEPARATOR == static_cast<unsigned int>(bges::Key::numpad_decimal_separator));
static_assert(bges_ffi::key::STAR == static_cast<unsigned int>(bges::Key::star));
static_assert(bges_ffi::key::SLASH == static_cast<unsigned int>(bges::Key::slash));
static_assert(bges_ffi::key::MINUS == static_cast<unsigned int>(bges::Key::minus));
static_assert(bges_ffi::key::PLUS == static_cast<unsigned int>(bges::Key::plus));
static_assert(bges_ffi::key::PERCENT == static_cast<unsigned int>(bges::Key::percent));
static_assert(bges_ffi::key::A == static_cast<unsigned int>(bges::Key::a));
static_assert(bges_ffi::key::B == static_cast<unsigned int>(bges::Key::b));
static_assert(bges_ffi::key::C == static_cast<unsigned int>(bges::Key::c));
static_assert(bges_ffi::key::D == static_cast<unsigned int>(bges::Key::d));
static_assert(bges_ffi::key::E == static_cast<unsigned int>(bges::Key::e));
static_assert(bges_ffi::key::F == static_cast<unsigned int>(bges::Key::f));
static_assert(bges_ffi::key::G == static_cast<unsigned int>(bges::Key::g));
static_assert(bges_ffi::key::H == static_cast<unsigned int>(bges::Key::h));
static_assert(bges_ffi::key::I == static_cast<unsigned int>(bges::Key::i));
static_assert(bges_ffi::key::J == static_cast<unsigned int>(bges::Key::j));
static_assert(bges_ffi::key::K == static_cast<unsigned int>(bges::Key::k));
static_assert(bges_ffi::key::L == static_cast<unsigned int>(bges::Key::l));
static_assert(bges_ffi::key::M == static_cast<unsigned int>(bges::Key::m));
static_assert(bges_ffi::key::N == static_cast<unsigned int>(bges::Key::n));
static_assert(bges_ffi::key::O == static_cast<unsigned int>(bges::Key::o));
static_assert(bges_ffi::key::P == static_cast<unsigned int>(bges::Key::p));
static_assert(bges_ffi::key::Q == static_cast<unsigned int>(bges::Key::q));
static_assert(bges_ffi::key::R == static_cast<unsigned int>(bges::Key::r));
static_assert(bges_ffi::key::S == static_cast<unsigned int>(bges::Key::s));
static_assert(bges_ffi::key::T == static_cast<unsigned int>(bges::Key::t));
static_assert(bges_ffi::key::U == static_cast<unsigned int>(bges::Key::u));
static_assert(bges_ffi::key::V == static_cast<unsigned int>(bges::Key::v));
static_assert(bges_ffi::key::W == static_cast<unsigned int>(bges::Key::w));
static_assert(bges_ffi::key::X == static_cast<unsigned int>(bges::Key::x));
static_assert(bges_ffi::key::Y == static_cast<unsigned int>(bges::Key::y));
static_assert(bges_ffi::key::Z == static_cast<unsigned int>(bges::Key::z));
static_assert(bges_ffi::key::F1 == static_cast<unsigned int>(bges::Key::F1));
static_assert(bges_ffi::key::F2 == static_cast<unsigned int>(bges::Key::F2));
static_assert(bges_ffi::key::F3 == static_cast<unsigned int>(bges::Key::F3));
static_assert(bges_ffi::key::F4 == static_cast<unsigned int>(bges::Key::F4));
static_assert(bges_ffi::key::F5 == static_cast<unsigned int>(bges::Key::F5));
static_assert(bges_ffi::key::F6 == static_cast<unsigned int>(bges::Key::F6));
static_assert(bges_ffi::key::F7 == static_cast<unsigned int>(bges::Key::F7));
static_assert(bges_ffi::key::F8 == static_cast<unsigned int>(bges::Key::F8));
static_assert(bges_ffi::key::F9 == static_cast<unsigned int>(bges::Key::F9));
static_assert(bges_ffi::key::F10 == static_cast<unsigned int>(bges::Key::F10));
static_assert(bges_ffi::key::F11 == static_cast<unsigned int>(bges::Key::F11));
static_assert(bges_ffi::key::F12 == static_cast<unsigned int>(bges::Key::F12));
static_assert(bges_ffi::key::F13 == static_cast<unsigned int>(bges::Key::F13));
static_assert(bges_ffi::key::F14 == static_cast<unsigned int>(bges::Key::F14));
static_assert(bges_ffi::key::F15 == static_cast<unsigned int>(bges::Key::F15));
static_assert(bges_ffi::key::SPACE == static_cast<unsigned int>(bges::Key::space));
static_assert(bges_ffi::key::ENTER == static_cast<unsigned int>(bges::Key::enter));
static_assert(bges_ffi::key::DEL == static_cast<unsigned int>(bges::Key::del));
static_assert(bges_ffi::key::BACKSPACE == static_cast<unsigned int>(bges::Key::backspace));
static_assert(bges_ffi::key::UP == static_cast<unsigned int>(bges::Key::up));
static_assert(bges_ffi::key::DOWN == static_cast<unsigned int>(bges::Key::down));
static_assert(bges_ffi::key::LEFT == static_cast<unsigned int>(bges::Key::left));
static_assert(bges_ffi::key::RIGHT == static_cast<unsigned int>(bges::Key::right));
static_assert(bges_ffi::key::PAGE_UP == static_cast<unsigned int>(bges::Key::page_up));
static_assert(bges_ffi::key::PAGE_DOWN == static_cast<unsigned int>(bges::Key::page_down));
static_assert(bges_ffi::key::TAB == static_cast<unsigned int>(bges::Key::tab));
static_assert(bges_ffi::key::END == static_cast<unsigned int>(bges::Key::end));
static_assert(bges_ffi::key::ESCAPE == static_cast<unsigned int>(bges::Key::escape));
static_assert(bges_ffi::key::INSERT == static_cast<unsigned int>(bges::Key::insert));
static_assert(bges_ffi::key::PAUSE == static_cast<unsigned int>(bges::Key::pause));
static_assert(bges_ffi::key::PLAYPAUSE == static_cast<unsigned int>(bges::Key::playpause));
static_assert(bges_ffi::key::PLAY == static_cast<unsigned int>(bges::Key::play));
static_assert(bges_ffi::key::RCTRL == static_cast<unsigned int>(bges::Key::right_ctrl));
static_assert(bges_ffi::key::LCTRL == static_cast<unsigned int>(bges::Key::left_ctrl));
static_assert(bges_ffi::key::RCAPS == static_cast<unsigned int>(bges::Key::right_caps));
static_assert(bges_ffi::key::LCAPS == static_cast<unsigned int>(bges::Key::left_caps));
static_assert(bges_ffi::key::META == static_cast<unsigned int>(bges::Key::meta));
static_assert(bges_ffi::key::UNLISTED_KEY_CODE == static_cast<unsigned int>(bges::Key::unlisted));

bges::Window::backend_ctx_ptr_t::~backend_ctx_ptr_t() = default;

bges::Window::Window() = default;

bges::Window::~Window() = default;

bool bges::Window::open(const char *name) noexcept {
#if BGES_STATIC_BACKEND == 1
	std::optional<bges::backend::Context> ctx = backend::init();
#else
	// FIXME
	std::string dll_path = std::filesystem::current_path().generic_string() + "/";
	if (std::filesystem::is_regular_file("libbges_sfml-backenddbg.so")) {
		dll_path += "libbges_sfml-backenddbg.so";
	}
	else if (std::filesystem::is_regular_file("bges_sfml-backenddbg.dll")) {
		dll_path += "bges_sfml-backenddbg.dll";
	}
	else if (std::filesystem::is_regular_file("libbges_sfml-backend.so")) {
		dll_path += "libbges_sfml-backend.so";
	}
	else if (std::filesystem::is_regular_file("bges_sfml-backend.dll")) {
		dll_path += "bges_sfml-backend.dll";
	}
	else {
		return false;
	}
	std::optional<bges::backend::Context> ctx = backend::init(dll_path);
#endif
	if (!ctx) {
		return false;
	}
	m_ctx.std::unique_ptr<backend::Context>::operator=(std::make_unique<backend::Context>(std::move(*ctx)));

	return m_ctx->open(m_ctx.get(), name);
}

bool bges::Window::open(const char *name, unsigned int width, unsigned int height) noexcept {
	if (open(name)) {
		set_size(width, height);
		return true;
	}
	return false;
}
void bges::Window::set_viewport(const Viewport &vp) {
	auto tl = vp.get_top_left();
	auto sz = vp.get_size();
	m_ctx->set_viewport(m_ctx.get(), bges_ffi::viewport{tl.x, tl.y, sz.width, sz.height});
}

void bges::Window::set_size(unsigned int width, unsigned int height) noexcept {
	assert(m_ctx != nullptr);
	assert(is_open());
	m_ctx->resize(m_ctx.get(), {width, height});
}

void bges::Window::close() noexcept {
	assert(m_ctx != nullptr);
	assert(is_open());
	m_ctx->close(m_ctx.get());
}

bool bges::Window::is_open() const noexcept {
	assert(m_ctx != nullptr);
	return m_ctx->is_open(m_ctx.get());
}

void bges::Window::clear() noexcept {
	assert(m_ctx != nullptr);
	m_ctx->clear(m_ctx.get());
}

void bges::Window::render() noexcept {
	assert(m_ctx != nullptr);
	for (auto &scene : m_scenes) {
		Scene::Attorney::render(*scene);
	}
	m_ctx->render(m_ctx.get());

	bges_ffi::event_list events{};
	events.begin = events.end = nullptr;
	auto deleter              = [this](bges_ffi::event_list *el) {
        m_ctx->free_events(m_ctx.get(), el);
	};
	std::unique_ptr<bges_ffi::event_list, decltype(deleter)> events_ptr(&events, std::move(deleter));

	m_ctx->retrieve_events(m_ctx.get(), &events);

	for (auto it = events.begin; it != events.end; ++it) {
		switch (it->type) {
			case bges_ffi::event_type::KEY_PRESS:
				fire_key_press(*this, bges::event::KeyPress{it->key.hw_key_code, static_cast<bges::Key>(it->key.key),
				                                            it->key.is_meta_pressed, it->key.is_shift_pressed, it->key.is_capslock_locked,
				                                            it->key.is_alt_pressed, it->key.is_ctrl_pressed});
				break;
			case bges_ffi::event_type::KEY_RELEASE:
				fire_key_release(*this,
				                 bges::event::KeyRelease{it->key.hw_key_code, static_cast<bges::Key>(it->key.key), it->key.is_meta_pressed,
				                                         it->key.is_shift_pressed, it->key.is_capslock_locked, it->key.is_alt_pressed,
				                                         it->key.is_ctrl_pressed});
				break;
			case bges_ffi::event_type::MOUSE_PRESS: {
				bges::event::MousePress ev{static_cast<float>(it->mouse_button.pos.x), static_cast<float>(it->mouse_button.pos.y),
				                           static_cast<bges::MouseButton>(it->mouse_button.kind), it->mouse_button.hw_btn_code};
				fire_mouse_press(*this, ev);
				Scene::Attorney::mouse_press(*m_scenes[0], ev); // TODO
				break;
			}
			case bges_ffi::event_type::MOUSE_RELEASE: {
				bges::event::MouseRelease ev{static_cast<float>(it->mouse_button.pos.x), static_cast<float>(it->mouse_button.pos.y),
				                             static_cast<bges::MouseButton>(it->mouse_button.kind), it->mouse_button.hw_btn_code};
				fire_mouse_release(*this, ev);
				Scene::Attorney::mouse_release(*m_scenes[0], ev); // TODO
				break;
			}
			case bges_ffi::event_type::MOUSE_MOVE: {
				bges::event::MouseMove ev{static_cast<float>(it->mouse_move.pos.x), static_cast<float>(it->mouse_move.pos.y)};
				fire_mouse_move(*this, ev);
				Scene::Attorney::mouse_move(*m_scenes[0], ev); // TODO
				break;
			}
			case bges_ffi::event_type::MOUSE_SCROLL: {
				bges::event::MouseScroll ev{};
				if (it->mouse_scroll.horizontal_scroll) {
					ev = {static_cast<float>(it->mouse_scroll.pos.x), static_cast<float>(it->mouse_scroll.pos.y), it->mouse_scroll.delta,
					      it->mouse_scroll.wheel_id, it->mouse_scroll.upwards ? ScrollDirection::left : ScrollDirection::right};
				}
				else {
					ev = {static_cast<float>(it->mouse_scroll.pos.x), static_cast<float>(it->mouse_scroll.pos.y), it->mouse_scroll.delta,
					      it->mouse_scroll.wheel_id, it->mouse_scroll.upwards ? ScrollDirection::up : ScrollDirection::down};
				}
				fire_mouse_scroll(*this, ev);
				Scene::Attorney::mouse_scroll(*m_scenes[0], ev); // TODO
			} break;
			case bges_ffi::event_type::RESIZE:
				fire_resize(*this, bges::event::Resize{it->window_size.width, it->window_size.height});
				break;
			case bges_ffi::event_type::FOCUS_GAIN:
				fire_focus_gain(*this, bges::event::FocusGain{});
				break;
			case bges_ffi::event_type::FOCUS_LOSE:
				[[fallthrough]];
			case bges_ffi::event_type::MINIMIZE:
				fire_focus_lose(*this, bges::event::FocusLose{});
				break;
			case bges_ffi::event_type::CLOSE:
				fire_close_request(*this, bges::event::CloseRequest{});
				break;
			default:
				// TODO log error
				break;
		}
	}
}

std::vector<bges::Scene>::size_type bges::Window::scene_count() const noexcept {
	return m_scenes.size();
}

bges::Scene &bges::Window::get_scene(std::vector<Scene>::size_type idx) noexcept {
	assert(idx < m_scenes.size());
	return *m_scenes[idx];
}

const bges::Scene &bges::Window::get_scene(std::vector<Scene>::size_type idx) const noexcept {
	assert(idx < m_scenes.size());
	return *m_scenes[idx];
}

void bges::Window::add_scene(std::shared_ptr<Scene> scene) {
	Scene::Attorney::set_window(*scene, this);
	m_scenes.emplace_back(std::move(scene));
}

void bges::Window::show_scene(std::vector<Scene>::size_type idx) noexcept {
	hide_all_scenes();
	unhide_scene(idx);
}

void bges::Window::unhide_scene(std::vector<Scene>::size_type idx) noexcept {
	m_scenes[idx]->un_hide();
}

void bges::Window::hide_all_scenes() noexcept {
	for (const auto &scene : m_scenes) {
		scene->hide();
	}
}
