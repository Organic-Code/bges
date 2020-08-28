#ifndef BGES_SCENE_HPP
#define BGES_SCENE_HPP

#include <vector>

#include <bges/base_classes/parent.hpp>
#include <bges/viewport.hpp>

namespace bges {

class Rectangle;
class Line;

class BGES_CPPEXPORT Scene : public event_publisher::MouseEvents<Scene> {
public:
	struct BGES_CPPEXPORT Attorney {
		static void set_window(Scene& scene, class Window* window) noexcept;
		static void render(Scene& scene) noexcept;
		static void mouse_move(Scene&, const event::MouseMove& ev);
		static void mouse_press(Scene&, const event::MousePress& ev);
		static void mouse_release(Scene&, const event::MouseRelease& ev);
		static void mouse_scroll(Scene&, const event::MouseScroll& ev);

		friend class Window;
	};

	Scene();

	const std::shared_ptr<Parent>& get_root() noexcept;
	void set_root(std::shared_ptr<Parent>) noexcept;

    [[nodiscard]] const Viewport& get_viewport() const noexcept;
    Viewport& viewport() noexcept;
    void set_viewport(const Viewport&) noexcept;

    void draw(const Rectangle &rect) noexcept;
    void draw(const Line &line) noexcept;

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

    std::shared_ptr<Parent> m_root;
    bool m_hidden{false};
    Viewport m_viewport{};
	Window* m_parent{nullptr};
};

}

#endif //BGES_SCENE_HPP
