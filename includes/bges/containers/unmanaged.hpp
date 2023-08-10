#ifndef BGES_CONTAINERS_UNMANAGED_HPP
#define BGES_CONTAINERS_UNMANAGED_HPP

#include <bges/details/export.hpp>
#include <bges/base_classes/parent.hpp>

namespace bges::container {
class BGES_CPPEXPORT Unmanaged : public Parent {
public:
private:
	void as_root_of(std::shared_ptr<Scene> s) noexcept override;
    void set_parent(Parent* p) noexcept override;
	void vrender(Scene& scene, const PointF& relative_to) noexcept override;

	std::weak_ptr<Scene> m_current_scene{};
	std::size_t m_mouse_move_id{};
	std::size_t m_mouse_press_id{};
	std::size_t m_mouse_release_id{};
	std::size_t m_mouse_scroll_id{};
};
}

#endif //BGES_CONTAINERS_UNMANAGED_HPP
