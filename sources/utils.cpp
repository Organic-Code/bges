#include <common/exchanged_types.h>

#include <bges/colors.hpp>

#include "utils.hpp"

bges_ffi::bges_color bges::foreign_color(const Color& color) {
	return {color.red, color.green, color.blue, color.alpha};
}