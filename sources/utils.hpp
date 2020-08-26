#ifndef BGES_UTILS_HPP
#define BGES_UTILS_HPP

namespace bges_ffi::version_0 {
struct bges_color;
}

namespace bges {

struct Color;
bges_ffi::version_0::bges_color foreign_color(const Color& color);

}

#endif //BGES_UTILS_HPP
