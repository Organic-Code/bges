#ifndef BGES_DETAILS_EXPORT_HPP
#define BGES_DETAILS_EXPORT_HPP

#if defined OS_WINDOWS
#	define BGES_CPPEXPORT __declspec(dllexport)
#elif defined OS_LINUX
#	define  BGES_CPPEXPORT __attribute__((visibility("default")))
#else
#	define BGES_CPPEXPORT
#endif

#endif //BGES_DETAILS_EXPORT_HPP
