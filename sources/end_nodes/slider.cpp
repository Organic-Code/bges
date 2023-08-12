#include <bges/end_nodes/slider.hpp>
#include <bges/events.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>

namespace {
} // namespace


void bges::Slider::vrender(Scene &sc, const PointF &relative_to) noexcept {
	p_skin->render(sc, {p_pos, relative_to, p_size, m_state, m_min, m_max, m_value});
}

void bges::Slider::mouse_pressed(const bges::event::MousePress &ev) {
	m_state = State::pressed;
	mouse_moved_ev({ev.x, ev.y});
}

void bges::Slider::set_scene(const std::shared_ptr<Scene> &scene) {
	if (auto locked = p_scene.lock() ; locked != nullptr) {
		locked->remove_mouse_release_listener(m_mouse_release_id);
		locked->remove_mouse_move_listener(m_mouse_move_id);
	}
	if (scene != nullptr) {
		m_mouse_release_id = scene->on_mouse_release([this](Scene& scene, const event::MouseRelease& ev) {
			m_state = State::base;
		});
		m_mouse_move_id = scene->on_mouse_move([this](Scene& scene, const event::MouseMove& ev) {
            mouse_moved_ev(ev);
        });
	}
	Renderable::set_scene(scene);
}

void bges::Slider::mouse_moved_ev(const bges::event::MouseMove &ev) {
	if (m_state != State::pressed) {
		return;
	}
	if (ev.x <= p_pos.x) {
		m_value = m_min;
	} else if (ev.x >= p_pos.x + p_size.width) {
		m_value = m_max;
	} else {
		m_value = (ev.x - p_pos.x) / p_size.width * (m_max - m_min) + m_min;
	}
	fire_value_update_float(*this, {m_value});
}

void bges::Slider::default_skin::render(Scene& sce, const SkinData& data) noexcept {
	Rectangle rect;
	rect.rect.x                 = static_cast<int>(data.pos.x);
	rect.rect.y                 = static_cast<int>(data.pos.y);
	rect.rect.width             = static_cast<unsigned int>(data.size.width);
	rect.rect.height            = static_cast<unsigned int>(data.size.height);
	rect.rect.outline_thickness = 0;
	rect.fill_color = bges::colors::darkorchid;

	Rectangle slide;
	slide.rect.x = static_cast<int>(data.pos.x);
	slide.rect.y = static_cast<int>(data.pos.y + data.size.height / 2);
	slide.rect.width = static_cast<unsigned int>(data.size.width);
	slide.rect.height = 2;
	slide.rect.outline_thickness = 0;
	slide.fill_color = bges::colors::black;

	Rectangle cursor;
	cursor.rect.width = 4;
	cursor.rect.height = static_cast<unsigned int>(data.size.height);
	cursor.rect.y = static_cast<int>(data.pos.y);
	cursor.rect.x = static_cast<int>((data.value - data.min) / (data.max - data.min) * (data.size.width - cursor.rect.width) + data.pos.x);
	if (data.state == State::pressed) {
        cursor.fill_color = bges::colors::dimgrey;
    } else {
		cursor.fill_color = bges::colors::lightslategrey;
	}
	cursor.fill_color.alpha = 0.80f;


	sce.draw(rect, data.relative);
	sce.draw(slide, data.relative);
	sce.draw(cursor, data.relative);
}