#pragma once

#include <iostream>
#include <string>
#include <vector>

int MyVersion();

// !!! I intentionally use "std::" because it's a header !!!

using BYTE = unsigned char;

using ipType = std::vector<BYTE>;

void MyRangeTest(std::vector<int>& v); // for debugging

std::ostream& operator<<(std::ostream& s, const ipType& ob);

ipType ConvertLineToIP(const std::string &str);

//                           // ! for an old linearic version !
template<typename... Args>
[[deprecated ("It's for an old linearic version")]] // Just to use "attribute: deprecated" :)
void FilterByBytes(std::ostream& s, ipType ip, Args... args)
{
	ipType a = { (args)... }; 

	if (std::equal(a.cbegin(), a.cend(), ip.cbegin()))
		s << ip;
}
