#ifndef PIXL_FS_FILE_TRAITS_HPP
#define PIXL_FS_FILE_TRAITS_HPP
namespace  pixl::fs
{
	struct file_traits
	{
		bool is_file{};
		bool is_directory{};
		bool is_valid{};

		bool can_be_written{};
		bool can_be_read{};
		bool can_be_created{};

		bool exists{};
		
	};
}
#endif