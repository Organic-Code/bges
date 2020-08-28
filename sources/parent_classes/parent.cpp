#include <bges/base_classes/parent.hpp>

#include <algorithm>
#include <vector>

namespace {
struct ptr_comp {
	const bges::Renderable *renderable;

	bool operator()(const bges::Parent::child_type &ptr) const noexcept {
		return renderable == ptr.get();
	}

	bool operator()(const bges::Renderable *other) const noexcept {
		return renderable == other;
	}
};
} // namespace

const std::vector<bges::Parent::child_type> &bges::Parent::children() const noexcept {
	return p_children;
}

void bges::Parent::add_child(child_type c) {
	Renderable::Attorney::set_parent(*c, this);
	p_children.emplace_back(std::move(c));
}

void bges::Parent::remove_child(const child_type &c) {
#if __cpp_lib_erase_if >= 202002L
	if (std::erase_if(p_children, ptr_comp{c.get()}) > 0) {
        Renderable::Attorney::set_parent(*c, nullptr);
	}
#else
	auto it = std::remove_if(p_children.begin(), p_children.end(), ptr_comp{c.get()});
	if (it != p_children.end()) {
		p_children.erase(it, p_children.end());
		Renderable::Attorney::set_parent(*c, nullptr);
	}
#endif
}

void bges::Parent::bring_to_front(const Renderable *r) noexcept {
    auto it = std::find_if(p_children.rbegin(), p_children.rend(), ptr_comp{r});
    if (it != p_children.rend() && it != p_children.rbegin()) {
        std::shared_ptr<Renderable> copy = std::move(*it);
        std::move_backward(p_children.rbegin(), it, std::next(it));
        *p_children.rbegin() = std::move(copy);
    }
}

void bges::Parent::bring_to_back(const Renderable *r) noexcept {
    auto it = std::find_if(p_children.begin(), p_children.end(), ptr_comp{r});
    if (it != p_children.end() && it != p_children.begin()) {
        std::shared_ptr<Renderable> copy = std::move(*it);
        std::move_backward(p_children.begin(), it, std::next(it));
        *p_children.begin() = std::move(copy);
    }
}

void bges::Parent::bring_to_front(const std::shared_ptr<Renderable>& r) noexcept {
	bring_to_front(r.get());
}
void bges::Parent::bring_to_back(const std::shared_ptr<Renderable>& r) noexcept {
	bring_to_back(r.get());
}

void bges::Parent::render_child(Scene& sc, std::vector<child_type>::size_type idx) noexcept {
	Renderable::Attorney::render(*p_children[idx], sc);
}
