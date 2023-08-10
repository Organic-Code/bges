#include <filesystem>
#include <optional>

#if defined OS_LINUX
#	include <dlfcn.h> // dlsym, dlopen, dlclose, dlerror
#elif defined OS_WINDOWS
#	include <Windows.h> // GetProcAddress, LoadLibrary, FreeLibrary, GetLastError, FormatMessageA
#endif

#include "common/exchanged_types.h"
#include "bges/bges.hpp"

#include "backend_context.hpp"

#if BGES_STATIC_BACKEND == 1
extern "C" void bgesbe_init_ctx(bges_ffi::version, bges_ffi::backend_win_ctx *);
extern "C" void bgesbe_destroy_ctx(bges_ffi::version, bges_ffi::backend_win_ctx *);
#endif

namespace backend = bges::backend;

namespace {
constexpr const char *BACKEND_INIT_FNNAME    = "bgesbe_init_ctx";
constexpr const char *BACKEND_DESTROY_FNNAME = "bgesbe_destroy_ctx";
constexpr bges_ffi::version my_version{0, 0, 0};
} // namespace

namespace {

void default_draw_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color color) {
	if (size.height > size.width) {
		auto y_end = static_cast<std::int32_t>(pos.y + size.height);
		while (size.width--) {
			ctx->draw_line(ctx, pos, {pos.x, y_end}, color);
			++pos.x;
		}
	}
	else {
		auto x_end = static_cast<std::int32_t>(pos.x + size.width);
		while (size.height--) {
			ctx->draw_line(ctx, pos, {x_end, pos.y}, color);
			++pos.y;
		}
	}
}

void default_draw_outlined_rectangle(bges_ffi::backend_win_ctx *ctx, bges_ffi::point pos, bges_ffi::size size, bges_ffi::color fill_color,
                                     uint16_t outline_thickness, bges_ffi::color outline_color) {
	if (size.width <= 2 * outline_thickness || size.height <= 2 * outline_thickness) {
		ctx->draw_rectangle(ctx, pos, size, outline_color);
		return;
	}

	bges_ffi::point temp_pt;
	bges_ffi::size temp_sz;

	// middle
	temp_pt.x      = pos.x + outline_thickness;
	temp_pt.y      = pos.y + outline_thickness;
	temp_sz.width  = size.width - 2 * outline_thickness;
	temp_sz.height = size.height - 2 * outline_thickness;
	ctx->draw_rectangle(ctx, temp_pt, temp_sz, fill_color);

	// top
	temp_pt = pos;
	temp_sz.width = size.width;
	temp_sz.height = outline_thickness;
	ctx->draw_rectangle(ctx, temp_pt, temp_sz, outline_color);

	// left
	temp_sz.width = outline_thickness;
	temp_sz.height = size.height;
    ctx->draw_rectangle(ctx, temp_pt, temp_sz, outline_color);

	// right
	temp_pt.x = pos.x + size.width - outline_thickness;
    ctx->draw_rectangle(ctx, temp_pt, temp_sz, outline_color);

	// bottom
	temp_sz.width = size.width;
	temp_sz.height = outline_thickness;
	temp_pt.x = pos.x;
	temp_pt.y = pos.y + size.height - outline_thickness;
	ctx->draw_rectangle(ctx, temp_pt, temp_sz, outline_color);
}

// called post loading
std::optional<backend::Context> sanitize(backend::Context &ctx) {
	if (ctx.backend_version.major != my_version.major) {
		return {};
	}
	if (ctx.open == nullptr) {
		return {};
	}
	if (ctx.resize == nullptr) {
		return {};
	}
	if (ctx.close == nullptr) {
		return {};
	}
	if (ctx.is_open == nullptr) {
		return {};
	}
	if (ctx.render == nullptr) {
		return {};
	}
	if (ctx.clear == nullptr) {
		return {};
	}
	if (ctx.draw_line == nullptr) {
		return {};
	}


	if (ctx.draw_rectangle == nullptr) {
		ctx.draw_rectangle = &default_draw_rectangle;
	}
	if (ctx.draw_outlined_rectangle == nullptr) {
		ctx.draw_outlined_rectangle = &default_draw_outlined_rectangle;
	}

	return {std::move(ctx)};
}
} // namespace

namespace {
struct state {
	std::filesystem::path library_path{};
	bool initialized{false};
};

state glob_state{};
} // namespace
const std::filesystem::path& bges::backend::glob_library_path{glob_state.library_path};

bool bges::init(const std::filesystem::path& lib_path) {
	if (!glob_state.initialized) {
#if BGES_STATIC_BACKEND == 0
		if (!std::filesystem::is_regular_file(lib_path)) {
			return false;
		}
#endif
		glob_state.library_path = lib_path;
		glob_state.initialized = true;
		return true;
	}
	return false;
}

bool bges::is_init() {
	return glob_state.initialized;
}


backend::Context::~Context() {
	if (m_handle == nullptr) {
		return;
	}

	if (destroy_ctx != nullptr) {
		destroy_ctx(my_version, this);
	}

#if defined OS_WINDOWS
	FreeLibrary(m_handle);
#elif defined OS_LINUX
	dlclose(m_handle);
#endif
}

backend::Context &backend::Context::operator=(backend::Context &&other) noexcept {
	bges_ffi::backend_win_ctx::operator=(other);
	destroy_ctx                        = other.destroy_ctx;
	m_handle                           = std::exchange(other.m_handle, nullptr);
	return *this;
}

backend::Context::Context(backend::Context &&other) noexcept {
	*this = std::move(other);
}


// todo : return fail reason
std::optional<backend::Context> backend::init() {
	Context ctx{};
#if BGES_STATIC_BACKEND == 1
	bgesbe_init_ctx(my_version, &ctx);
	ctx.destroy_ctx = bgesbe_destroy_ctx;

#else

	std::string str_path;
	if (glob_library_path.is_relative()) {
		str_path = "./" + glob_library_path.generic_string();
	}
	else {
		str_path = glob_library_path.generic_string();
	}

#	if defined OS_LINUX
	ctx.m_handle = dlopen(str_path.c_str(), RTLD_NOW);
#	elif defined OS_WINDOWS
	for (char &c : str_path) {
		if (c == '/') {
			c = '\\'; // required by LoadLibrary for some reason
		}
	}

	ctx.m_handle = LoadLibrary(str_path.c_str());
#	endif

	if (ctx.m_handle == nullptr) {
		return {};
	}

#	if defined OS_WINDOWS

	auto ctx_init
	  = reinterpret_cast<void (*)(bges_ffi::version, bges_ffi::backend_win_ctx *)>(GetProcAddress(ctx.m_handle, BACKEND_INIT_FNNAME));
	auto ctx_destroy
	  = reinterpret_cast<void (*)(bges_ffi::version, bges_ffi::backend_win_ctx *)>(GetProcAddress(ctx.m_handle, BACKEND_DESTROY_FNNAME));

#	elif defined OS_LINUX

	auto ctx_init = reinterpret_cast<void (*)(bges_ffi::version, bges_ffi::backend_win_ctx *)>(dlsym(ctx.m_handle, BACKEND_INIT_FNNAME));
	auto ctx_destroy
	  = reinterpret_cast<void (*)(bges_ffi::version, bges_ffi::backend_win_ctx *)>(dlsym(ctx.m_handle, BACKEND_DESTROY_FNNAME));

#	endif

	if (ctx_init == nullptr || ctx_destroy == nullptr) {
		return {};
	}

	ctx_init(my_version, &ctx);
	ctx.destroy_ctx = ctx_destroy;

#endif
	return sanitize(ctx);
}
