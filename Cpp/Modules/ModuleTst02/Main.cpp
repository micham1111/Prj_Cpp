// ModuleTst02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  properties
//   Configuration
//      C / C++
//         Language
//             C++ Language Standard : Preview - Features from the Latest C++...
//             Enable Experimental C++ Standard Library Modules : Yes
#if 0
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
#else
import ModuleBasic;
import std.core;

//using namespace std;

int main()
{
    std::cout << "The result of f() is " << Bar::f() << std::endl; // 42
    // int i = Bar::f_internal(); // C2039
    // int j = ANSWER; //C2065
}
#endif


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
