
#include "fsdomain_resolver.hpp"


#include "common/result.hpp"
#include "common/string_extra.hpp"
#include "provider_registry.hpp"

namespace pixl::fs{
	common::result<fsdomain_resolver::solution,const char *> fsdomain_resolver::find_solution(const std::string& opt_root_domain) const
	{
		using common::Err, common::Ok;
		std::string root_domain;
		std::string to_process; 

		
		if(!opt_root_domain.empty()){
			root_domain = opt_root_domain;
			to_process = m_path;
		} else {
			//find root domain
			//the syntax for inline root-domains has to be <root-domain>:(/\\)+ <rest-of-the-path> (minus the angle-brackets of course)
			const auto rdindex  = m_path.find_first_of(':');
			if(rdindex == std::string::npos) return Err("invalid syntax for path string, no domain delimiter :");
			root_domain = m_path.substr(0,rdindex);

			//find the rest of the path ... technically this will resolve //////////lol/test.bin to lol/test.bin just fine,
			//but hopefully no one is actually insane enough to mess with such paths
			//
			//if he/she does, congrats you found a ... "feature"
			const auto pindex = m_path.find_first_not_of("/\\",rdindex+1);
			if(pindex == std::string::npos) return Err("invalid syntax for path string, last domain delimiter beyond end");
			
			to_process = m_path.substr(pindex,std::string::npos);	
		}

		if(root_domain.empty() || to_process.empty()) return Err("invalid syntax for path string, one or more properties empty");

		if(!provider_registry::has_domain(root_domain)) return Err("runtime error, no such domain");

		
		solution steps{};
		auto tokens = common::split_string_at<'\\','/'>(to_process);

		std::string previous_domain = root_domain;
		std::string domain = root_domain;

		filesystem_resolver* resolver;
		std::string path_for_resolver;

		//get first resolver
		//TODO support multiple resolvers 
		resolver = *provider_registry::domain_get_first_resolver(domain);
		
		for(auto token : tokens)
		{

			if(previous_domain != domain)
			{
				previous_domain = domain;

				if(!provider_registry::has_domain(domain)) return Err(("domain could not be resolved!, cannot continue. unknown domain: " + domain).c_str());

				//add resolver step
				steps.emplace_back(resolver,path_for_resolver);

				//get new resolver
				resolver = *provider_registry::domain_get_first_resolver(domain);
				if(!dynamic_cast<memory_filesystem_resolver*>(resolver)) return Err("the requested resolver is not a memory resolver. sub domain resolvers can only be memory resolvers!");
			}

			if(token.find('.') != std::string::npos)
			{
				//assign new domain (note if this is the last token, the last domain is technically going to be wrong, but since it is never processed nothing happens!
				domain = token.substr(token.find_first_of('.'),std::string::npos);

				//the file itself is still part of the old resolver
				//i.e.: /sandbox/assets/archive.pp.xz -> directory_in_archive/file.png
				//where the new domain is ".pp.xz"
				path_for_resolver += token;
			}
			else
			{
				path_for_resolver += token + resolver->get_delimiter();
			}
			
			
		}

		return Ok(steps);
	}
}
