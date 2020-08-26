#ifndef BGES_COLORS_HPP
#define BGES_COLORS_HPP

#include <cstdint>
#include <bges/details/export.hpp>

namespace bges {

struct IColor;
struct Color {
	float red{0};
	float green{0};
	float blue{0};
	float alpha{1.f};

    BGES_CPPEXPORT operator IColor() const noexcept;
};

struct IColor {
	std::uint8_t red{0};
	std::uint8_t green{0};
	std::uint8_t blue{0};
	std::uint8_t alpha{255};

    BGES_CPPEXPORT operator Color() const noexcept;
};
} // namespace bges

#endif //BGES_COLORS_HPP
