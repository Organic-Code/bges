#ifndef BGES_SHAPES_HPP
#define BGES_SHAPES_HPP

#include <bges/colors.hpp>
#include <bges/geometry.hpp>
#include <bges/base_classes/renderable.hpp>

namespace bges {

// TODO
class BGES_CPPEXPORT Rectangle : public Renderable {
public:
	GeoRectangle rect{};
	Color outline_color{};
	Color fill_color{};

protected:
    void vrender(Scene&, const PointF& relative_to) noexcept override;
};

class BGES_CPPEXPORT Line : public Renderable {
public:
	GeoLine line{};
	Color color{};

protected:
    void vrender(Scene&, const PointF& relative_to) noexcept override;
};

} // namespace bges

#endif //BGES_SHAPES_HPP
