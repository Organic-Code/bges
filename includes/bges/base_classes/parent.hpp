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

	virtual ~Parent();

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
    virtual void bring_to_front(const child_type::element_type * c) noexcept;
	void bring_to_front(const child_type& c) noexcept;

	/**
	 * @param c Child to bring to the back of the render list (will be printed below others)
	 */
    virtual void bring_to_back(const child_type::element_type * c) noexcept;
    void bring_to_back(const child_type&) noexcept;

	/**
	 * This attorney allows the scene to swap root for a different parent
	 */
	struct Attorney {
		static void as_root_of(Parent& p, std::shared_ptr<Scene> scene) {
			p.as_root_of(std::move(scene));
		}
		friend class Scene;
	};

protected:
	/**
	 * Attoney enablers
	 */
	void child_set_pos(std::vector<child_type>::size_type idx, const PointF& pos) noexcept {
		Renderable::Attorney::set_pos(*p_children[idx], pos);
	}
	void child_set_scene(std::vector<child_type>::size_type idx, const std::shared_ptr<Scene>& scene) {
		Renderable::Attorney::set_scene(*p_children[idx], scene);
	}
	void child_mouse_moved_within(std::vector<child_type>::size_type idx, const event::MouseMove& ev) noexcept {
		Renderable::Attorney::mouse_moved_within(*p_children[idx], ev);
	}
	void child_mouse_exited(std::vector<child_type>::size_type idx, const event::MouseExit& ev) noexcept {
		Renderable::Attorney::mouse_exited(*p_children[idx], ev);
	}
	void child_mouse_entered(std::vector<child_type>::size_type idx, const event::MouseEnter& ev) noexcept {
		Renderable::Attorney::mouse_entered(*p_children[idx], ev);
	}
	void child_mouse_pressed(std::vector<child_type>::size_type idx, const event::MousePress& ev) noexcept {
		Renderable::Attorney::mouse_pressed(*p_children[idx], ev);
	}
	void child_mouse_release(std::vector<child_type>::size_type idx, const event::MouseRelease& ev) noexcept {
		Renderable::Attorney::mouse_release(*p_children[idx], ev);
	}

	void set_scene(const std::shared_ptr<Scene>& scene) override {
		p_scene = scene;
		for (auto i = 0u; i < p_children.size(); ++i) {
			child_set_scene(i, scene);
		}
	}


	virtual void as_root_of(std::shared_ptr<Scene>) = 0;
    void render_child(Scene&, std::vector<child_type>::size_type idx, const PointF& relative_to) noexcept;

	void mouse_moved_within(const event::MouseMove& ev) override;
	void mouse_exited(const event::MouseExit& ev) override;
	void mouse_entered(const event::MouseEnter& ev) override;
	void mouse_pressed(const event::MousePress& ev) override;
	void mouse_release(const event::MouseRelease& ev) override;

    std::vector<child_type> p_children;
	std::size_t p_hovered_child{std::numeric_limits<std::size_t>::max()};
};
} // namespace bges

#endif //BGES_BASE_CLASSES_PARENT_HPP
