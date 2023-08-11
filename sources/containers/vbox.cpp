#include <bges/containers/vbox.hpp>
#include <bges/events.hpp>
#include <bges/scene.hpp>

template <typename T>
void bges::container::VBox::add_listeners(T* parent) noexcept {
	if (parent != nullptr) {

		m_mouse_move_id = parent->on_mouse_move([this](T&, const event::MouseMove& ev) {
            if (is_in_bounds({ev.x, ev.y})) {
                if (!m_mouse_in_bounds) {
                    m_mouse_in_bounds = true;
                    fire_mouse_enter(*this, {ev.x, ev.y});
                } else {
                    fire_mouse_move(*this, ev);
                }
            } else if (m_mouse_in_bounds) {
                m_mouse_in_bounds = false;
                fire_mouse_exit(*this, {ev.x, ev.y});
            }
        });
		m_mouse_press_id = parent->on_mouse_press([this](T&, const event::MousePress& ev) {
            if (is_in_bounds({ev.x, ev.y})) {
                fire_mouse_press(*this, ev);
            }
        });
		m_mouse_release_id = parent->on_mouse_release([this](T&, const event::MouseRelease& ev) {
			if (is_in_bounds({ev.x, ev.y})) {
				fire_mouse_release(*this, ev);
			}
		});
		m_mouse_scroll_id = parent->on_mouse_scroll([this](T&, const event::MouseScroll& ev) {
            if (is_in_bounds({ev.x, ev.y})) {
                fire_mouse_scroll(*this, ev);
            }
        });
		m_mouse_enter_id = parent->on_mouse_enter([this](T&, const event::MouseEnter& ev) {
            if (is_in_bounds({ev.x, ev.y})) {
                m_mouse_in_bounds = true;
                fire_mouse_enter(*this, ev);
            } else if (m_mouse_in_bounds) {
                m_mouse_in_bounds = false;
                fire_mouse_exit(*this, {ev.x, ev.y});
            }
        });
		m_mouse_exit_id = parent->on_mouse_exit([this](T&, const event::MouseExit& ev) {
            if (m_mouse_in_bounds) {
                m_mouse_in_bounds = false;
                fire_mouse_exit(*this, ev);
            }
        });

	}
}

template <typename T>
void bges::container::VBox::remove_listeners(T* parent) noexcept {
	parent->remove_mouse_move_listener(m_mouse_move_id);
	parent->remove_mouse_press_listener(m_mouse_press_id);
	parent->remove_mouse_release_listener(m_mouse_release_id);
	parent->remove_mouse_scroll_listener(m_mouse_scroll_id);
	parent->remove_mouse_enter_listener(m_mouse_enter_id);
	parent->remove_mouse_exit_listener(m_mouse_exit_id);
}

void bges::container::VBox::set_spacing(float v) noexcept {
	m_vspacing = v;
}

void bges::container::VBox::set_margins(PointF margins) noexcept {
	m_margins = margins;
}

void bges::container::VBox::vrender(Scene &scene, const PointF& relative_to) noexcept {
	p_size.width = 0;

	auto pos = p_pos + m_margins;

	for (unsigned int i = 0 ; i < p_children.size() ; ++i) {

		set_child_pos(i, pos);
		render_child(scene, i, relative_to);
		pos.y += p_children[i]->get_displayed_size().height + m_vspacing;

		p_size.width = std::max(p_children[i]->get_displayed_size().width, p_size.width);
	}
	p_size.height = pos.y + m_margins.x - p_pos.y;
	p_size.width += m_margins.x;
}

void bges::container::VBox::set_parent(Parent* p) noexcept {
	assert(m_current_scene.lock() == nullptr && "Cannot have a parent if I am root");
	assert((p == nullptr || p_parent == nullptr) && "Remove me from the tree before adding another parent.");

	if (p_parent != nullptr) {
		remove_listeners(p_parent);
	} else if (p != nullptr) {
		add_listeners(p);
	}
	p_parent = p;
}

void bges::container::VBox::as_root_of(std::shared_ptr<Scene> sc) noexcept {
	assert(p_parent == nullptr && "Cannot be root if I have a parent");

	if (auto current = m_current_scene.lock() ; current != nullptr) {
		remove_listeners(current.get());
	}
	m_current_scene = sc;
	add_listeners(sc.get());
}

bool bges::container::VBox::is_in_bounds(bges::PointF f) const noexcept {
	return f.x >= p_pos.x && f.x <= p_pos.x + p_size.width && f.y >= p_pos.y && f.y <= p_pos.y + p_size.height;
}
void bges::container::VBox::bring_to_front(const child_type::element_type *c) noexcept {
	Parent::bring_to_back(c); // printing logic is reversed for this class
}
void bges::container::VBox::bring_to_back(const child_type::element_type *c) noexcept {
	Parent::bring_to_front(c); // printing logic is reversed for this class
}
