#ifndef PIXL_COMMON_DETAIL_CAN_CONVERT_HPP
#define PIXL_COMMON_DETAIL_CAN_CONVERT_HPP
#include <type_traits>

namespace pixl::common
{
		template<typename,typename T>
		struct has_to_resource
		{
			static_assert(
				std::integral_constant<T,false>::value,
				"Second template param needs to be of function type.");
		};

		template <typename C,typename Ret,typename... Args>
		struct has_to_resource<C,Ret(Args...)>
		{
		private:
			template<typename T>
			static constexpr auto check(T*)
				-> typename std::is_same<decltype(std::declval<T>().to_resource(std::declval<Args>()... )),Ret>::type;

			template <typename>
			static constexpr auto check(...)
				-> std::false_type;

			typedef decltype(check<C>(nullptr)) type;
		public:
			static constexpr bool value = type::value;
		};

		template<typename,typename T>
		struct has_from_resource
		{
			static_assert(
				std::integral_constant<T,false>::value,
				"Second template param needs to be of function type.");
		};

		template <typename C,typename Ret,typename... Args>
		struct has_from_resource<C,Ret(Args...)>
		{
		private:
			template<typename T>
			static constexpr auto check(T*)
				-> typename std::is_same<decltype(std::declval<T>().from_resource(std::declval<Args>()... )),Ret>::type;

			template <typename>
			static constexpr auto check(...)
				-> std::false_type;

			typedef decltype(check<C>(nullptr)) type;
		public:
			static constexpr bool value = type::value;
		};
	
}
#endif