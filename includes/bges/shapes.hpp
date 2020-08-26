#ifndef BGES_SHAPES_HPP
#define BGES_SHAPES_HPP

#include <bges/colors.hpp>
#include <bges/geometry.hpp>

namespace bges {
struct Rectangle: PointI, SizeU {
	Color fill_color{};
	Color outline_color{};
	unsigned int outline_thickness{};
};

struct Line {
	Color color{};
	PointI min_pos{};
	PointI max_pos{};
};
} // namespace bges

#endif //BGES_SHAPES_HPP
