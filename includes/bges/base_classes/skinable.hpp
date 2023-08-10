#ifndef BGES_BASE_CLASSES_SKINABLE_HPP
#define BGES_BASE_CLASSES_SKINABLE_HPP

#include <memory>
#include <utility>

namespace bges {

template <typename> class Skin;

template <typename SkinnedClass>
class Skinable {

	virtual void set_skin(std::shared_ptr<Skin<SkinnedClass>> new_skin) noexcept {
		p_skin = std::move(new_skin);
	}

protected:
	std::shared_ptr<Skin<SkinnedClass>> p_skin{};
};
} // namespace bges

#endif //BGES_BASE_CLASSES_SKINABLE_HPP
