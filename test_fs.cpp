#include <common/basic_resource.hpp>
#include <iostream>


#include "filesystem/filesystem_view.hpp"
#include "filesystem/provider_registry.hpp"

class Serializable
{
public:

	Serializable(std::string string) : m_string(std::move(string)){}

	Serializable(const Serializable& other) = default;
	Serializable(Serializable&& other) noexcept = default;
	Serializable& operator=(const Serializable& other) = default;
	Serializable& operator=(Serializable&& other) noexcept = default;

	static void to_resource(pixl::common::basic_resource* resource,const Serializable& value)
	{
		(*resource) = value.m_string;
	}

	static void from_resource(Serializable* value, const pixl::common::basic_resource& resource)
	{
		value->m_string = resource.to_string();
	}

	std::string& get()
	{
		return m_string;
	}
	
private:
	std::string m_string;
};


class test_resolver : public pixl::fs::memory_filesystem_resolver
{
public:

	bool is_file() override{ return false;}
	bool is_directory() override{ return false;}
	bool is_valid() override{ return false;}
	bool writeable() override{ return false;}
	bool readable() override{ return false;}
	bool createable() override{ return false;}
	bool exists() override{ return false;}
	pixl::common::basic_resource get() override{ throw std::runtime_error("not implemented!");}
	bool set(const pixl::common::basic_resource&) override{ throw std::runtime_error("not implemented!");}
};
class tld_resolver : public pixl::fs::filesystem_resolver
{
public:
	bool is_file() override{ return false;}
	bool is_directory() override{ return false;}
	bool is_valid() override{ return false;}
	bool writeable() override{ return false;}
	bool readable() override{ return false;}
	bool createable() override{ return false;}
	bool exists() override{ return false;}
	pixl::common::basic_resource get() override{ throw std::runtime_error("not implemented!");}
	bool set(const pixl::common::basic_resource&) override{ throw std::runtime_error("not implemented!");}
};

int main()
{
	using namespace pixl;


	
	pixl::fs::provider_registry::domain_create_resolver<test_resolver>(".test");
	pixl::fs::provider_registry::domain_create_resolver<tld_resolver>("toplevel");

	pixl::fs::provider_registry::has_domain("virtual");
	pixl::fs::provider_registry::has_domain(".pp");
	common::basic_resource resource(nullptr);

	resource = "Hello World";

	std::cout << fs::filesystem_view::validate_domains("toplevel://this_is_a.test/file.png") << std::endl; 
	std::cout << fs::filesystem_view::validate_domains("toplevel://this_is_a.fuck/file.png") << std::endl; 
	
	std::cout << resource.to_string() << std::endl;

	auto s = common::from_resource<Serializable>(resource,"");

	std::cout << s.get() << std::endl;
 
	
}
