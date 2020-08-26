#ifndef BGES_BACKEND_CONTEXT_HPP
#define BGES_BACKEND_CONTEXT_HPP

#include <filesystem>
#include <optional>

#if defined OS_WINDOWS
#	include <Windows.h>
#endif

#include "common/exchanged_types.h"

namespace bges::backend {
struct Context : bges_ffi::backend_win_ctx {

	Context(Context &&) noexcept;
	Context(const Context &) = delete;
	Context & operator=(Context &&) noexcept;
	Context & operator=(const Context &) = delete;
    ~Context();

private:
#if defined OS_WINDOWS
    HMODULE m_handle{};
#elif defined OS_LINUX
    void *m_handle{};
#endif

    void (*destroy_ctx)(bges_ffi::version, bges_backend_win_ctx *){nullptr};

	Context() noexcept : bges_ffi::backend_win_ctx{} {};

#if BGES_STATIC_BACKEND == 1
    friend std::optional<Context> init();
#else
	friend std::optional<Context> init(const std::filesystem::path&);
#endif
};

#if BGES_STATIC_BACKEND == 1
[[nodiscard]] std::optional<Context> init();
#else
[[nodiscard]] std::optional<Context> init(const std::filesystem::path&);
#endif

} // namespace backend

#endif // BGES_BACKEND_CONTEXT_HPP