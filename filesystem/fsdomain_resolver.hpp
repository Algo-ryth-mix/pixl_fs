#ifndef PIXL_FS_FSDOMAIN_RESOLVER_HPP
#define PIXL_FS_FSDOMAIN_RESOLVER_HPP
#include <string>
#include <utility>
#include <vector>



#include "common/result.hpp"
#include "filesystem_resolver.hpp"

namespace pixl::fs
{
	class fsdomain_resolver
	{
	public:
		fsdomain_resolver(std::string path) : m_path(std::move(path)){};

		using solution = std::vector<std::pair<filesystem_resolver*,std::string>>;

		[[nodiscard]] common::result<solution,const char *> find_solution(const std::string& opt_root_domain = "") const;

	private:
		std::string m_path;
	};
}
#endif
