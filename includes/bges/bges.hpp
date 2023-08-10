#ifndef BGES_BGES_HPP
#define BGES_BGES_HPP

#include <filesystem>
#include <bges/details/export.hpp>


namespace bges {

/**
 * Initializes the library
 * @param library_path path to the dynamic library to use as a bges back-end. May be empty if the library was statically linked
 * @return true on successful init, false otherwise
 */
BGES_CPPEXPORT bool init(const std::filesystem::path& library_path = {});

/**
 * @return true if bges was initialized
 */
BGES_CPPEXPORT bool is_init();

}  // namespace bges

#endif //BGES_BGES_HPP
