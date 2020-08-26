#ifndef BGES_GEOMETRY_HPP
#define BGES_GEOMETRY_HPP

namespace bges {

template <typename T>
struct Point {
	T x{}, y{};
};

using PointF = Point<float>;
using PointI = Point<int>;


template <typename T>
struct Size {
	T width{}, height{};
};

using SizeF = Size<float>;
using SizeU = Size<unsigned>;

struct Viewport : PointF, SizeF {
};
} // namespace bges

#endif //BGES_GEOMETRY_HPP
