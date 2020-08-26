#include <bges/colors.hpp>

#include <cmath>

bges::Color::operator bges::IColor() const noexcept {
	return {static_cast<std::uint8_t>(std::round(red * 255)), static_cast<std::uint8_t>(std::round(green * 255)),
	        static_cast<std::uint8_t>(std::round(blue * 255)), static_cast<std::uint8_t>(std::round(alpha * 255))};
}

bges::IColor::operator bges::Color() const noexcept {
	return {red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f};
}
