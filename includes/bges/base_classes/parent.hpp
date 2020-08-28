#ifndef BGES_BASE_CLASSES_PARENT_HPP
#define BGES_BASE_CLASSES_PARENT_HPP

#include <memory>
#include <vector>

#include <bges/details/export.hpp>
#include <bges/base_classes/renderable.hpp>
#include <bges/base_classes/event_publishers.hpp>

namespace bges {
class BGES_CPPEXPORT Parent: public Renderable, public event_publisher::MouseEvents<Parent> {
public:
	enum class clipping_policy {
		no_clipping,
		clip_to_parent
	};

	using child_type = std::shared_ptr<Renderable>;

	[[nodiscard]] const std::vector<child_type> &children() const noexcept;
    void add_child(child_type);
    void remove_child(const child_type &); // todo: also document complexity

    void bring_to_front(const Renderable *) noexcept;
    void bring_to_back(const Renderable *) noexcept;

    void bring_to_front(const std::shared_ptr<Renderable>&) noexcept;
    void bring_to_back(const std::shared_ptr<Renderable>&) noexcept;

	struct Attorney {
		static void as_root_of(Parent& p, Scene* scene) {
			p.as_root_of(scene);
		}
		friend class Scene;
	};

protected:
	virtual void as_root_of(Scene*) = 0;
    void render_child(Scene&, std::vector<child_type>::size_type idx) noexcept;
    std::vector<child_type> p_children;

};
} // namespace bges

#endif //BGES_BASE_CLASSES_PARENT_HPP
