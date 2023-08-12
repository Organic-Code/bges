#include <bges/base_classes/parent.hpp>

#include <algorithm>
#include <vector>

namespace {
std::size_t find_child(const std::vector<std::shared_ptr<bges::Renderable>>& children, const bges::PointF& point) {
	for (unsigned int i = children.size() ; i--;) { // starting with the lastly rendered one
		if (children[i]->is_within(point)) {
			return i;
		}
	}
	return std::numeric_limits<std::size_t>::max();
}
}

namespace {
struct ptr_comp {
	const bges::Renderable *renderable;

	bool operator()(const bges::Parent::child_type &ptr) const noexcept {
		return renderable == ptr.get();
	}

	bool operator()(const bges::Parent::child_type::element_type *other) const noexcept {
		return renderable == other;
	}
};
} // namespace


bges::Parent::~Parent() {
	for (auto &child : p_children) {
		Renderable::Attorney::set_parent(*child, nullptr);
	}
}

const std::vector<bges::Parent::child_type> &bges::Parent::children() const noexcept {
	return p_children;
}

void bges::Parent::add_child(child_type c) {
	assert(std::find(p_children.begin(), p_children.end(), c) == p_children.end() && "Cannot add the same child multiple times");
	Renderable::Attorney::set_parent(*c, this);
	p_children.emplace_back(std::move(c));

	auto scene = p_scene.lock();
	if (scene != nullptr) {
		Renderable::Attorney::set_scene(*p_children.back(), scene);
	}
}

void bges::Parent::remove_child(const child_type &child) {
#if __cpp_lib_erase_if >= 202002L
	if (std::erase_if(p_children, ptr_comp{child.get()}) > 0) {
        Renderable::Attorney::set_parent(*child, nullptr);
	}
#else
	auto it = std::remove_if(p_children.begin(), p_children.end(), ptr_comp{child.get()});
	if (it != p_children.end()) {
		p_children.erase(it, p_children.end());
		Renderable::Attorney::set_parent(*child, nullptr);
	}
#endif
}

void bges::Parent::bring_to_front(const child_type::element_type *render) noexcept {
    auto it = std::find_if(p_children.rbegin(), p_children.rend(), ptr_comp{render});
    if (it != p_children.rend() && it != p_children.rbegin()) {
        std::shared_ptr<Renderable> copy = std::move(*it);
        std::move_backward(p_children.rbegin(), it, std::next(it));
        *p_children.rbegin() = std::move(copy);
    }
}

void bges::Parent::bring_to_front(const std::shared_ptr<Renderable>& r) noexcept {
	bring_to_front(r.get());
}

void bges::Parent::bring_to_back(const child_type::element_type *r) noexcept {
    auto it = std::find_if(p_children.begin(), p_children.end(), ptr_comp{r});
    if (it != p_children.end() && it != p_children.begin()) {
        std::shared_ptr<Renderable> copy = std::move(*it);
        std::move_backward(p_children.begin(), it, std::next(it));
        *p_children.begin() = std::move(copy);
    }
}
void bges::Parent::bring_to_back(const std::shared_ptr<Renderable>& r) noexcept {
	bring_to_back(r.get());
}

void bges::Parent::render_child(Scene& sc, std::vector<child_type>::size_type idx, const PointF& relative_to) noexcept {
	Renderable::Attorney::render(*p_children[idx], sc, relative_to);
}


void bges::Parent::mouse_moved(const event::MouseMove& ev) {
	auto selected = find_child(p_children, {ev.x, ev.y});
	if (selected == p_hovered_child && selected != std::numeric_limits<std::size_t>::max()) {
		child_mouse_moved_within(selected, ev);
	} else {
		if (p_hovered_child != std::numeric_limits<std::size_t>::max()) {
			child_mouse_exited(p_hovered_child, {ev.x, ev.y});
			p_hovered_child = std::numeric_limits<std::size_t>::max();
		}
		if (selected != std::numeric_limits<std::size_t>::max()) {
			p_hovered_child = selected;
			child_mouse_entered(selected, {ev.x, ev.y});
		}
	}
}

void bges::Parent::mouse_exited(const event::MouseExit& ev) {
	if (p_hovered_child != std::numeric_limits<std::size_t>::max()) {
		child_mouse_exited(p_hovered_child, ev);
	}
	p_hovered_child = std::numeric_limits<std::size_t>::max();
}

void bges::Parent::mouse_entered(const event::MouseEnter& ev) {
	auto selected = find_child(p_children, {ev.x, ev.y});
	if (selected != std::numeric_limits<std::size_t>::max()) {
		p_hovered_child = selected;
		child_mouse_entered(selected, ev);
	}
}

void bges::Parent::mouse_pressed(const event::MousePress& ev) {
	if (p_hovered_child != std::numeric_limits<std::size_t>::max()) {
		child_mouse_pressed(p_hovered_child, ev);
	}
}

void bges::Parent::mouse_release(const event::MouseRelease& ev) {
	if (p_hovered_child != std::numeric_limits<std::size_t>::max()) {
		child_mouse_release(p_hovered_child, ev);
	}
}
