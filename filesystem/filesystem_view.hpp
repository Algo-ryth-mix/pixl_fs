#ifndef PIXL_FS_FILESYSTEM_VIEW_HPP
#define PIXL_FS_FILESYSTEM_VIEW_HPP
#include "fsdomain_resolver.hpp"

namespace pixl::fs
{
	class filesystem_view
	{
	public:
		static bool validate_domains(const std::string& path)
		{
			auto res = fsdomain_resolver(path).find_solution();
			return (res.valid());
		}


		
	};
}

#endif