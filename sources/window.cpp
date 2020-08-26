#include <bges/shapes.hpp>
#include <bges/window.hpp>
#include <bges/geometry.hpp>
#include <cassert>
#include <memory>
#include <string_view>

#include "backend_context.hpp"
#include "utils.hpp"

namespace {
template <typename Container, typename... Args>
typename std::enable_if<std::is_same<std::invoke_result_t<typename Container::value_type, Args...>, void>::value>::type
fire(Container &container, Args &&... args) {
	for (auto &listener : container) {
		try {
			listener(std::forward<Args>(args)...);
		}
		catch (...) {
			// TODO
		}
	}
}

template <typename Container, typename FuncT, typename... Args>
std::enable_if_t<!std::is_same_v<std::invoke_result_t<typename Container::value_type, Args...>, void>>
fire(Container &container, FuncT &&funct, Args &&... args) {
	for (auto &listener : container) {
		try {
			funct(listener(std::forward<Args>(args)...));
		}
		catch (...) {
			// TODO
		}
	}
}

} // namespace

bges::Window::Window() noexcept
    : m_ctx{} { }
bges::Window::~Window() = default;

bool bges::Window::open(const char *name) noexcept {
#if BGES_STATIC_BACKEND == 1
	std::optional<backend::Context> ctx = backend::init();
#else
	std::string dll_path = std::filesystem::current_path().generic_string() + "/";
	if (std::filesystem::is_regular_file("libbges_sfml-backenddbg.so")) {
		dll_path += "libbges_sfml-backenddbg.so";
	}
	else if (std::filesystem::is_regular_file("bges_sfml-backenddbg.dll")) {
		dll_path += "bges_sfml-backenddbg.dll";
	}
	else if (std::filesystem::is_regular_file("libbges_sfml-backend.so")) {
		dll_path += "libbges_sfml-backend.so";
	}
	else if (std::filesystem::is_regular_file("bges_sfml-backend.dll")) {
		dll_path += "bges_sfml-backend.dll";
	}
	else {
		return false;
	}
	std::optional<backend::Context> ctx = backend::init(dll_path);
#endif
	if (!ctx) {
		return false;
	}
	m_ctx = std::make_unique<backend::Context>(std::move(*ctx));

	return m_ctx->open(m_ctx.get(), name);
}

bool bges::Window::open(const char *name, unsigned int width, unsigned int height) noexcept {
	if (open(name)) {
		set_size(width, height);
		return true;
	}
	return false;
}
void bges::Window::set_viewport(const Viewport& vp) {
    m_ctx->set_viewport(m_ctx.get(), bges_ffi::viewport{vp.x, vp.y, vp.width, vp.height});
}

void bges::Window::set_size(unsigned int width, unsigned int height) noexcept {
	assert(m_ctx != nullptr);
	assert(is_open());
	m_ctx->resize(m_ctx.get(), {width, height});
}

void bges::Window::close() noexcept {
	assert(m_ctx != nullptr);
	assert(is_open());
	m_ctx->close(m_ctx.get());
}

bool bges::Window::is_open() const noexcept {
	assert(m_ctx != nullptr);
	return m_ctx->is_open(m_ctx.get());
}

void bges::Window::draw(const Rectangle &rect) noexcept {
	assert(m_ctx != nullptr);
	m_ctx->draw_outlined_rectangle(m_ctx.get(), {rect.x, rect.y}, {rect.width, rect.height}, foreign_color(rect.fill_color),
	                               static_cast<std::uint16_t>(rect.outline_thickness), foreign_color(rect.outline_color));
}

void bges::Window::draw(const Line &line) noexcept {
	assert(m_ctx != nullptr);
	m_ctx->draw_line(m_ctx.get(), {line.min_pos.x, line.min_pos.y}, {line.max_pos.x, line.max_pos.y}, foreign_color(line.color));
}

void bges::Window::clear() noexcept {
	assert(m_ctx != nullptr);
	m_ctx->clear(m_ctx.get());
}

void bges::Window::render() noexcept {
	assert(m_ctx != nullptr);
	m_ctx->render(m_ctx.get());

	bges_ffi::event_list events;
	auto deleter = [this](bges_ffi::event_list *el) {
		m_ctx->free_events(m_ctx.get(), el);
	};
	std::unique_ptr<bges_ffi::event_list, decltype(deleter)> events_ptr(&events, std::move(deleter));

	m_ctx->retrieve_events(m_ctx.get(), &events);

	for (auto it = events.begin; it != events.end; ++it) {
		if (it->type == bges_ffi::event_type::CLOSE) {
			fire(
			  m_on_close_request,
			  [this](bool should_close) {
				  if (should_close)
					  close();
			  },
			  *this);
		}
	}
}

void bges::Window::on_close_request(std::function<bool(Window &)> on_close_listener) {
	m_on_close_request.emplace_back(std::move(on_close_listener));
}
