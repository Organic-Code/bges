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
	}

	void set_text(std::string text) noexcept {
		m_text = std::move(text);
	}

	~Button() {
		set_parent(nullptr);
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


	// automatically called by parent
	void mouse_exited(const event::MouseExit&) override;
	void mouse_entered(const event::MouseEnter&) override;
	void mouse_pressed(const event::MousePress&) override;
	void mouse_release(const event::MouseRelease&) override;

    void vrender(Scene& sce, const PointF& relative_to) noexcept override;
    void set_parent(Parent*) noexcept override;

	void set_scene(const std::shared_ptr<Scene>& scene) override;

	bges::IColor m_color{200, 200, 200, 255};

	std::size_t m_mouse_release_id{0};

	bool m_mouse_pressed{false};  // true if mouse is pressed on the button, info from parent
	bool m_mouse_released{false}; // true if mouse was released, info from scene
	std::string m_text{};
	State m_state{State::base};
};
}  // namespace bges

#endif //BGES_END_NOTES_BUTTON_HPP
