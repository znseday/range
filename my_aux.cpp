#include <iostream>
#include <sstream>

#include "my_aux.h"

#include <range/v3/all.hpp>

#if (defined WIN32) || (defined WIN64)
#define PROJECT_VERSION_PATCH 1000
#else
#include "version.h"
#endif

using namespace std;

int MyVersion()
{
    return PROJECT_VERSION_PATCH;
}

void MyRangeTest(vector<int>& v)
{
	ranges::sort(v);
}

ostream& operator<<(ostream& s, const ipType& ob)
{
	for (int i = 0; i < 4; i++)
		s << (int)ob[i] << ((i < 3) ? '.' : '\n');

	return s;
}

ipType ConvertLineToIP(const std::string& str)
{
	ipType ip;
	//stringstream ss(str);
	//stringstream ss;
	//ss << str;
	// I don't know how to use it yet (((
	//for (int t, i = 0; i < 4; i++)
	//{
		//int t;
		//ss >> t; 
		//ip.Byte[i] = t;
	//}

	int t[4];
	sscanf(str.c_str(), "%i.%i.%i.%i", &t[0], &t[1], &t[2], &t[3]);
	for (int i = 0; i < 4; i++)
		ip.push_back((BYTE)t[i]);
		/*ip.Bytes[i] = t[i];*/

	return ip;
}


// [[deprecated]]
//bool ipType::operator<(const ipType& ob) const
//{
//	if (Bytes[0] > ob.Bytes[0])
//		return true;
//	else if (Bytes[0] == ob.Bytes[0])
//	{
//		if (Bytes[1] > ob.Bytes[1])
//			return true;
//		else if (Bytes[1] == ob.Bytes[1])
//		{
//			if (Bytes[2] > ob.Bytes[2])
//				return true;
//			else if (Bytes[2] == ob.Bytes[2])
//			{
//				if (Bytes[3] > ob.Bytes[3])
//					return true;
//				else
//					return false;
//			}
//			else
//				return false;
//		}
//		else
//			return false;
//	}
//	else
//		return false;
//}
