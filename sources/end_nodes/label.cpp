#include <bges/end_nodes/label.hpp>
#include <bges/scene.hpp>

void bges::Label::vrender(Scene &sc, const PointF& relative_to) noexcept {
	sc.draw(*this, relative_to);
}
