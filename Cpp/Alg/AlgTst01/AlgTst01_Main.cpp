// AlgTst01_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Algorithms equal, mismatch and lexicographical_compare.
#include <algorithm>  // algorithm definitions
#include <array>      // array class-template definition
#include <iterator>   // ostream_iterator

//#include <numeric>
//#include <string>
//#include <vector>
//#include <execution>
#include <format> // C++20: This will be #include <format>
//#include <iomanip>
//#include <iostream>
#include <string>
#include <random> 

// expert-cpp-proficient-programmer-2nd_Guerra23_R.pdf, *SC:Expert-C-2nd-edition-main

// \Expert-C-2nd-edition-main\Chapter084_count_if.cpp
void Tst01()
{
    std::array<int, 6> a1{ 1, 2, 3, 4, 3, 6 };    
    std::ostream_iterator<int> output{ std::cout, " " };     
    std::cout << "\nTst01:(1) a1 contains:  ";
    std::ranges::copy(a1, output);  // 
    auto res = std::count_if(std::cbegin(a1), cend(a1),
                            [](int x) { return x == 3; });
    std::cout << "There are " << res << " number of elements equal to 3" << std::endl;
}

// fig14_02.cpp
void Tst02()
{
    
    

}

// fig14_03.cpp
void Tst03()
{
    
 }

// fig14_03.cpp
void Tst04()
{
  
}

// fig14_04.cpp
void Tst05()
{
    
}

int main()
{
    std::cout << ">Main:=====================\n";
    
    Tst01();
    //Tst02(); 
    //Tst03(vNums);
    //Tst03();
    //Tst04();
    //Tst05();
    
    std::cout << "\n\n<Main:=====================\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
