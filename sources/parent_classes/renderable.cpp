#include <cassert>

#include <bges/base_classes/renderable.hpp>
#include <bges/base_classes/parent.hpp>
#include <bges/geometry.hpp>

void bges::Renderable::render(bges::Scene& sc, const PointF& relative_to) noexcept {
	if (!is_hidden()) {
		vrender(sc, relative_to);
	}
}

void bges::Renderable::hide() noexcept {
	p_hidden = true;
}

void bges::Renderable::un_hide() noexcept {
	p_hidden = false;
}
bool bges::Renderable::is_hidden() const noexcept {
	return p_hidden;
}

bges::SizeF bges::Renderable::get_displayed_size() const noexcept {
	return p_size;
}

void bges::Renderable::set_preferred_size(SizeF size) noexcept {
	p_preferred_size = size;
}

void bges::Renderable::set_min_size(SizeF size) noexcept {
	p_min_size = size;
}

void bges::Renderable::set_max_size(SizeF size) noexcept {
	p_max_size = size;
}

void bges::Renderable::set_size(SizeF size) noexcept {
	set_preferred_size(size);
	set_max_size(size);
	set_min_size(size);
}

bges::SizeF bges::Renderable::get_preferred_size() noexcept {
	return p_preferred_size;
}

bges::SizeF bges::Renderable::get_min_size() noexcept {
	return p_min_size;
}

bges::SizeF bges::Renderable::get_max_size() noexcept {
	return p_max_size;
}


bges::PointF bges::Renderable::get_pos() const noexcept {
	return p_pos;
}

void bges::Renderable::to_front() noexcept {
	assert(p_parent);
	p_parent->bring_to_front(this);
}

void bges::Renderable::to_back() noexcept {
    assert(p_parent);
	p_parent->bring_to_back(this);
}

void bges::Renderable::set_parent(Parent * p) noexcept {
    assert((p_parent == nullptr || p == nullptr) && "Only one parent at a time");
	p_parent = p;
}

void bges::Renderable::set_pos(bges::PointF p) noexcept {
	p_pos = p;
}
