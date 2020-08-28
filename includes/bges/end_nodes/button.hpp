#ifndef BGES_END_NOTES_BUTTON_HPP
#define BGES_END_NOTES_BUTTON_HPP

#include <bges/details/export.hpp>

#include <bges/base_classes/event_publishers.hpp>
#include <bges/base_classes/renderable.hpp>
#include <bges/colors.hpp>

namespace bges {
class BGES_CPPEXPORT Button : public Renderable, public bges::event_publisher::Click<Button> {
public:
	Button() {
		p_size = {50, 20};
		p_pos = {10, 500};
	}

private:
	void mouse_moved(Parent&, const event::MouseMove&) noexcept;
	void mouse_press(Parent&, const event::MousePress&) noexcept;
	void mouse_release(Parent&, const event::MouseRelease&) noexcept;

	virtual void vrender(Scene&) noexcept override;
    virtual void set_parent(Parent*) noexcept override;

	bges::IColor m_color{200, 200, 200, 255};

	std::size_t m_mouse_move_id{0};
	std::size_t m_mouse_press_id{0};
	std::size_t m_mouse_release_id{0};
	bool m_mouse_pressed{false};
};
}

#endif //BGES_END_NOTES_BUTTON_HPP
