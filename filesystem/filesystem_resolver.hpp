#ifndef PIXL_FS_FILESYSTEM_RESOLVER_HPP
#define PIXL_FS_FILESYSTEM_RESOLVER_HPP
#include <string>


#include "common/basic_resource.hpp"
#include "detail/meta.hpp"
#include "file_traits.hpp"
#include "types.hpp"

namespace pixl::fs
{
	class filesystem_resolver : public filesystem_resolver_common_base
	{
	public:
		filesystem_resolver() = default;
		filesystem_resolver(const filesystem_resolver& other) = default;
		filesystem_resolver(filesystem_resolver&& other) noexcept = default;
		filesystem_resolver& operator=(const filesystem_resolver& other) = default;
		filesystem_resolver& operator=(filesystem_resolver&& other) noexcept = default;
		virtual ~filesystem_resolver() = default;


		file_traits resolve(const std::string& path);;

		void set_target(const std::string& target);

		virtual bool is_file()			= 0;
		virtual bool is_directory()		= 0;
		virtual bool is_valid()			= 0;
		virtual bool writeable()		= 0;
		virtual bool readable()			= 0;
		virtual bool createable()		= 0;
		virtual bool exists()			= 0;

		virtual common::basic_resource get() = 0;
		virtual bool set(const common::basic_resource&) = 0;


		
		[[nodiscard]] virtual char get_delimiter() const noexcept;

	protected:
		std::string m_target;
		
		
	};

	class memory_filesystem_resolver : public filesystem_resolver , public memory_resolver_common_base
	{
	public:

		
		virtual ~memory_filesystem_resolver() = default;
		virtual bool ready_to_read() = 0;
		void set_data(byte_vector* b);
	protected:
		[[nodiscard]] byte_vector& get_data() const;
		[[nodiscard]] bool has_data() const;

		
		bool request_artifact_data(byte_vector&) const;
		bool set_artifact_data(const byte_vector&) const;
		
	private:
		byte_vector* data = nullptr;
	};


}
#endif
