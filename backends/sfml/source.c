#include "common/exchanged_types.h"
#include "common/export_symbol.h"

BGES_EXPORT_SYMBOL bges_version bgesbe_version(bges_version front_end_version) {
	return front_end_version;
}

BGES_EXPORT_SYMBOL void bgesbe_call_table(bges_version front_end_version, /* out */ fn_ptr *call_table) {
}