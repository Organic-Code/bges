#include <iostream>

#include "common/export_symbol.h"

BGES_EXPORT_SYMBOL int dummy() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
