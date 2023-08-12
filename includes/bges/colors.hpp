#ifndef BGES_COLORS_HPP
#define BGES_COLORS_HPP

#include <cstdint>
#include <bges/details/export.hpp>

namespace bges {

struct IColor;
struct Color {
	float red{0};
	float green{0};
	float blue{0};
	float alpha{1.f};

	BGES_CPPEXPORT operator IColor() const noexcept;
};

struct IColor {
	std::uint8_t red{0};
	std::uint8_t green{0};
	std::uint8_t blue{0};
	std::uint8_t alpha{255};

	BGES_CPPEXPORT operator Color() const noexcept;
};

namespace colors {
	[[maybe_unused]] inline constexpr IColor aliceblue{0xf0, 0xf8, 0xff};
	[[maybe_unused]] inline constexpr IColor antiquewhite{0xfa, 0xeb, 0xd7};
	[[maybe_unused]] inline constexpr IColor aqua{0x00, 0xff, 0xff};
	[[maybe_unused]] inline constexpr IColor aquamarine{0x7f, 0xff, 0xd4};
	[[maybe_unused]] inline constexpr IColor azure{0xf0, 0xff, 0xff};
	[[maybe_unused]] inline constexpr IColor beige{0xf5, 0xf5, 0xdc};
	[[maybe_unused]] inline constexpr IColor bisque{0xff, 0xe4, 0xc4};
	[[maybe_unused]] inline constexpr IColor black{0x00, 0x00, 0x00};
	[[maybe_unused]] inline constexpr IColor blanchedalmond{0xff, 0xeb, 0xcd};
	[[maybe_unused]] inline constexpr IColor blue{0x00, 0x00, 0xff};
	[[maybe_unused]] inline constexpr IColor blueviolet{0x8a, 0x2b, 0xe2};
	[[maybe_unused]] inline constexpr IColor brown{0xa5, 0x2a, 0x2a};
	[[maybe_unused]] inline constexpr IColor burlywood{0xde, 0xb8, 0x87};
	[[maybe_unused]] inline constexpr IColor cadetblue{0x5f, 0x9e, 0xa0};
	[[maybe_unused]] inline constexpr IColor chartreuse{0x7f, 0xff, 0x00};
	[[maybe_unused]] inline constexpr IColor chocolate{0xd2, 0x69, 0x1e};
	[[maybe_unused]] inline constexpr IColor coral{0xff, 0x7f, 0x50};
	[[maybe_unused]] inline constexpr IColor cornflowerblue{0x64, 0x95, 0xed};
	[[maybe_unused]] inline constexpr IColor cornsilk{0xff, 0xf8, 0xdc};
	[[maybe_unused]] inline constexpr IColor crimson{0xdc, 0x14, 0x3c};
	[[maybe_unused]] inline constexpr IColor cyan = aqua;
	[[maybe_unused]] inline constexpr IColor darkblue{0x00, 0x00, 0x8b};
	[[maybe_unused]] inline constexpr IColor darkcyan{0x00, 0x8b, 0x8b};
	[[maybe_unused]] inline constexpr IColor darkgoldenrod{0xb8, 0x86, 0x0b};
	[[maybe_unused]] inline constexpr IColor darkgray{0xa9, 0xa9, 0xa9};
	[[maybe_unused]] inline constexpr IColor darkgreen{0x00, 0x64, 0x00};
	[[maybe_unused]] inline constexpr IColor darkgrey = darkgray;
	[[maybe_unused]] inline constexpr IColor darkkhaki{0xbd, 0xb7, 0x6b};
	[[maybe_unused]] inline constexpr IColor darkmagenta{0x8b, 0x00, 0x8b};
	[[maybe_unused]] inline constexpr IColor darkolivegreen{0x55, 0x6b, 0x2f};
	[[maybe_unused]] inline constexpr IColor darkorange{0xff, 0x8c, 0x00};
	[[maybe_unused]] inline constexpr IColor darkorchid{0x99, 0x32, 0xcc};
	[[maybe_unused]] inline constexpr IColor darkred{0x8b, 0x00, 0x00};
	[[maybe_unused]] inline constexpr IColor darksalmon{0xe9, 0x96, 0x7a};
	[[maybe_unused]] inline constexpr IColor darkseagreen{0x8f, 0xbc, 0x8f};
	[[maybe_unused]] inline constexpr IColor darkslateblue{0x48, 0x3d, 0x8b};
	[[maybe_unused]] inline constexpr IColor darkslategray{0x2f, 0x4f, 0x4f};
	[[maybe_unused]] inline constexpr IColor darkslategrey = darkslategray;
	[[maybe_unused]] inline constexpr IColor darkturquoise{0x00, 0xce, 0xd1};
	[[maybe_unused]] inline constexpr IColor darkviolet{0x94, 0x00, 0xd3};
	[[maybe_unused]] inline constexpr IColor deeppink{0xff, 0x14, 0x93};
	[[maybe_unused]] inline constexpr IColor deepskyblue{0x00, 0xbf, 0xff};
	[[maybe_unused]] inline constexpr IColor dimgray{0x69, 0x69, 0x69};
	[[maybe_unused]] inline constexpr IColor dimgrey = dimgray;
	[[maybe_unused]] inline constexpr IColor dodgerblue{0x1e, 0x90, 0xff};
	[[maybe_unused]] inline constexpr IColor firebrick{0xb2, 0x22, 0x22};
	[[maybe_unused]] inline constexpr IColor floralwhite{0xff, 0xfa, 0xf0};
	[[maybe_unused]] inline constexpr IColor forestgreen{0x22, 0x8b, 0x22};
	[[maybe_unused]] inline constexpr IColor fuchsia{0xff, 0x00, 0xff};
	[[maybe_unused]] inline constexpr IColor gainsboro{0xdc, 0xdc, 0xdc};
	[[maybe_unused]] inline constexpr IColor ghostwhite{0xf8, 0xf8, 0xff};
	[[maybe_unused]] inline constexpr IColor gold{0xff, 0xd7, 0x00};
	[[maybe_unused]] inline constexpr IColor goldenrod{0xda, 0xa5, 0x20};
	[[maybe_unused]] inline constexpr IColor gray{0x80, 0x80, 0x80};
	[[maybe_unused]] inline constexpr IColor green{0x00, 0x80, 0x00};
	[[maybe_unused]] inline constexpr IColor greenyellow{0xad, 0xff, 0x2f};
	[[maybe_unused]] inline constexpr IColor grey = gray;
	[[maybe_unused]] inline constexpr IColor honeydew{0xf0, 0xff, 0xf0};
	[[maybe_unused]] inline constexpr IColor hotpink{0xff, 0x69, 0xb4};
	[[maybe_unused]] inline constexpr IColor indianred{0xcd, 0x5c, 0x5c};
	[[maybe_unused]] inline constexpr IColor indigo{0x4b, 0x00, 0x82};
	[[maybe_unused]] inline constexpr IColor ivory{0xff, 0xff, 0xf0};
	[[maybe_unused]] inline constexpr IColor khaki{0xf0, 0xe6, 0x8c};
	[[maybe_unused]] inline constexpr IColor lavender{0xe6, 0xe6, 0xfa};
	[[maybe_unused]] inline constexpr IColor lavenderblush{0xff, 0xf0, 0xf5};
	[[maybe_unused]] inline constexpr IColor lawngreen{0x7c, 0xfc, 0x00};
	[[maybe_unused]] inline constexpr IColor lemonchiffon{0xff, 0xfa, 0xcd};
	[[maybe_unused]] inline constexpr IColor lightblue{0xad, 0xd8, 0xe6};
	[[maybe_unused]] inline constexpr IColor lightcoral{0xf0, 0x80, 0x80};
	[[maybe_unused]] inline constexpr IColor lightcyan{0xe0, 0xff, 0xff};
	[[maybe_unused]] inline constexpr IColor lightgoldenrodyellow{0xfa, 0xfa, 0xd2};
	[[maybe_unused]] inline constexpr IColor lightgray{0xd3, 0xd3, 0xd3};
	[[maybe_unused]] inline constexpr IColor lightgreen{0x90, 0xee, 0x90};
	[[maybe_unused]] inline constexpr IColor lightgrey = lightgray;
	[[maybe_unused]] inline constexpr IColor lightpink{0xff, 0xb6, 0xc1};
	[[maybe_unused]] inline constexpr IColor lightsalmon{0xff, 0xa0, 0x7a};
	[[maybe_unused]] inline constexpr IColor lightseagreen{0x20, 0xb2, 0xaa};
	[[maybe_unused]] inline constexpr IColor lightskyblue{0x87, 0xce, 0xfa};
	[[maybe_unused]] inline constexpr IColor lightslategray{0x77, 0x88, 0x99};
	[[maybe_unused]] inline constexpr IColor lightslategrey = lightslategray;
	[[maybe_unused]] inline constexpr IColor lightsteelblue{0xb0, 0xc4, 0xde};
	[[maybe_unused]] inline constexpr IColor lightyellow{0xff, 0xff, 0xe0};
	[[maybe_unused]] inline constexpr IColor lime{0x00, 0xff, 0x00};
	[[maybe_unused]] inline constexpr IColor limegreen{0x32, 0xcd, 0x32};
	[[maybe_unused]] inline constexpr IColor linen{0xfa, 0xf0, 0xe6};
	[[maybe_unused]] inline constexpr IColor magenta = fuchsia;
	[[maybe_unused]] inline constexpr IColor maroon{0x80, 0x00, 0x00};
	[[maybe_unused]] inline constexpr IColor mediumaquamarine{0x66, 0xcd, 0xaa};
	[[maybe_unused]] inline constexpr IColor mediumblue{0x00, 0x00, 0xcd};
	[[maybe_unused]] inline constexpr IColor mediumorchid{0xba, 0x55, 0xd3};
	[[maybe_unused]] inline constexpr IColor mediumpurple{0x93, 0x70, 0xdb};
	[[maybe_unused]] inline constexpr IColor mediumseagreen{0x3c, 0xb3, 0x71};
	[[maybe_unused]] inline constexpr IColor mediumslateblue{0x7b, 0x68, 0xee};
	[[maybe_unused]] inline constexpr IColor mediumspringgreen{0x00, 0xfa, 0x9a};
	[[maybe_unused]] inline constexpr IColor mediumturquoise{0x48, 0xd1, 0xcc};
	[[maybe_unused]] inline constexpr IColor mediumvioletred{0xc7, 0x15, 0x85};
	[[maybe_unused]] inline constexpr IColor midnightblue{0x19, 0x19, 0x70};
	[[maybe_unused]] inline constexpr IColor mintcream{0xf5, 0xff, 0xfa};
	[[maybe_unused]] inline constexpr IColor mistyrose{0xff, 0xe4, 0xe1};
	[[maybe_unused]] inline constexpr IColor moccasin{0xff, 0xe4, 0xb5};
	[[maybe_unused]] inline constexpr IColor navajowhite{0xff, 0xde, 0xad};
	[[maybe_unused]] inline constexpr IColor navy{0x00, 0x00, 0x80};
	[[maybe_unused]] inline constexpr IColor oldlace{0xfd, 0xf5, 0xe6};
	[[maybe_unused]] inline constexpr IColor olive{0x80, 0x80, 0x00};
	[[maybe_unused]] inline constexpr IColor olivedrab{0x6b, 0x8e, 0x23};
	[[maybe_unused]] inline constexpr IColor orange{0xff, 0xa5, 0x00};
	[[maybe_unused]] inline constexpr IColor orangered{0xff, 0x45, 0x00};
	[[maybe_unused]] inline constexpr IColor orchid{0xda, 0x70, 0xd6};
	[[maybe_unused]] inline constexpr IColor palegoldenrod{0xee, 0xe8, 0xaa};
	[[maybe_unused]] inline constexpr IColor palegreen{0x98, 0xfb, 0x98};
	[[maybe_unused]] inline constexpr IColor paleturquoise{0xaf, 0xee, 0xee};
	[[maybe_unused]] inline constexpr IColor palevioletred{0xdb, 0x70, 0x93};
	[[maybe_unused]] inline constexpr IColor papayawhip{0xff, 0xef, 0xd5};
	[[maybe_unused]] inline constexpr IColor peachpuff{0xff, 0xda, 0xb9};
	[[maybe_unused]] inline constexpr IColor peru{0xcd, 0x85, 0x3f};
	[[maybe_unused]] inline constexpr IColor pink{0xff, 0xc0, 0xcb};
	[[maybe_unused]] inline constexpr IColor plum{0xdd, 0xa0, 0xdd};
	[[maybe_unused]] inline constexpr IColor powderblue{0xb0, 0xe0, 0xe6};
	[[maybe_unused]] inline constexpr IColor purple{0x80, 0x00, 0x80};
	[[maybe_unused]] inline constexpr IColor rebeccapurple{0x66, 0x33, 0x99};
	[[maybe_unused]] inline constexpr IColor red{0xff, 0x00, 0x00};
	[[maybe_unused]] inline constexpr IColor rosybrown{0xbc, 0x8f, 0x8f};
	[[maybe_unused]] inline constexpr IColor royalblue{0x41, 0x69, 0xe1};
	[[maybe_unused]] inline constexpr IColor saddlebrown{0x8b, 0x45, 0x13};
	[[maybe_unused]] inline constexpr IColor salmon{0xfa, 0x80, 0x72};
	[[maybe_unused]] inline constexpr IColor sandybrown{0xf4, 0xa4, 0x60};
	[[maybe_unused]] inline constexpr IColor seagreen{0x2e, 0x8b, 0x57};
	[[maybe_unused]] inline constexpr IColor seashell{0xff, 0xf5, 0xee};
	[[maybe_unused]] inline constexpr IColor sienna{0xa0, 0x52, 0x2d};
	[[maybe_unused]] inline constexpr IColor silver{0xc0, 0xc0, 0xc0};
	[[maybe_unused]] inline constexpr IColor skyblue{0x87, 0xce, 0xeb};
	[[maybe_unused]] inline constexpr IColor slateblue{0x6a, 0x5a, 0xcd};
	[[maybe_unused]] inline constexpr IColor slategray{0x70, 0x80, 0x90};
	[[maybe_unused]] inline constexpr IColor slategrey = slategray;
	[[maybe_unused]] inline constexpr IColor snow{0xff, 0xfa, 0xfa};
	[[maybe_unused]] inline constexpr IColor springgreen{0x00, 0xff, 0x7f};
	[[maybe_unused]] inline constexpr IColor steelblue{0x46, 0x82, 0xb4};
	[[maybe_unused]] inline constexpr IColor tan{0xd2, 0xb4, 0x8c};
	[[maybe_unused]] inline constexpr IColor teal{0x00, 0x80, 0x80};
	[[maybe_unused]] inline constexpr IColor thistle{0xd8, 0xbf, 0xd8};
	[[maybe_unused]] inline constexpr IColor tomato{0xff, 0x63, 0x47};
	[[maybe_unused]] inline constexpr IColor transparent{0x00, 0x00, 0x00, 0x00};
	[[maybe_unused]] inline constexpr IColor turquoise{0x40, 0xe0, 0xd0};
	[[maybe_unused]] inline constexpr IColor violet{0xee, 0x82, 0xee};
	[[maybe_unused]] inline constexpr IColor wheat{0xf5, 0xde, 0xb3};
	[[maybe_unused]] inline constexpr IColor white{0xff, 0xff, 0xff};
	[[maybe_unused]] inline constexpr IColor whitesmoke{0xf5, 0xf5, 0xf5};
	[[maybe_unused]] inline constexpr IColor yellow{0xff, 0xff, 0x00};
	[[maybe_unused]] inline constexpr IColor yellowgreen{0x9a, 0xcd, 0x32};

} // namespace colors
} // namespace bges

#endif //BGES_COLORS_HPP
