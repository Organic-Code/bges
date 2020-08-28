#include <bges/shapes.hpp>
#include <bges/scene.hpp>

void bges::Rectangle::vrender(Scene &sc) noexcept {
	sc.draw(*this);
}

void bges::Line::vrender(Scene &sc) noexcept {
	sc.draw(*this);
}
