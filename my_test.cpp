#define BOOST_TEST_MODULE range_test_module

#include "my_aux.h"

// It's visible only if this included in CMakelists manually. Why?
#include <range/v3/all.hpp>

#include <boost/test/unit_test.hpp>

//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <fstream>
//#include <algorithm>

using namespace std;

BOOST_AUTO_TEST_SUITE(range_test_suite)

BOOST_AUTO_TEST_CASE(range_test_MyVersion)
{
    BOOST_CHECK(MyVersion() > 0);
}

BOOST_AUTO_TEST_CASE(range_test_ConvertLineToIP)
{
	string TestString = "100.2.30.44";
	ipType ip = ConvertLineToIP(TestString);
	BOOST_CHECK(ip[0] == 100 && ip[1] == 2 && ip[2] == 30 && ip[3] == 44);
}

BOOST_AUTO_TEST_CASE(range_test_FilterByBytes)
{
	string TestString = "100.2.30.44";
	
	ipType ip = ConvertLineToIP(TestString);
	cout << "ip for test: " << ip;
	cout << "result ip (must be the same): ";
	FilterByBytes(cout, ip, (BYTE)100, (BYTE)2);
	stringstream ss;
	FilterByBytes(ss, ip, (BYTE)100, (BYTE)2);
	string test;
	ss >> test;

	BOOST_REQUIRE_EQUAL(TestString, test);
}

BOOST_AUTO_TEST_CASE(range_test_FilterByBytes_not)
{
	string TestString = "100.2.30.44";

	ipType ip = ConvertLineToIP(TestString);
	stringstream ss;
	FilterByBytes(ss, ip, (BYTE)100, (BYTE)74, (BYTE)30);
	string test;
	ss >> test;

	BOOST_REQUIRE_NE(TestString, test);
}

BOOST_AUTO_TEST_CASE(range_test_does_range_work)
{
	cout << endl;
	std::vector<int> v{ 2, 0, 1 }; // Just to be sure that Range is visible and works
	ranges::copy(v, ranges::ostream_iterator<int>(cout, " "));
	cout << endl;
	
	ranges::sort(v);               // Just to be sure that Range is visible and works

	ranges::copy(v, ranges::ostream_iterator<int>(cout, " "));
	cout << endl;

	// "cout" doesn't work in Travis, but works in VS 

	BOOST_CHECK(v[0] == 0 && v[1] == 1 && v[2] == 2);
}

BOOST_AUTO_TEST_SUITE_END()
