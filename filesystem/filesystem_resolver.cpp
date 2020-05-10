#include "filesystem_resolver.hpp"

namespace pixl::fs
{
	file_traits filesystem_resolver::resolve(const std::string& path)
	{
		set_target(path);
		file_traits traits;

		traits.is_file = is_file();
		traits.is_directory = is_directory();
		traits.is_valid = is_valid();
		traits.can_be_written = writeable();
		traits.can_be_read = readable();
		traits.can_be_created = createable();
		traits.exists = exists();
		return traits;
		
	}

	void filesystem_resolver::set_target(const std::string& target)
	{
		m_target = target;
	}

	char filesystem_resolver::get_delimiter() const noexcept
	{
		return '/';
	}

	void memory_filesystem_resolver::set_data(byte_vector* b)
	{
		data = b;
	}

	byte_vector& memory_filesystem_resolver::get_data() const
	{
		return *data;
	}

	bool memory_filesystem_resolver::has_data() const
	{
		return data;
	}

	bool memory_filesystem_resolver::request_artifact_data(byte_vector&) const
	{
	}

	bool memory_filesystem_resolver::set_artifact_data(const byte_vector&) const
	{
	}
}
