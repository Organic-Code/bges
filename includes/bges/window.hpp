#ifndef BGES_WINDOW_HPP
#define BGES_WINDOW_HPP

#include <array>
#include <functional>
#include <memory>

#include <bges/details/export.hpp>
#include <bges/base_classes/event_publishers.hpp>
#include <../sources/backend_context.hpp>

namespace bges {

struct Rectangle;
struct Line;
class Viewport;
class Scene;

namespace backend {
	struct Context;
}

class BGES_CPPEXPORT Window: public event_publisher::MouseEvents<Window &>,
              public event_publisher::KeyboardEvents<Window &>,
              public event_publisher::WindowEvents<Window &> {
public:
	// does not open the window. call "open" to open
	Window();

	Window(Window &&) noexcept = default;
	Window &operator=(Window &&) noexcept = default;

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	~Window();

	// return false on failure
	bool open(const char *name) noexcept;
	bool open(const char *name, unsigned int width, unsigned int height) noexcept;

	void set_viewport(const Viewport &vp);
	void set_size(unsigned int width, unsigned int height) noexcept;
	void close() noexcept;

	[[nodiscard]] bool is_open() const noexcept;

	// using scenes and not rectangle.

	void clear() noexcept;
	void render() noexcept;

	[[nodiscard]] std::vector<Scene>::size_type scene_count() const noexcept;
	Scene &get_scene(std::vector<Scene>::size_type idx) noexcept;
	[[nodiscard]] const Scene &get_scene(std::vector<Scene>::size_type idx) const noexcept;
	void add_scene(std::shared_ptr<Scene> scene);
	void show_scene(std::vector<Scene>::size_type idx) noexcept;

	template <unsigned int N>
	void show_scenes(const std::array<std::vector<Scene>::size_type, N>& scenes) noexcept {
		hide_all_scenes();
		for (auto idx : scenes) {
			unhide_scene(idx);
		}
	}



	struct Attorney {
		static bges::backend::Context& get_context(Window& win) noexcept {
			assert(win.m_ctx != nullptr);
			return *win.m_ctx;
		}
	};

private:
	void unhide_scene(std::vector<Scene>::size_type idx) noexcept;
	void hide_all_scenes() noexcept;

	// Come on, why do I need that struct ? MSVC you’re killing me u.u
    struct backend_ctx_ptr_t : std::unique_ptr<bges::backend::Context> {
		~backend_ctx_ptr_t();
	} m_ctx{};

	std::vector<std::shared_ptr<Scene>> m_scenes{};
};
} // namespace bges

#endif //BGES_WINDOW_HPP
