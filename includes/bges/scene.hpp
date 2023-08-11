#ifndef BGES_SCENE_HPP
#define BGES_SCENE_HPP

#include <vector>

#include <bges/base_classes/parent.hpp>
#include <bges/viewport.hpp>

namespace bges {

class Rectangle;
class Line;
class Label;

class BGES_CPPEXPORT Scene : public event_publisher::MouseEvents<Scene> {
public:
	struct BGES_CPPEXPORT Attorney {
		static void set_window(Scene& scene, class Window* window) noexcept;
		static void render(Scene& scene) noexcept;
		static void mouse_move(Scene&, const event::MouseMove& ev);
		static void mouse_press(Scene&, const event::MousePress& ev);
		static void mouse_release(Scene&, const event::MouseRelease& ev);
		static void mouse_scroll(Scene&, const event::MouseScroll& ev);
		static void mouse_enter(Scene&, const event::MouseEnter& ev);
		static void mouse_exit(Scene&, const event::MouseExit& ev);

		friend class Window;
	};

	static std::shared_ptr<Scene> create();

	[[nodiscard]] const std::shared_ptr<Parent>& get_root() noexcept;
	static void set_root(const std::shared_ptr<Scene>& this_scene, std::shared_ptr<Parent>) noexcept;

    [[nodiscard]] const Viewport& get_viewport() const noexcept;
    Viewport& viewport() noexcept;
    void set_viewport(const Viewport&) noexcept;

    void draw(const Rectangle &rect, const PointF& relative_to = PointF{0.f,0.f}) noexcept;
    void draw(const Line &line, const PointF& relative_to = PointF{0.f, 0.f}) noexcept;
	void draw(const Label& label, const PointF& relative_to = PointF{0.f, 0.f}) noexcept;

	void hide() noexcept {
		m_hidden = true;
	}

	void un_hide() noexcept {
		m_hidden = false;
	}

private:

	void render() noexcept;

    void mouse_move(const event::MouseMove&);
    void mouse_press(const event::MousePress&);
    void mouse_release(const event::MouseRelease&);
    void mouse_scroll(const event::MouseScroll&);
    void mouse_enter(const event::MouseEnter&);
    void mouse_exit(const event::MouseExit&);

    std::shared_ptr<Parent> m_root;
    bool m_hidden{false};
    Viewport m_viewport{};
	Window* m_parent{nullptr};
};

}

#endif //BGES_SCENE_HPP
