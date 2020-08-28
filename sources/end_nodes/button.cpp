#include <bges/end_nodes/button.hpp>
#include <bges/events.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>

void bges::Button::mouse_moved(Parent &, const event::MouseMove &ev) noexcept {
	if (m_mouse_pressed) {
		if (ev.x >= p_pos.x && ev.y >= p_pos.y && ev.x <= (p_pos.x + p_size.width) && ev.y <= (p_pos.y + p_size.height)) {
            m_color         = {127, 127, 127, 255};
		} else {
            m_color = {200, 200, 200, 255};
		}
	}
}
void bges::Button::mouse_press(Parent &, const event::MousePress &ev) noexcept {
	if (ev.x >= p_pos.x && ev.y >= p_pos.y) {
		m_mouse_pressed = ev.x <= (p_pos.x + p_size.width) && ev.y <= (p_pos.y + p_size.height);
		if (m_mouse_pressed) {
			m_color = {127, 127, 127, 255};
		}
	}
}
void bges::Button::mouse_release(Parent &, const event::MouseRelease &ev) noexcept {
	if (m_mouse_pressed) {
		if (ev.x >= p_pos.x && ev.y >= p_pos.y && ev.x <= (p_pos.x + p_size.width) && ev.y <= (p_pos.y + p_size.height)) {
			fire_click(*this, {});
			m_color = {200, 200, 200, 255};
		}
		m_mouse_pressed = false;
	}
}

void bges::Button::vrender(Scene &sc) noexcept {
	Rectangle rect;
	rect.rect.x                 = p_pos.x;
	rect.rect.y                 = p_pos.y;
	rect.rect.width             = p_size.width;
	rect.rect.height            = p_size.height;
	rect.rect.outline_thickness = 0;
	rect.fill_color             = m_color;
	sc.draw(rect);
}
void bges::Button::set_parent(Parent *p) noexcept {
	if (p != nullptr) {
		assert(p_parent == nullptr);
		p_parent        = p;
		m_mouse_move_id = p_parent->on_mouse_move([this](Parent &p, const event::MouseMove &ev) {
			mouse_moved(p, ev);
		});
		m_mouse_move_id = p_parent->on_mouse_press([this](Parent &p, const event::MousePress &ev) {
			mouse_press(p, ev);
		});
		m_mouse_move_id = p_parent->on_mouse_release([this](Parent &p, const event::MouseRelease &ev) {
			mouse_release(p, ev);
		});
	}
	else {
		assert(p_parent != nullptr);
		p_parent->remove_mouse_move_listener(m_mouse_move_id);
		p_parent->remove_mouse_press_listener(m_mouse_press_id);
		p_parent->remove_mouse_release_listener(m_mouse_release_id);
		p_parent = nullptr;
	}
}