#include <range/v3/all.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <string>

#include "my_aux.h"

using namespace std;

//using namespace ranges;

int main()
{
	// This example from our lesson works ONLY on Range 0.5 (0.4 and 0.9 don't work on VS 2019!)
	// const std::string s{ "hello" };
	// ranges::for_each(s | ranges::view::filter([](auto c) { return c == 'l'; }), [](auto i) { std::cout << i << std::endl; });

	vector<ipType> ips;
	string line;

#if (defined WIN32) || (defined WIN64)

	std::cout << "Home work, version: " << MyVersion() << std::endl << std::endl; // for debugging

	//std::istream& i_stream = std::ifstream("ip_filter.tsv"); // doesn't work if "/permissive-" is included as an option(( Why???

	std::ifstream i_stream("ip_filter.tsv"); //  "/permissive-" forced me to write it like this
	if (!i_stream)
	{
		std::cout << "My error: the input file not found" << std::endl;
		exit(0);
	}

	while (getline(i_stream, line))
		ips.push_back(ConvertLineToIP(line));

#else
	istream& i_stream = cin;
	while (getline(cin, line))
		ips.push_back(ConvertLineToIP(line));
#endif

	//while (getline(i_stream, line))       // This universal version doesn't work any more (((
	//	ips.push_back(ConvertLineToIP(line));

	ranges::sort(ips, greater<ipType>()); // lex sort

	ranges::copy(ips, ranges::ostream_iterator<ipType>(cout));// Warning C26444	Avoid unnamed objects with custom construction and destruction (es.84). 
	// This warning appears even for simple int (see tests). What to do with that?

	//for (auto it = ips.cbegin(); it != ips.cend(); ++it) // Now, it's used "ranges::copy" instead
	//	std::cout << *it;

	auto LambdaFilterByBytes = [&ips](auto... params)
	{
		ipType a { (params)... };
		const int argc = sizeof...(params);
		for (int i = argc; i < 4; i++)
			a.push_back(0);  // for lower_bound

		ipType b { (params)... };
		for (int i = argc; i < 4; i++)
			b.push_back(255); // for upper_bound

		auto it_l = ranges::lower_bound(ips, a, std::greater<ipType>());
		auto it_u = ranges::upper_bound(ips, b, std::greater<ipType>());

		//std::cout << "--------------------" << std::endl; 
		//std::cout << *it_l;   // for debugging
		//std::cout << *it_u;   // for debugging
		//std::cout << "--------------------" << std::endl;

		for (; it_l != it_u; ++it_u)
			std::cout << *it_u;
	};

	LambdaFilterByBytes((BYTE)1);

	//cout << "------------------------------------------------------" << endl;
	LambdaFilterByBytes((BYTE)46, (BYTE)70);
	//cout << "------------------------------------------------------" << endl;

	auto LambdaFilterAny = [&ips](BYTE byte)
	{
		for (auto it = ips.cbegin(); it != ips.cend(); ++it)
			if (ranges::any_of( (*it), [byte](BYTE val) {return val == byte; }))
				std::cout << *it;
	};
	LambdaFilterAny((BYTE)46);

    return 0;
}
