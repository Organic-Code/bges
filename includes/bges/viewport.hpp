#ifndef BGES_VIEWPORT_HPP
#define BGES_VIEWPORT_HPP

#include <bges/details/export.hpp>
#include <bges/geometry.hpp>

namespace bges {
class BGES_CPPEXPORT Viewport {
public:
	Viewport() noexcept = default;
	Viewport(float left_x, float top_y, float width, float height) noexcept : Viewport({left_x, top_y}, {width, height}) {}
	Viewport(PointF top_left, SizeF size) noexcept
	    : m_top_left{top_left}
	    , m_size{size} {};

	/**
	 * @return the top left point, where the viewport begins (minimizes x and y coordinates)
	 *
	 * @see Viewport::get_size()
	 * @see Viewport::get_center()
	 * @see Viewport::set_top_left()
	 */
    [[nodiscard]] PointF get_top_left() const noexcept;

	/**
	 * @return the point a the center of the viewport
	 *
	 * @see Viewport::get_half_size()
	 * @see Viewport::get_top_left()
	 * @see Viewport::set_center()
	 */
    [[nodiscard]] PointF get_center() const noexcept;

	/**
	 * @return the size of the viewport
	 *
	 * @see Viewport::get_top_left()
	 * @see Viewport::get_half_size()
	 * @see Viewport::set_size()
	 */
    [[nodiscard]] SizeF get_size() const noexcept;

	/**
	 * @return half the size of the viewport, intended to be used with get_center
	 *
	 * @see Viewport::get_center()
	 * @see Viewport::get_size()
	 * @see Viewport::set_half_size()
	 */
	[[nodiscard]] SizeF get_half_size() const noexcept;

	/**
	 * sets the top left point, where the viewport begins (minimizes x and y coordinates)
	 * @param top_left new top left point
	 *
	 * @see Viewport::set_center(PointF)
	 * @see Viewport::set_size(SizeF)
	 * @see Viewport::get_top_left()
	 * @see Viewport::move(PointF)
	 */
    void set_top_left(PointF top_left) noexcept;

	/**
	 * sets the point which shall be at the center of the viewport
	 * @param center new central point
	 *
	 * @see Viewport::set_top_left(PointF)
	 * @see Viewport::set_half_size(SizeF)
	 * @see Viewport::get_center()
	 * @see Viewport::move(PointF)
	 */
    void set_center(PointF center) noexcept;

	/**
	 * sets the size of the viewport
	 * @param size new size of the viewport
	 *
	 * @see Viewport::set_top_left(PointF)
	 * @see Viewport::set_half_size(SizeF)
	 * @see Viewport::get_size()
	 */
    void set_size(SizeF size) noexcept;

	/**
	 * sets the half size of the viewport, intended to be used with set_center
	 * @param half_size new half size of the viewport
	 *
	 * @see Viewport::set_center(PointF)
	 * @see Viewport::set_size(SizeF)
	 * @see Viewport::get_half_size()
	 */
    void set_half_size(SizeF half_size) noexcept;

	/**
	 * Zooms in or out the viewport around a given pivot point. factors > 1 zooms in (on the screen, stuff gets bigger), < 1 zooms out (on the screen, stuff gets smaller), = 1 you just wasted compute cycles
	 * @param zoom_factor zooming in or out by this factor ; should be > 0. [a factor of 2 will make every displayed object to double in apparent size]
	 * @param pivot pivot point. this point does not move relative to the window ; usually the position of the mouse relative to the viewport
	 *
	 * @see Viewport::zoom(float zoom_factor)
	 */
    void zoom(float zoom_factor, PointF pivot) noexcept;

    /**
     * Zooms in or out the viewport around a given pivot point. factors > 1 zooms in (on the screen, stuff gets bigger), < 1 zooms out (on the screen, stuff gets smaller), = 1 you just wasted compute cycles
     * The zooming is done such that the center stays still (ie : pivot = get_center())
     * @param zoom_factor zooming in or out by this factor ; should be > 0. [a factor of 2 will make every displayed object to double in apparent size]
     *
	 * @see Viewport::zoom(float zoom_factor, PointF pivot)
     */
    void zoom(float zoom_factor) noexcept;

	/**
	 * Moves the viewport around
	 * @param x_offset shifting to apply in the x coordinate
	 * @param y_offset shifting to apply in the y coordinate
	 *
	 * @see Viewport::move(PointF)
	 * @see Viewport::set_top_left(PointF)
	 * @see Viewport::set_center(PointF)
	 */
    void move(float x_offset, float y_offset) noexcept;

	/**
	 * Moves the viewport around
	 * @param offset Shifting to apply in the x and y coordinates
	 *
	 * @see Viewport::move(float, float)
	 * @see Viewport::set_top_left(PointF)
	 * @see Viewport::set_center(PointF)
	 */
    void move(PointF offset) noexcept;

private:
	PointF m_top_left{};
	SizeF m_size{};

	// TODO (c.f. sf::View::setViewport) ; associate each scene with a view (in bges::Window) ; if only one scene, .set_view is available, otherwise assert() fails
	// PointF m_top_left_dp_zone{};
	// SizeF m_top_left_dp_zone{};
};
} // namespace bges

#endif //BGES_VIEWPORT_HPP
