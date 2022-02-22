// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"

int main()
{
	Red::Core::RedString cTestString = "Red Framework";

	Red::Core::RedChar cTestCh = cTestString[2];
	cTestString.SetCharAtIndex(2, 'e');

	std::cout << "Hello " << cTestString.TextPtr() << "!\n";
}