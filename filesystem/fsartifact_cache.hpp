#ifndef PIXL_FS_FSARTIFACT_CACHE_HPP
#define PIXL_FS_FSARTIFACT_CACHE_HPP

namespace pixl::fs
{
	class fsartifact_cache
	{
	public:
		static void set_artifact();
		static void request_artifact();


	private:

		static fsartifact_cache& get_driver();
		
		
	};
}
#endif