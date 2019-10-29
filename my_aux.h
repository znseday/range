#pragma once

#include <iostream>
#include <string>
#include <vector>

// Added this cos Travis doesn't work without it in this file (doesn't see "ranges::equal")
// But in VS it works without "#include" (it's logical cos "ranges::equal" is in a template)
#include <range/v3/all.hpp>

int MyVersion();

// !!! I intentionally use "std::" because it's a header !!!

using BYTE = unsigned char;

using ipType = std::vector<BYTE>;

[[deprecated("It's for an old version when boost tests didn't work")]]
void MyRangeTest(std::vector<int>& v); // for debugging

namespace std // "namespace std" added, but is it ok to do that???
{
	std::ostream& operator<<(std::ostream& s, const ipType& ob);
}

ipType ConvertLineToIP(const std::string &str);

//                           // ! for an old linearic version !
template<typename... Args>
[[deprecated ("It's for an old linearic version")]] // Just to use "attribute: deprecated" :)
void FilterByBytes(std::ostream& s, ipType ip, Args... args)
{
	ipType a = { (args)... }; 

	if (ranges::equal(a, ip.cbegin())) // instead of std::equal
		s << ip;
}
