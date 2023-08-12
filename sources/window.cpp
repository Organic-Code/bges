#include <cassert>
#include <memory>

#include <bges/bges.hpp>
#include <bges/events.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>
#include <bges/viewport.hpp>
#include <bges/window.hpp>

#include "backend_context.hpp"
#include "utils.hpp"

bges::Window::backend_ctx_ptr_t::~backend_ctx_ptr_t() = default;

bges::Window::Window() = default;

bges::Window::~Window() = default;

bool bges::Window::open(const char *name) noexcept {
	if (!bges::is_init()) {
		return false;
	}

	std::optional<bges::backend::Context> ctx = backend::init();
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
	auto tol = vp.get_top_left();
	auto siz = vp.get_size();
	m_ctx->set_viewport(m_ctx.get(), bges_ffi::viewport{tol.x, tol.y, siz.width, siz.height});
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
	const std::unique_ptr<bges_ffi::event_list, decltype(deleter)> events_ptr(&events, std::move(deleter));

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
				std::optional<bges::event::MouseScroll> ev;
				if (it->mouse_scroll.horizontal_scroll) {
					ev = {static_cast<float>(it->mouse_scroll.pos.x), static_cast<float>(it->mouse_scroll.pos.y), it->mouse_scroll.delta,
					      it->mouse_scroll.wheel_id, it->mouse_scroll.upwards ? ScrollDirection::left : ScrollDirection::right};
				}
				else {
					ev = {static_cast<float>(it->mouse_scroll.pos.x), static_cast<float>(it->mouse_scroll.pos.y), it->mouse_scroll.delta,
					      it->mouse_scroll.wheel_id, it->mouse_scroll.upwards ? ScrollDirection::up : ScrollDirection::down};
				}
				fire_mouse_scroll(*this, *ev);
				Scene::Attorney::mouse_scroll(*m_scenes[0], *ev); // TODO
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
