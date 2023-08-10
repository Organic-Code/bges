#include <bges/end_nodes/label.hpp>
#include <bges/containers/unmanaged.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>
#include <bges/window.hpp>

#include <cassert>

namespace {
constexpr int32_t pt_resolution = 100;
}

void bges::Scene::Attorney::render(Scene &scene) noexcept {
	assert(scene.m_parent != nullptr);
	scene.render();
}

void bges::Scene::Attorney::set_window(Scene &scene, class Window *window) noexcept {
	assert(scene.m_parent == nullptr || window == nullptr);
	scene.m_parent = window;
}

void bges::Scene::Attorney::mouse_move(Scene &sc, const event::MouseMove &ev) {
	sc.mouse_move(ev);
}
void bges::Scene::Attorney::mouse_press(Scene &sc, const event::MousePress &ev) {
	sc.mouse_press(ev);
}
void bges::Scene::Attorney::mouse_release(Scene &sc, const event::MouseRelease &ev) {
	sc.mouse_release(ev);
}
void bges::Scene::Attorney::mouse_scroll(Scene &sc, const event::MouseScroll &ev) {
	sc.mouse_scroll(ev);
}

std::shared_ptr<bges::Scene> bges::Scene::create() {
	std::shared_ptr<Scene> scene {new Scene};
	set_root(scene, std::make_shared<container::Unmanaged>());
	return scene;
}

const std::shared_ptr<bges::Parent> &bges::Scene::get_root() noexcept {
	return m_root;
}

void bges::Scene::set_root(const std::shared_ptr<Scene>& this_scene, std::shared_ptr<Parent> new_root) noexcept {
	assert(new_root != nullptr);
	if (this_scene->m_root) {
		Parent::Attorney::as_root_of(*this_scene->m_root, nullptr);
	}
	this_scene->m_root = std::move(new_root);
	Parent::Attorney::as_root_of(*this_scene->m_root, this_scene);
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

void bges::Scene::draw(const Rectangle &rect, const PointF &relative_to) noexcept {
	assert(m_parent);

	int rel_x = pt_resolution * rect.rect.x + static_cast<int>(pt_resolution * relative_to.x);
	int rel_y = pt_resolution * rect.rect.y + static_cast<int>(pt_resolution * relative_to.y);

	auto &ctx = Window::Attorney::get_context(*m_parent);
	ctx.draw_outlined_rectangle(&ctx, {rel_x, rel_y, pt_resolution}, {rect.rect.width, rect.rect.height},
	                            {rect.fill_color.red, rect.fill_color.green, rect.fill_color.blue, rect.fill_color.alpha},
	                            rect.rect.outline_thickness,
	                            {rect.outline_color.red, rect.outline_color.green, rect.outline_color.blue, rect.outline_color.alpha});
}

void bges::Scene::draw(const Line &line, const PointF &relative_to) noexcept {
	assert(m_parent);

	const int rel_min_x = pt_resolution * line.line.min_pos.x + static_cast<int>(pt_resolution * relative_to.x);
	const int rel_min_y = pt_resolution * line.line.min_pos.y + static_cast<int>(pt_resolution * relative_to.y);
	const int rel_max_x = pt_resolution * line.line.max_pos.x + static_cast<int>(pt_resolution * relative_to.x);
	const int rel_max_y = pt_resolution * line.line.max_pos.y + static_cast<int>(pt_resolution * relative_to.y);

	auto &ctx = Window::Attorney::get_context(*m_parent);
	ctx.draw_line(&ctx, {rel_min_x, rel_min_y, pt_resolution}, {rel_max_x, rel_max_y, pt_resolution},
	              {line.color.red, line.color.green, line.color.blue, line.color.alpha});
}

void bges::Scene::draw(const Label &label, const PointF &relative_to) noexcept {
	// TODO actually (font, size, outlined, color, clipping, ...)
	assert(m_parent);

	const int rel_x = pt_resolution * label.pos.x + static_cast<int>(pt_resolution * relative_to.x);
	const int rel_y = pt_resolution * label.pos.x + static_cast<int>(pt_resolution * relative_to.y);

	auto &ctx = Window::Attorney::get_context(*m_parent);
	ctx.draw_text_line(&ctx, bges_ffi::bges_point{rel_x, rel_y, pt_resolution}, label.text.c_str());
}

void bges::Scene::render() noexcept {
	if (m_hidden) {
		return;
	}

	assert(m_parent != nullptr);
	Renderable::Attorney::render(*m_root, *this);
}

void bges::Scene::mouse_move(const event::MouseMove &ev) {
	fire_mouse_move(*this, ev);
}
void bges::Scene::mouse_press(const event::MousePress &ev) {
	fire_mouse_press(*this, ev);
}
void bges::Scene::mouse_release(const event::MouseRelease &ev) {
	fire_mouse_release(*this, ev);
}
void bges::Scene::mouse_scroll(const event::MouseScroll &ev) {
	fire_mouse_scroll(*this, ev);
}
