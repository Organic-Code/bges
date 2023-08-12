#ifndef BGES_BASE_CLASSES_RENDERABLE_HPP
#define BGES_BASE_CLASSES_RENDERABLE_HPP

#include <bges/details/export.hpp>
#include <bges/geometry.hpp>

#include <cassert>
#include <memory>

namespace bges {
class Scene;
class Parent;
namespace event {
struct MouseMove;
struct MousePress;
struct MouseRelease;
struct MouseScroll;
struct MouseEnter;
struct MouseExit;
}

/**
 * The renderable class is the base class for all GUI elements that ought to be rendered to the screen, including parents that render their children
 */
class BGES_CPPEXPORT Renderable {
public:
	Renderable() noexcept = default;
	Renderable(const Renderable&) noexcept = default;
	Renderable(Renderable&&) noexcept = default;
	Renderable& operator=(const Renderable&) noexcept = default;
	Renderable& operator=(Renderable&&) noexcept = default;
    virtual ~Renderable() = default;

	/**
	 * Disables rendering
	 * @see Renderable::un_hide
	 * @see Renderable::is_hidden
	 */
    void hide() noexcept;

	/**
	 * Re enables rendering
	 * @see Renderable::hide
	 * @see Renderable::is_hidden
	 */
    void un_hide() noexcept;

	/**
	 * @return true if this renderable is currently ignoring render calls
	 * @see Renderable::hide
	 * @see Renderable::un_hide
	 */
	[[nodiscard]] bool is_hidden() const noexcept;

	/**
	 * @return The current px size of the renderable. May not fully include children, depending on Parent::clipping_policy
	 */
	[[nodiscard]] SizeF get_displayed_size() const noexcept;

	/**
	 * Sets the preferred size of this element, which is the size it will take if possible
	 * @see Renderable::set_size
	 */
    void set_preferred_size(SizeF) noexcept;

	/**
	 * Sets the minimum size of this element
	 * @see Renderable::set_size
	 */
    void set_min_size(SizeF) noexcept;

	/**
	 * Sets the maximum size of this element
	 * @see Renderable::set_size
	 */
    void set_max_size(SizeF) noexcept;

	/**
	 * Sets all min, max, and pref size of this element
	 * @see Renderable::set_preffered_size
	 * @see Renderable::set_min_size
	 * @see Renderable::set_max_size
	 */
    void set_size(SizeF) noexcept;

    [[nodiscard]] SizeF get_preferred_size() noexcept;
    [[nodiscard]] SizeF get_min_size() noexcept;
    [[nodiscard]] SizeF get_max_size() noexcept;

	/**
	 * @return The current position of this element, relative to its parent
	 */
	[[nodiscard]] PointF get_pos() const noexcept;

    void to_front() noexcept;
    void to_back() noexcept;

	bool is_within(const PointF& point) const noexcept {
		return point.x >= p_pos.x && point.x <= p_pos.x + p_size.width && point.y >= p_pos.y && point.y <= p_pos.y + p_size.height;
	}

	class Attorney {
		static void render(Renderable& r, Scene& w, const PointF& relative_to = PointF{0.f,0.f}) noexcept {
			r.render(w, relative_to);
		}
		static void set_parent(Renderable& r, Parent* p) noexcept {
			r.set_parent(p);
		}
		static void set_pos(Renderable& r, PointF p) noexcept {
			r.set_pos(p);
		}
		static void set_scene(Renderable& r, const std::shared_ptr<Scene>& scene) noexcept {
			r.set_scene(scene);
		}

		static void mouse_moved_within(Renderable& r, const event::MouseMove& ev) {
			r.mouse_moved(ev);
		}
		static void mouse_exited(Renderable& r, const event::MouseExit& ev) {
			r.mouse_exited(ev);
		}
		static void mouse_entered(Renderable& r, const event::MouseEnter& ev) {
			r.mouse_entered(ev);
		}
		static void mouse_pressed(Renderable& r, const event::MousePress& ev) {
			r.mouse_pressed(ev);
		}
		static void mouse_release(Renderable& r, const event::MouseRelease& ev) {
			r.mouse_release(ev);
		}

		friend class Scene;
		friend class Parent;
		friend class Button; // todo : ne pas ajouter le bouton juste comme ça (sert actuellement pour faire le rendu du label)
	};

protected:
	virtual void vrender(Scene&, const PointF& relative_to) noexcept = 0;
	virtual void set_parent(Parent*) noexcept;

	virtual void set_pos(PointF p) noexcept;

	virtual void set_scene(const std::shared_ptr<Scene>& scene) {
		p_scene = scene;
	}

	// methods called by parents on their children, whenever the corresponding action is done within their bound.
	virtual void mouse_moved(const event::MouseMove&) {};
	virtual void mouse_exited(const event::MouseExit&) {};
	virtual void mouse_entered(const event::MouseEnter&) {};
	virtual void mouse_pressed(const event::MousePress&) {};
	virtual void mouse_release(const event::MouseRelease&) {};

	bool p_hidden{false};
	PointF p_pos{};
	SizeF p_size{};
	Parent* p_parent{nullptr};

	SizeF p_preferred_size{};
	SizeF p_min_size{};

	SizeF p_max_size{};

	std::weak_ptr<Scene> p_scene;
private:
	void render(Scene&, const PointF& relative_to = PointF{0.f, 0.f}) noexcept;
};
}

#endif //BGES_BASE_CLASSES_RENDERABLE_HPP
