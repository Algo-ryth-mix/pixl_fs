#ifndef PIXL_COMMON_BASIC_RESOURCE_HPP
#define PIXL_COMMON_BASIC_RESOURCE_HPP
#define PIXL_HAS_COMMON_BASIC_RESOURCE
#include <string>

#include "common/detail/can_convert.hpp"
#include "types.hpp"

namespace pixl::common
{

	class basic_resource
	{
	public:
		explicit basic_resource(nullptr_t) : m_container{}{}
		explicit basic_resource(pixl::byte_vector v) : m_container(std::move(v)) {}
		explicit basic_resource(const std::string& v)
		{
			m_container.assign(v.begin(), v.end());
		}

		
		basic_resource(const basic_resource& other) = default;
		basic_resource(basic_resource&& other) noexcept = default;
		basic_resource& operator=(const basic_resource& other) = default;
		basic_resource& operator=(basic_resource&& other) noexcept = default;

		[[nodiscard]] auto begin() noexcept
		{
			return m_container.begin();
		}

		[[nodiscard]] auto end() noexcept
		{
			return m_container.end();
		}

		[[nodiscard]] auto data() noexcept
		{
			return m_container.data();
		}

		[[nodiscard]] auto begin() const noexcept
		{
			return m_container.begin();
		}

		[[nodiscard]] auto end() const noexcept
		{
			return m_container.end();
		}

		[[nodiscard]] auto data() const noexcept
		{
			return m_container.data();
		}
		
		[[nodiscard]] auto size() const noexcept
		{
			return m_container.size();
		}
		[[nodiscard]] auto empty() const noexcept
		{
			return m_container.empty();
		}

		[[nodiscard]] pixl::byte_vector& get() noexcept
		{
			return m_container;
		}

		[[nodiscard]] const pixl::byte_vector& get() const noexcept
		{
			return m_container;
		}
		
		basic_resource& operator=(const std::string& value)
		{
			m_container.assign(value.begin(),value.end());
			return *this;
		}
		

		[[nodiscard]] std::string to_string() const
		{
			auto cstr = reinterpret_cast<const char*>(data());
			return std::string(cstr,size());
		}

	private:
		pixl::byte_vector m_container;
	};

	template <	typename T,
				typename = std::enable_if<has_to_resource<T,void(basic_resource*,const T&)>::value>>
	void to_resource(basic_resource* resource,const T& value)
	{
		T::to_resource(resource,value);
	}

	template <	typename T,
				typename = std::enable_if<has_to_resource<T,void(basic_resource*,const T&)>::value>>
	basic_resource to_resource(const T& value)
	{
		basic_resource res(nullptr);
		T::to_resource(&res,value);
		return res;
	}
	

	template <	typename T,
				typename = std::enable_if<has_from_resource<T,void(T*,const basic_resource&)>::value>>
	void from_resource(T* value, const basic_resource& resource)
	{
		T::from_resource(value,resource);
	}
	template <	typename T,
				typename = std::enable_if<has_from_resource<T,void(T*,const basic_resource&)>::value>,
				typename = std::enable_if<std::is_default_constructible<T>::value>,
				typename = std::enable_if<std::is_move_constructible<T>::value>>
	T from_resource(const basic_resource& resource)
	{
		T value;
		T::from_resource(&value,resource);
		return std::move(value);
	}
		template <	typename T,
				typename = std::enable_if<has_from_resource<T,void(T*,const basic_resource&)>::value>,
				typename = std::enable_if<std::is_move_constructible<T>::value>,
				class ... Args>
	T from_resource(const basic_resource& resource,Args&&... args)
	{
		T value(std::forward<Args>(args)...);
		T::from_resource(&value,resource);
		return std::move(value);
	}
	
}

#endif