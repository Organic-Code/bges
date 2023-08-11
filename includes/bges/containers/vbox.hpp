#ifndef BGES_CONTAINERS_VBOX_HPP
#define BGES_CONTAINERS_VBOX_HPP

#include <bges/details/export.hpp>
#include <bges/base_classes/parent.hpp>
#include <bges/geometry.hpp>

namespace bges::container {

class BGES_CPPEXPORT VBox : public Parent {
public:
	/**
	 * Sets the vertical spacing between each element
	 * @param v spacing to apply
	 */
	void set_spacing(float v) noexcept;

	/**
	 * Sets the margins (blank space at the left and at the top of the vbox elements)
	 */
	void set_margins(PointF margins) noexcept;

	void bring_to_front(const child_type::element_type * c) noexcept override;
	void bring_to_back(const child_type::element_type * c) noexcept override;

private:
	void as_root_of(std::shared_ptr<Scene> s) noexcept override;
	void set_parent(Parent* p) noexcept override;
	void vrender(Scene& scene, const PointF& relative_to) noexcept override;

	/**
	 * @return True if f is within the vbox
	 */
	[[nodiscard]] bool is_in_bounds(PointF f) const noexcept;

	template <typename T>
	void add_listeners(T* parent) noexcept;
	template <typename T>
	void remove_listeners(T* parent) noexcept;

	std::weak_ptr<Scene> m_current_scene{};
	float m_vspacing{0.f};
	PointF m_margins{};

	std::size_t m_mouse_move_id{};
	std::size_t m_mouse_press_id{};
	std::size_t m_mouse_release_id{};
	std::size_t m_mouse_scroll_id{};
	std::size_t m_mouse_enter_id{};
	std::size_t m_mouse_exit_id{};

	bool m_mouse_in_bounds{false};
};
}

#endif //BGES_CONTAINERS_VBOX_HPP
