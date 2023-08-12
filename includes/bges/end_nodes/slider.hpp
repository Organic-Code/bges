#ifndef BGES_END_NODES_SLIDER_HPP
#define BGES_END_NODES_SLIDER_HPP

#include <bges/details/export.hpp>

#include <bges/base_classes/event_publishers.hpp>
#include <bges/base_classes/renderable.hpp>
#include <bges/base_classes/skin.hpp>
#include <bges/base_classes/skinable.hpp>
#include <bges/colors.hpp>

#include <bges/end_nodes/label.hpp>

namespace bges {

class BGES_CPPEXPORT Slider : public Renderable, public event_publisher::ValueUpdateFloat<Slider>, public Skinable<Slider> {
public:
	enum class State {
		pressed,
		base
	};

	struct SkinData {
		// TODO beaucoup de trucs à copier chaque frame (pareil dans Button)
		PointF pos{};
		PointF relative{};
		SizeF size{};
		State state{};
		float min{};
		float max{};
		float value{};
	};

	Slider(float min, float max) noexcept : Slider(min, max, min + max / 2) { }
	Slider(float min, float max, float value) noexcept : m_min{min}, m_max{max}, m_value{value} {
		assert(min < max && value >= min && value <= max);
		p_skin = std::make_shared<default_skin>();
		p_size = {500, 30}; // TODO temporaire
	}

	void set_min_max(float min, float max) {
		// TODO
		m_min = min;
		m_max = max;
		float new_value = std::clamp(m_value, min, max);
		if (new_value != m_value) {
			m_value = new_value;
			fire_value_update_float(*this, {m_value});
		}
	}

	~Slider() override {
		Slider::set_parent(nullptr);
	}

	// TODO

private:

	class BGES_CPPEXPORT default_skin : public Skin<Slider> {
	public:
		virtual ~default_skin() = default;
	private:
		void render(Scene& sce, const SkinData& data) noexcept override;
	};


	// automatically called by parent
	void mouse_pressed(const event::MousePress& ev) override;

	void mouse_moved_ev(const event::MouseMove& ev);

	void vrender(Scene& sce, const PointF& relative_to) noexcept override;
	//void set_parent(Parent*) noexcept override;

	void set_scene(const std::shared_ptr<Scene>& scene) override;

	bges::IColor m_color{200, 200, 200, 255};

	std::size_t m_mouse_release_id{0};
	std::size_t m_mouse_move_id{0};

	State m_state{State::base};
	float m_min{}, m_max{}, m_value{};
};
}  // namespace bges

#endif //BGES_END_NODES_SLIDER_HPP
