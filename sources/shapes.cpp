#include <bges/shapes.hpp>
#include <bges/scene.hpp>

void bges::Rectangle::vrender(Scene &sc, const PointF& relative_to) noexcept {
	// FIXME : pas besoin d’à la fois "rect" et "p_pos"+"p_size"
	p_pos.x = rect.x;
	p_pos.y = rect.y;
	p_size.width = rect.width;
	p_size.height = rect.height;
	sc.draw(*this, relative_to);
}

void bges::Line::vrender(Scene &sc, const PointF& relative_to) noexcept {
	sc.draw(*this, relative_to);
}
