#include "simple/support/rational.hpp"

using simple::support::rational;

constexpr bool Ratio()
{
	static_assert(int(10 * rational{1,2}) == 5);
	static_assert(int(9 * rational{1,2}) == 4);
	static_assert(double(9 * rational{1.0,2.0}) == 4.5);
	static_assert(int(rational{1,3} * 9) == 3);
	static_assert(int(rational{1,3} * rational{5,2} * 12) == 10);
	static_assert(int(13 * rational{5,2} * rational{2,5}) == 13);

	bool assertion = true;

	auto ratio = rational{1,2};
	assertion &= int(ratio) == 0;
	ratio *= 2;
	assertion &= int(ratio) == 1;
	ratio *= 3;
	assertion &= int(ratio) == 3;
	ratio *= rational{1,2};
	assertion &= int(ratio) == 1;
	ratio *= 5;
	assertion &= int(ratio) == 7;
	ratio *= 2;
	assertion &= int(ratio) == 15;

	return assertion;
}

int main()
{
	static_assert(Ratio());
	return 0;
}
