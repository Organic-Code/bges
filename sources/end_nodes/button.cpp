#include <bges/end_nodes/label.hpp>
#include <bges/end_nodes/button.hpp>
#include <bges/events.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>

namespace {
constexpr bges::IColor hover_color   = {127, 127, 127, 255};
constexpr bges::IColor pressed_color = {240, 240, 240, 255};
constexpr bges::IColor clicked_color = {100, 100, 200, 255};
constexpr bges::IColor canceled_color = {200, 100, 100, 255};
constexpr bges::IColor default_color = {200, 200, 200, 255};
} // namespace

void bges::Button::mouse_exited(const event::MouseExit& ev) {
	if (!m_mouse_pressed) {
		m_state = State::base;
	}
}

void bges::Button::mouse_entered(const event::MouseEnter& ev) {
	if (!m_mouse_pressed) {
		m_state = State::hovered;
	}
}

void bges::Button::mouse_pressed(const event::MousePress &ev) {
	if (ev.x >= p_pos.x && ev.y >= p_pos.y) {
		m_mouse_pressed = ev.x <= (p_pos.x + p_size.width) && ev.y <= (p_pos.y + p_size.height);
		if (m_mouse_pressed) {
			m_state = State::pressed;
		}
	}
}

void bges::Button::mouse_release(const event::MouseRelease &ev) {
	if (m_mouse_pressed) {
		if (ev.x >= p_pos.x && ev.y >= p_pos.y && ev.x <= (p_pos.x + p_size.width) && ev.y <= (p_pos.y + p_size.height)) {
			fire_click(*this, {ev.button});
			m_state = State::clicked;
		}
		else {
			m_state = State::canceled;
		}
		m_mouse_pressed = false;
	}
	m_mouse_released = false;
}

void bges::Button::vrender(Scene &sc, const PointF &relative_to) noexcept {
	if (m_mouse_pressed && m_mouse_released) { /* If mouse was pressed on the button (info from parent), but released outside of it (info from scene)*/
		m_mouse_pressed = false;
		m_mouse_released = false;
		m_state = State::canceled;
	}

	p_skin->render(sc, {p_pos, relative_to, p_size, m_state, m_text});
}

void bges::Button::set_parent(Parent *p) noexcept {
}

void bges::Button::set_scene(const std::shared_ptr<Scene>& scene) {
	if (scene != nullptr) {
		m_mouse_release_id = scene->on_mouse_release([this](Scene &, const event::MouseRelease &ev) {
			if (m_mouse_pressed) {
				m_mouse_released = true;
			}
		});

	} else if (auto my_scene = p_scene.lock() ; my_scene != nullptr) {
		my_scene->remove_mouse_release_listener(m_mouse_release_id);
	}
    p_scene = scene;
}

void bges::Button::default_skin::render(bges::Scene &sce, const bges::Button::SkinData &data) noexcept {

	Rectangle rect;
	switch (data.state) {
		case State::hovered:
			rect.fill_color = hover_color;
			break;
		case State::pressed:
			rect.fill_color = pressed_color;
			break;
		case State::clicked:
			rect.fill_color = clicked_color;
			break;
		case State::canceled:
			rect.fill_color = canceled_color;
			break;
		case State::base:
			rect.fill_color = default_color;
			break;
	}

	rect.rect.x                 = static_cast<int>(data.pos.x);
	rect.rect.y                 = static_cast<int>(data.pos.y);
	rect.rect.width             = static_cast<unsigned int>(data.size.width);
	rect.rect.height            = static_cast<unsigned int>(data.size.height);
	rect.rect.outline_thickness = 0;
	sce.draw(rect, data.relative);

	if (m_label.text != data.text) {
		m_label.text = data.text;
	}

	Label::Attorney::render(m_label, sce, data.relative + data.pos);
}
