#ifndef BGES_BASE_CLASSES_RENDERABLE_HPP
#define BGES_BASE_CLASSES_RENDERABLE_HPP

#include <bges/details/export.hpp>
#include <bges/geometry.hpp>

#include <cassert>

namespace bges {
class Scene;
class Parent;

class BGES_CPPEXPORT Renderable {
public:
	class Attorney {
		static void render(Renderable& r, Scene& w) noexcept {
			r.render(w);
		}
		static void set_parent(Renderable& r, Parent* p) noexcept {
			r.set_parent(p);
		}
		friend class Scene;
		friend class Parent;
	};


	Renderable() noexcept = default;
	Renderable(const Renderable&) noexcept = default;
	Renderable(Renderable&&) noexcept = default;
	Renderable& operator=(const Renderable&) noexcept = default;
	Renderable& operator=(Renderable&&) noexcept = default;
    virtual ~Renderable() = default;

    void hide() noexcept;
    void un_hide() noexcept;
	[[nodiscard]] bool is_hidden() const noexcept;

	[[nodiscard]] SizeF get_displayed_size() const noexcept;

    void set_preferred_size(SizeF) noexcept;
    void set_min_size(SizeF) noexcept;
    void set_max_size(SizeF) noexcept;
    void set_size(SizeF) noexcept;

    SizeF get_preferred_size() noexcept;
    SizeF get_min_size() noexcept;
    SizeF get_max_size() noexcept;

	[[nodiscard]] PointF get_pos() const noexcept;

    void to_front() noexcept;
    void to_back() noexcept;

protected:
	virtual void vrender(Scene&) noexcept = 0;
	virtual void set_parent(Parent*) noexcept;

    bool p_hidden{false};
	PointF p_pos{};
	SizeF p_size{};
	Parent* p_parent{nullptr};

	SizeF p_preferred_size{};
	SizeF p_min_size{};
	SizeF p_max_size{};

private:
    void render(Scene&) noexcept;
};
}

#endif //BGES_BASE_CLASSES_RENDERABLE_HPP
