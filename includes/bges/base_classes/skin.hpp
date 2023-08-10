#ifndef BGES_BASE_CLASSES__SKIN_HPP
#define BGES_BASE_CLASSES__SKIN_HPP

namespace bges {

class Scene;

/**
 * The Skin class allows for one to replace the default rendering of some classes (like bges::Button) and implement a custom one.
 * @tparam SkinnedClass class who is going to have its rendering replaced
 *
 * @note inherit this class, do not specialize it.
 */
template <typename SkinnedClass>
class Skin {
private:
	virtual void render(Scene&, const typename SkinnedClass::SkinData& data) noexcept = 0;
	friend SkinnedClass;
};

}  // namespace bges

#endif //BGES_BASE_CLASSES__SKIN_HPP
