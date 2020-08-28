#include <bges/containers/unmanaged.hpp>
#include <bges/scene.hpp>

void bges::container::Unmanaged::vrender(Scene &scene) noexcept {
	for (unsigned int i = 0 ; i < p_children.size() ; ++i) {
		render_child(scene, i);
	}
}

void bges::container::Unmanaged::set_parent(Parent* p) noexcept {
	if (p != nullptr) {

	}
}

void bges::container::Unmanaged::as_root_of(Scene* sc) noexcept {
	// TODO remove those listener when sc is set to nullptr
	if (sc != nullptr) {
		sc->on_mouse_move([this](Scene&, const event::MouseMove& ev) {
			fire_mouse_move(*this, ev);
		});
		sc->on_mouse_press([this](Scene&, const event::MousePress& ev) {
			fire_mouse_press(*this, ev);
		});
		sc->on_mouse_release([this](Scene&, const event::MouseRelease& ev) {
			fire_mouse_release(*this, ev);
		});
		sc->on_mouse_scroll([this](Scene&, const event::MouseScroll& ev) {
			fire_mouse_scroll(*this, ev);
		});
	}
}
