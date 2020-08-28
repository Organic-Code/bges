#include <cassert>

#include <bges/viewport.hpp>

bges::PointF bges::Viewport::get_top_left() const noexcept {
	return m_top_left;
}

bges::PointF bges::Viewport::get_center() const noexcept {
	return {m_top_left.x + m_size.width / 2, m_top_left.y + m_size.height / 2};
}

bges::SizeF bges::Viewport::get_size() const noexcept {
	return m_size;
}

bges::SizeF bges::Viewport::get_half_size() const noexcept {
	return m_size / 2.f;
}

void bges::Viewport::set_top_left(PointF top_left) noexcept {
	m_top_left = top_left;
}

void bges::Viewport::set_center(PointF center) noexcept {
	m_top_left = {center.x - m_size.width / 2, center.y - m_size.height / 2};
}

void bges::Viewport::set_size(SizeF size) noexcept {
	m_size = size;
}

void bges::Viewport::set_half_size(SizeF half_size) noexcept {
	m_size = half_size * 2.f;
}

void bges::Viewport::zoom(float zoom_factor, PointF pivot) noexcept {
	assert(zoom_factor > 0);

	zoom_factor = 1 / zoom_factor;

	PointF vp2pvt_ratio = {(pivot.x - m_top_left.x) / m_size.width, (pivot.y - m_top_left.y) / m_size.height};
	m_size *= zoom_factor;

	m_top_left.x = pivot.x - vp2pvt_ratio.x * m_size.width;
	m_top_left.y = pivot.y - vp2pvt_ratio.y * m_size.height;
}

void bges::Viewport::zoom(float zoom_factor) noexcept {
	zoom(zoom_factor, get_center());
}

void bges::Viewport::move(float x_offset, float y_offset) noexcept {
	move({x_offset, y_offset});
}

void bges::Viewport::move(PointF offset) noexcept {
	m_top_left += offset;
}
