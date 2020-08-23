#ifndef BGES_COMMON_EXPORT_SYMBOL_H
#define BGES_COMMON_EXPORT_SYMBOL_H

#if defined OS_WINDOWS
#	define BGES_CALL_CONVENTION
#	if defined __cplusplus
#		define BGES_EXPORT_SYMBOL extern "C" __declspec(dllexport)
#	else
#		define BGES_EXPORT_SYMBOL __declspec(dllexport)
#	endif
#elif defined OS_LINUX
#	define BGES_CALL_CONVENTION
#	if defined __cplusplus
#		define BGES_EXPORT_SYMBOL extern "C" __attribute__((visibility("default")))
#	else
#		define BGES_EXPORT_SYMBOL __attribute__((visibility("default")))
#	endif
#endif

#endif //BGES_COMMON_EXPORT_SYMBOL_H
