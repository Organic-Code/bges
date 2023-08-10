#ifndef BGES_BASE_CLASSES_PARENT_HPP
#define BGES_BASE_CLASSES_PARENT_HPP

#include <memory>
#include <vector>

#include <bges/details/export.hpp>
#include <bges/base_classes/renderable.hpp>
#include <bges/base_classes/event_publishers.hpp>

namespace bges {
/**
 * Base class for Parents, which are classes containing other GUI elements. Such classes include HBox, VBox, Pan, …
 */
class BGES_CPPEXPORT Parent: public Renderable, public event_publisher::MouseEvents<Parent> {
public:
	enum class clipping_policy { // TODO none implemented
		no_clipping,    // Children can be drawn outside of the parent’s hitbox
		clip_to_parent, // Children (or children parts) outside of the parent’s hitbox are not rendered
		scrolling,      // Add a scroll bar if children are outside of the parent’s hitbox
		distort,        // Creates a local viewport, distorting children so that they fit in the parent’s hitbox
	};

	using child_type = std::shared_ptr<Renderable>;

	/**
	 * @return The current children list
	 */
	[[nodiscard]] const std::vector<child_type> &children() const noexcept;

	/**
	 * @param c Child to add to the render list
	 */
    void add_child(child_type c);

	/**
	 * @param c Child to remove from the render list (compared by address)
	 */
    void remove_child(const child_type & c);

	/**
	 * @param c Child to bring to the front of the render list (will be printed above others)
	 */
    void bring_to_front(const child_type::element_type * c) noexcept;
	void bring_to_front(const child_type& c) noexcept;

	/**
	 * @param c Child to bring to the back of the render list (will be printed below others)
	 */
    void bring_to_back(const child_type::element_type * c) noexcept;
    void bring_to_back(const child_type&) noexcept;

	/**
	 * This attorney allows the scene to swap root for a different parent
	 */
	struct Attorney {
		static void as_root_of(Parent& p, std::shared_ptr<Scene> scene) {
			p.as_root_of(scene);
		}
		friend class Scene;
	};

protected:
	virtual void as_root_of(std::shared_ptr<Scene>) = 0;
    void render_child(Scene&, std::vector<child_type>::size_type idx, const PointF& relative_to) noexcept;
    std::vector<child_type> p_children;

};
} // namespace bges

#endif //BGES_BASE_CLASSES_PARENT_HPP
