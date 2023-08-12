#include <bges/containers/unmanaged.hpp>
#include <bges/scene.hpp>


void bges::container::Unmanaged::vrender(Scene &scene, const PointF& relative_to) noexcept {
	for (unsigned int i = 0 ; i < p_children.size() ; ++i) {
		render_child(scene, i, relative_to);
	}
}

void bges::container::Unmanaged::set_parent(Parent* p) noexcept {
	p_parent = p;
}

void bges::container::Unmanaged::as_root_of(std::shared_ptr<Scene> sc) noexcept {
}
