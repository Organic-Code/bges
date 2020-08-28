#ifndef BGES_UNMANAGED_HPP
#define BGES_UNMANAGED_HPP

#include <bges/details/export.hpp>
#include <bges/base_classes/parent.hpp>

namespace bges::container {
class BGES_CPPEXPORT Unmanaged : public Parent {
public:
private:
	void as_root_of(Scene*) noexcept override;
    void set_parent(Parent*) noexcept override;
	void vrender(Scene& scene) noexcept override;
};
}

#endif //BGES_UNMANAGED_HPP
