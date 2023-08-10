#include <bges/containers/unmanaged.hpp>
#include <bges/scene.hpp>

void bges::container::Unmanaged::vrender(Scene &scene, const PointF& relative_to) noexcept {
	for (unsigned int i = 0 ; i < p_children.size() ; ++i) {
		render_child(scene, i, relative_to);
	}
}

void bges::container::Unmanaged::set_parent(Parent* p) noexcept {
	if (p != nullptr) {

	}
}

void bges::container::Unmanaged::as_root_of(std::shared_ptr<Scene> sc) noexcept {
	if (auto current = m_current_scene.lock() ; current != nullptr) {
		current->remove_mouse_move_listener(m_mouse_move_id);
		current->remove_mouse_press_listener(m_mouse_press_id);
		current->remove_mouse_release_listener(m_mouse_release_id);
		current->remove_mouse_scroll_listener(m_mouse_scroll_id);
	}

	m_current_scene = sc;
	if (sc != nullptr) {
		m_mouse_move_id = sc->on_mouse_move([this](Scene&, const event::MouseMove& ev) {
            // TODO filtrer : s’exécute même si le curseur est sur un enfant.
			fire_mouse_move(*this, ev);
		});
		m_mouse_press_id = sc->on_mouse_press([this](Scene&, const event::MousePress& ev) {
            // TODO filtrer : s’exécute même si le curseur est sur un enfant.
			fire_mouse_press(*this, ev);
		});
		m_mouse_release_id = sc->on_mouse_release([this](Scene&, const event::MouseRelease& ev) {
			// TODO filtrer : s’exécute même si le curseur est sur un enfant.
			fire_mouse_release(*this, ev);
		});
		m_mouse_scroll_id = sc->on_mouse_scroll([this](Scene&, const event::MouseScroll& ev) {
            // TODO filtrer : s’exécute même si le curseur est sur un enfant.
			fire_mouse_scroll(*this, ev);
		});
	}
}
