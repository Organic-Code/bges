#ifndef BGES_BASE_CLASSES_RENDERABLE_HPP
#define BGES_BASE_CLASSES_RENDERABLE_HPP

#include <bges/details/export.hpp>
#include <bges/geometry.hpp>

#include <cassert>

namespace bges {
class Scene;
class Parent;

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

	class Attorney {
		static void render(Renderable& r, Scene& w, const PointF& relative_to = PointF{0.f,0.f}) noexcept {
			r.render(w, relative_to);
		}
		static void set_parent(Renderable& r, Parent* p) noexcept {
			r.set_parent(p);
		}
		friend class Scene;
		friend class Parent;
		friend class Button; // todo : ne pas ajouter le bouton juste comme ça (sert actuellement pour faire le rendu du label)
	};

protected:
	virtual void vrender(Scene&, const PointF& relative_to) noexcept = 0;
	virtual void set_parent(Parent*) noexcept;

    bool p_hidden{false};
	PointF p_pos{};
	SizeF p_size{};
	Parent* p_parent{nullptr};

	SizeF p_preferred_size{};
	SizeF p_min_size{};
	SizeF p_max_size{};

private:
    void render(Scene&, const PointF& relative_to = PointF{0.f, 0.f}) noexcept;
};
}

#endif //BGES_BASE_CLASSES_RENDERABLE_HPP
