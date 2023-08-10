#include <bges/shapes.hpp>
#include <bges/scene.hpp>

void bges::Rectangle::vrender(Scene &sc, const PointF& relative_to) noexcept {
	sc.draw(*this, relative_to);
}

void bges::Line::vrender(Scene &sc, const PointF& relative_to) noexcept {
	sc.draw(*this, relative_to);
}
