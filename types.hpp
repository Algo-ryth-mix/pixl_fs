#ifndef PIXL_FILESYSTEM_REQUIRED_TYPES_HPP
#define PIXL_FILESYSTEM_REQUIRED_TYPES_HPP

//begin contract
//has common/basic_resource


//end contract

//begin types

//begin byte:uint8_t
#include <cstdint>
#include <cstddef>
namespace pixl{using byte = std::uint8_t;}
//end byte:uint8_t

//begin byte_vector:std::vector<pixl::byte>
#include <vector>
namespace pixl{using byte_vector=std::vector<pixl::byte>;}
//end byte_vector:std::vector<pixl::byte>

//end types



#endif