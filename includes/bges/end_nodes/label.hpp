#ifndef BGES_END_NODES_LABEL_HPP
#define BGES_END_NODES_LABEL_HPP

#include <bges/base_classes/renderable.hpp>
#include <bges/colors.hpp>
#include <bges/geometry.hpp>

#include <string>

namespace bges {

class BGES_CPPEXPORT Label : public Renderable {
public:

	Label(std::string_view txt) : text(txt) {}
	Label() noexcept = default;
	Label(const Label&) = default;
	Label(Label&&) noexcept = default;
	Label& operator=(const Label&) = default;
	Label& operator=(Label&&) noexcept = default;
	~Label() override = default;

	PointI pos{};
	Color color{};
	bool outline{false};
	std::string text{};

	// TODO: font

protected:
	void vrender(Scene& scene, const PointF& relative_to) noexcept override;
};

} // namespace bges

#endif //BGES_END_NODES_LABEL_HPP
