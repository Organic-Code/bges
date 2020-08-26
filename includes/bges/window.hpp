#ifndef BGES_WINDOW_HPP
#define BGES_WINDOW_HPP

#include <memory>
#include <functional>

#include <bges/details/export.hpp>

namespace bges {

struct Rectangle;
struct Line;
struct Viewport;

namespace backend {
	struct Context;
}

class Window {
public:
	// does not open the window. call "open" to open
	BGES_CPPEXPORT Window() noexcept;

	BGES_CPPEXPORT Window(Window &&);
	BGES_CPPEXPORT Window &operator=(Window &&);

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	BGES_CPPEXPORT ~Window();

	// return false on failure
	BGES_CPPEXPORT [[nodiscard]] bool open(const char *name) noexcept;
	BGES_CPPEXPORT [[nodiscard]] bool open(const char *name, unsigned int width, unsigned int height) noexcept;

	BGES_CPPEXPORT void set_viewport(const Viewport& vp);
	BGES_CPPEXPORT void set_size(unsigned int width, unsigned int height) noexcept;
	BGES_CPPEXPORT void close() noexcept;

	BGES_CPPEXPORT [[nodiscard]] bool is_open() const noexcept;

	BGES_CPPEXPORT void draw(const Rectangle &rect) noexcept;
	BGES_CPPEXPORT void draw(const Line &line) noexcept;

	// using scenes and not rectangle.

	BGES_CPPEXPORT void clear() noexcept;
	BGES_CPPEXPORT void render() noexcept;

	// the caller shall return true to close the window
	BGES_CPPEXPORT void on_close_request(std::function<bool(Window&)> on_close_listener);

private:
	std::unique_ptr<backend::Context> m_ctx;

	std::vector<std::function<bool(Window&)>> m_on_close_request;
};
} // namespace bges

#endif //BGES_WINDOW_HPP
