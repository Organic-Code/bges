#ifndef BGES_GEOMETRY_HPP
#define BGES_GEOMETRY_HPP

namespace bges {

template <typename T>
struct Point {
	T x{}, y{};

	Point operator+(const Point& other) const noexcept {
		return Point{*this} += other;
	}
	Point& operator+=(const Point& other) noexcept {
		x += other.x;
		y += other.y;
		return *this;
	}

	Point operator-(const Point& other) const noexcept {
        return Point{*this} -= other;
	}
	Point& operator-=(const Point& other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;

	}
};

using PointF = Point<float>; // NOLINT(readability-identifier-naming)
using PointI = Point<int>; // NOLINT(readability-identifier-naming)


template <typename T>
struct Size {
	T width{}, height{};

    Size operator*(T factor) const noexcept {
		return Size{*this} *= factor;
	}
    Size& operator*=(T factor) noexcept {
		width *= factor;
		height *= factor;
		return *this;
	}

    Size operator/(T factor) const noexcept {
		return Size{*this} /= factor;
	}
    Size& operator/=(T factor) noexcept {
		width /= factor;
		height /= factor;
		return *this;
	}
};

using SizeF = Size<float>; // NOLINT(readability-identifier-naming)
using SizeU = Size<unsigned>; // NOLINT(readability-identifier-naming)

struct GeoRectangle: PointI, SizeU {
    unsigned int outline_thickness{};
};

struct GeoLine {
    PointI min_pos{};
    PointI max_pos{};
};
} // namespace bges

#endif //BGES_GEOMETRY_HPP
