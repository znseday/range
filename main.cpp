#include <range/v3/all.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>

#include "my_aux.h"

using namespace std;

int main()
{
	// This example from our class isn't compiled on VS 2019 !!!!!
	//const std::string s{ "hello" };
	//ranges::for_each(s | ranges::view::filter([](auto c) { return c == 'l'; }), [](auto i) { std::cout << i << std::endl; });

	vector<ipType> ips;

#if (defined WIN32) || (defined WIN64)
	vector<int> tv = { 2, 0, 1 };
	//ranges::copy(tv, ostream_iterator<int>(cout));  // doesn't work even for <int>. Why ???
	std::copy(tv.cbegin(), tv.cend(), ostream_iterator<int>(cout));
	cout << endl;
	ranges::sort(tv);  // Just to be sure that Range is visible and works
	std::copy(tv.cbegin(), tv.cend(), ostream_iterator<int>(cout));
	cout << endl;

	std::cout << "Home work, version: " << MyVersion() << std::endl << std::endl; // for debugging

	std::istream & i_stream = std::ifstream("ip_filter.tsv"); // doesn't work if "/permissive-" is included as an option(( Why???
	if (!i_stream)
	{
		std::cout << "My error: the input file not found" << std::endl;
		exit(0);
	}
#else
	istream& i_stream = cin;
#endif

	std::string line;
	while (getline(i_stream, line))
		ips.push_back(ConvertLineToIP(line));

	ranges::sort(ips, std::greater<ipType>()); // lex sort

	//ranges::copy(ips, std::ostream_iterator<ipType>(std::cout));                       // isn't compiled !
	//ranges::copy(ips.cbegin(), ips.cend(), std::ostream_iterator<ipType>(std::cout));  // isn't compiled !

	for (auto it = ips.cbegin(); it != ips.cend(); ++it) // Added, cos std::copy doesn't work any more !
		std::cout << *it;

	//copy(ips.cbegin(), ips.cend(), ostream_iterator<ipType>(cout)); // How to make it work?


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
			//if (std::any_of((*it).cbegin(), (*it).cend(), [byte](BYTE val) {return val == byte; }))
				std::cout << *it;
	};
	LambdaFilterAny((BYTE)46);

    return 0;
}
