#ifndef SIMPLE_SUPPORT_ALGORITHM_HPP
#define SIMPLE_SUPPORT_ALGORITHM_HPP
#include <iterator>

#include "range.hpp"

namespace simple::support
{

	template <typename Itr, typename Num = int>
	constexpr Itr next_number(Itr begin, Itr end, Num base = 2)
	{
		while(begin != end)
		{
			++(*begin);
			if(*begin < base)
				break;
			*begin = 0;
			++begin;
		}
		return begin;
	}

	template <typename Range, typename Num = int>
	constexpr auto next_number(Range& range, Num base = 2)
	{
		using std::begin;
		using std::end;
		return next_number(begin(range), end(range), base);
	}

	template <typename Itr, typename Num = int>
	constexpr Itr prev_number(Itr begin, Itr end, Num base = 2)
	{
		while(begin != end)
		{
			--(*begin);
			if(*begin >= 0)
				break;
			*begin = base - 1;
			++begin;
		}
		return begin;
	}

	template <typename Range, typename Num = int>
	constexpr auto prev_number(Range& range, Num base = 2)
	{
		using std::begin;
		using std::end;
		return prev_number(begin(range), end(range), base);
	}


	template <typename Container>
	constexpr auto make_range(Container& container)
	{
		using std::begin;
		using std::end;
		return make_range(begin(container), end(container));
	}

	template <typename Container>
	constexpr auto make_range(Container&& container) = delete;

	template <typename Container>
	constexpr auto reverse_range(Container& container)
	{
		using std::rbegin;
		using std::rend;
		return make_range(rbegin(container), rend(container));
	}

	template <typename Container>
	constexpr auto reverse_range(Container&& container) = delete;


	template<typename Index = std::size_t, typename Container>
	constexpr
	auto get_iterator_range(Container&& container, const range<Index>& index_range)
	{
		using std::begin;
		using std::end;
		return make_range(std::forward<Container>(container)).sub_range(index_range);
	}

} // namespace simple::support

#endif /* end of include guard */
