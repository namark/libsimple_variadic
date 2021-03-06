#ifndef SIMPLE_SUPPORT_FUNCTION_UTILS_HPP
#define SIMPLE_SUPPORT_FUNCTION_UTILS_HPP
#include <type_traits>
#include <tuple>

namespace simple { namespace support
{

	template <typename Function>
	struct fun_signature;

	template <typename ReturnType, typename... ArgumentType>
	struct fun_signature<ReturnType(ArgumentType...)>
	{
		using return_type = ReturnType;
		using argument_type = std::tuple<ArgumentType...>;
	};

	template <typename Function, int param_index = 0>
	struct fun_param
	{
		using type = std::tuple_element_t<param_index, typename fun_signature<Function>::argument_type>;
	};

	template <typename Function, int param_index = 0>
	using fun_param_t = typename fun_param<Function, param_index>::type;

	template <typename Function>
	using fun_return_t = typename fun_signature<Function>::return_type;

	template <typename ReturnType, typename... ArgumentType>
	inline constexpr ReturnType nop(ArgumentType...) {}

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

	// std::invoke is not constexpr, until c++20 -_-
	template< class F, class... Args>
	constexpr std::invoke_result_t<F, Args...>
	invoke(F&& f, Args&&... args)
	noexcept(std::is_nothrow_invocable_v<F,Args...>)
	{
		return std::apply(std::forward<F>(f),
			std::forward_as_tuple(std::forward<Args>(args)...));
	}

}} // namespace simple.support

#endif /* end of include guard */
