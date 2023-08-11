#include <bges/base_classes/parent.hpp>

#include <algorithm>
#include <vector>

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

const std::vector<bges::Parent::child_type> &bges::Parent::children() const noexcept {
	return p_children;
}

void bges::Parent::add_child(child_type c) {
	assert(std::find(p_children.begin(), p_children.end(), c) == p_children.end() && "Cannot add the same child multiple times");
	Renderable::Attorney::set_parent(*c, this);
	p_children.emplace_back(std::move(c));
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

void bges::Parent::set_child_pos(std::vector<child_type>::size_type idx, const bges::PointF &pos) noexcept {
	Renderable::Attorney::set_pos(*p_children[idx], pos);
}

void bges::Parent::render_child(Scene& sc, std::vector<child_type>::size_type idx, const PointF& relative_to) noexcept {
	Renderable::Attorney::render(*p_children[idx], sc, relative_to);
}
