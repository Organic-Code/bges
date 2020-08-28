#include <bges/containers/unmanaged.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>
#include <bges/window.hpp>

#include <cassert>

void bges::Scene::Attorney::render(Scene &scene) noexcept {
	assert(scene.m_parent != nullptr);
	scene.render();
}

void bges::Scene::Attorney::set_window(Scene &scene, class Window *window) noexcept {
	assert(scene.m_parent == nullptr || window == nullptr);
	scene.m_parent = window;
}

void bges::Scene::Attorney::mouse_move(Scene& sc, const event::MouseMove& ev) {
	sc.mouse_move(ev);
}
void bges::Scene::Attorney::mouse_press(Scene& sc, const event::MousePress& ev) {
	sc.mouse_press(ev);
}
void bges::Scene::Attorney::mouse_release(Scene& sc, const event::MouseRelease& ev) {
	sc.mouse_release(ev);
}
void bges::Scene::Attorney::mouse_scroll(Scene& sc, const event::MouseScroll& ev) {
	sc.mouse_scroll(ev);
}

bges::Scene::Scene() {
	set_root(std::make_shared<container::Unmanaged>());
}

const std::shared_ptr<bges::Parent> &bges::Scene::get_root() noexcept {
	return m_root;
}

void bges::Scene::set_root(std::shared_ptr<Parent> new_root) noexcept {
	assert(new_root != nullptr);
	if (m_root) {
		Parent::Attorney::as_root_of(*m_root, nullptr);
	}
	m_root = std::move(new_root);
	Parent::Attorney::as_root_of(*m_root, this);
}

const bges::Viewport &bges::Scene::get_viewport() const noexcept {
	return m_viewport;
}

bges::Viewport &bges::Scene::viewport() noexcept {
	return m_viewport;
}

void bges::Scene::set_viewport(const Viewport &vp) noexcept {
	m_viewport = vp;
}

void bges::Scene::draw(const Rectangle &rect) noexcept {
	assert(m_parent);
	auto &ctx = Window::Attorney::get_context(*m_parent);
	ctx.draw_outlined_rectangle(&ctx, {rect.rect.x, rect.rect.y}, {rect.rect.width, rect.rect.height},
	                            {rect.fill_color.red, rect.fill_color.green, rect.fill_color.blue, rect.fill_color.alpha},
	                            rect.rect.outline_thickness,
	                            {rect.outline_color.red, rect.outline_color.green, rect.outline_color.blue, rect.outline_color.alpha});
}

void bges::Scene::draw(const Line &line) noexcept {
	assert(m_parent);
	auto &ctx = Window::Attorney::get_context(*m_parent);
	ctx.draw_line(&ctx, {line.line.min_pos.x, line.line.min_pos.y}, {line.line.max_pos.x, line.line.max_pos.y},
	              {line.color.red, line.color.green, line.color.blue, line.color.alpha});
}

void bges::Scene::render() noexcept {
	if (m_hidden) {
		return;
	}

	assert(m_parent != nullptr);
	Renderable::Attorney::render(*m_root, *this);
}

void bges::Scene::mouse_move(const event::MouseMove& ev) {
	fire_mouse_move(*this, ev);
}
void bges::Scene::mouse_press(const event::MousePress& ev) {
	fire_mouse_press(*this, ev);
}
void bges::Scene::mouse_release(const event::MouseRelease& ev) {
	fire_mouse_release(*this, ev);
}
void bges::Scene::mouse_scroll(const event::MouseScroll& ev) {
	fire_mouse_scroll(*this, ev);
}
