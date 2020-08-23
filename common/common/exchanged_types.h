#ifndef BGES_COMMON_EXCHANGED_TYPES_H
#define BGES_COMMON_EXCHANGED_TYPES_H

#if defined __cplusplus
#	include <cstdint>
#else
#	include <stdint.h>
#endif

typedef void (*fn_ptr)();

typedef struct {
	uint8_t major; // any source changes introducing  breaking changes to the API
	uint8_t minor; // any source changes that modify the API in a backward-compatible way
	uint8_t patch; // any source changes that do not modify the API
} bges_version;

#endif //BGES_COMMON_EXCHANGED_TYPES_H
