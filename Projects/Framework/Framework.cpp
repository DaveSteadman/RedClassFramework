// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"

int main()
{
	Red::Core::RedString cTestString = "Red Framework";

	std::cout << "Hello " << cTestString.TextPtr() << "!\n";
}