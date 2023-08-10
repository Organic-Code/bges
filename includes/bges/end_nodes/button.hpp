#ifndef BGES_END_NOTES_BUTTON_HPP
#define BGES_END_NOTES_BUTTON_HPP

#include <bges/details/export.hpp>

#include <bges/base_classes/event_publishers.hpp>
#include <bges/base_classes/renderable.hpp>
#include <bges/base_classes/skin.hpp>
#include <bges/base_classes/skinable.hpp>
#include <bges/colors.hpp>

#include <bges/end_nodes/label.hpp>

namespace bges {

class BGES_CPPEXPORT Button : public Renderable, public event_publisher::Click<Button>, public Skinable<Button> {
public:
	enum class State {
		hovered,
		pressed,
		clicked,
		canceled,
		base
	};

	struct SkinData {
		PointF pos{};
		PointF relative{};
		SizeF size{};
		State state{};
		std::string_view text{};
	};

	explicit Button(std::string label) : m_text(std::move(label)) {
		p_skin = std::make_shared<default_skin>();
		p_size = {100, 30}; // TODO temporaire
		p_pos = {10, 500}; // TODO temporaire
	}

	void set_text(std::string text) noexcept {
		m_text = std::move(text);
	}

	// TODO

private:

	class BGES_CPPEXPORT default_skin : public Skin<Button> {
	public:
		virtual ~default_skin() = default;
	private:
		void render(Scene& sce, const SkinData& data) noexcept override;

		Label m_label{};
	};

	void mouse_moved(Parent&, const event::MouseMove&) noexcept;
	void mouse_press(Parent&, const event::MousePress&) noexcept;
	void mouse_release(Parent&, const event::MouseRelease&) noexcept;

	void vrender(Scene& sce, const PointF& relative_to) noexcept override;
    void set_parent(Parent*) noexcept override;

	bges::IColor m_color{200, 200, 200, 255};

	std::size_t m_mouse_move_id{0};
	std::size_t m_mouse_press_id{0};
	std::size_t m_mouse_release_id{0};
	bool m_mouse_pressed{false};
	std::string m_text{};
	State m_state{State::base};
};
}  // namespace bges

#endif //BGES_END_NOTES_BUTTON_HPP
