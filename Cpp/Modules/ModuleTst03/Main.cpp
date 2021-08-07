// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  properties
//   Configuration
//      C / C++
//         Language
//             C++ Language Standard : Preview - Features from the Latest C++...
//             Enable Experimental C++ Standard Library Modules : Yes
// https://docs.microsoft.com/en-us/cpp/cpp/modules-cpp?view=msvc-160
// The module, import, and export declarations are available in C++20 and require the /experimental:module compiler switch along with /std:c++latest. 
#if 1
#include <iostream>
import PIMPL_Tst;

int main()
{
    std::cout << "Hello World!\n";

    S s;
    s.do_stuff();          // OK.
    s.get();               // OK: pointer to incomplete type.
    //auto impl = *s.get();  // ill-formed: use of undefined type 'Impl'.
}
#else

import PIMPL_Tst;
//#pragma warning(disable : 5050)  // to disable uncaught_exception warning   ?????
import std.core;
//#pragma warning(disable : 4996)  // to disable uncaught_exception warning



//import <vector>;
//import std.regex;
//import <cstdlib>;
#ifdef DEBUG_LOGGING
//import std.filesystem;
#endif


//using namespace std;

int main()
{
    std::cout << "Test Modules: PIMPL!\n";
    //std::cout << "The result of f() is " << Bar::f() << std::endl; // 42

    S s;
    s.do_stuff();          // OK.
    s.get();               // OK: pointer to incomplete type.
    //auto impl = *s.get();  // ill-formed: use of undefined type 'Impl'.
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
