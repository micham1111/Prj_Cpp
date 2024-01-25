// RangesTst01_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Algorithms equal, mismatch and lexicographical_compare.
#include <algorithm>  // algorithm definitions
//#include <array>      // array class-template definition
#include <vector>
#include <ranges>
//#include <iterator>   // ostream_iterator

//#include <numeric>
//#include <string>

//#include <execution>
#include <format> // C++20: This will be #include <format>
//#include <iomanip>
//#include <iostream>
#include <string>
//#include <random> 
#include <cmath>
#include <numeric> // std::iota


// Guerra23: expert-cpp-proficient-programmer-2nd_Guerra23_R.pdf,  *SC:Expert-C-2nd-edition-main\
// 
//                                     
using MatrixInt = std::vector<std::vector<int>>;

int count_evens(const std::vector<int>& number_line) {    
    __int64 nCount = std::count_if(std::ranges::cbegin(number_line),
                                   std::ranges::cend(number_line), 
                                   [](int num) {return num % 2 == 0; });
    return static_cast<int>(nCount);
    
}

std::vector<int> count_all_evens(const MatrixInt& numbers)
{
    std::vector<int> result;
    std::ranges::transform(numbers, std::back_inserter(result), count_evens);
    return result;
}

//std::vector<int> count_all_evens2(const MatrixInt& numbers)
auto count_all_evens2(const MatrixInt& numbers)
{
    //std::vector<int> result;
    auto result = numbers |
             std::ranges::views::transform(count_evens);
    return result;
}


//=================================================================================
//  Guerra23: Expert-C-2nd-edition-main\Chapter08\3_count_evens_functional.cpp
void Tst01()
{
    MatrixInt m{ {1, 2, 3}, {4, 5, 6} };
    std::vector<int> vCount = count_all_evens(m);
    std::string s = std::format("Tst01:(2) vCoun size={}, \n", vCount.size());
    std::cout << s;  // Tst01:(2) vCoun size=2
    
    //for (auto item : vCount) {
    //    s = std::format("{} ", item);
    //   std::cout << s;  // 1 2
    //}
    std::ostream_iterator<int> output{ std::cout, " " };
    std::ranges::copy(vCount, output);  // 1 2
    std::cout << std::endl;    
}

void Tst02()
{
    MatrixInt m{ {1, 2, 3}, {4, 5, 6} };
    auto vCount = count_all_evens2(m);
    std::string s = std::format("Tst02:(2) vCoun size={}, \n", vCount.size());
    std::cout << s;  // Tst02:(2) vCoun size=2

    std::ostream_iterator<int> output{ std::cout, " " };
    std::ranges::copy(vCount, output);  // 1 2
    std::cout << std::endl;
}


// Expert-C-2nd-edition-main/Chapter08/7_transform_sqrt.cpp
void Tst03()
{
    std::vector<double> vec{ 1.1, 2.2, 4.3, 16.2, 9.4 };
    auto result = vec | std::views::transform(static_cast<double (*)(double)>(std::sqrt));
    std::string s = std::format("Tst03:(2) result size={}\n", result.size());
    std::cout << s;  // Tst03:(2) result size=5

    std::cout << "\nTst03:(3) results: \n";
    std::ostream_iterator<double> output{ std::cout, " " };
    std::ranges::copy(result, output);  // 1.04881 1.48324 2.07364 4.02492 3.06594
}


// https://en.cppreference.com/w/cpp/ranges/filter_view
void Tst04()
{
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    std::cout << "\nTst04:(1)  \n";
    for (int i : std::views::iota(0, 6)  // 0, 1, 2, 3, 4, 5
        | std::views::filter(even)       // 0, 2, 4,
        | std::views::transform(square))
        std::cout << i << ' ';  // 0 4 16
}

// 
void Tst05()
{
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };
    
    auto vec = std::views::iota(0, 6)       // 0, 1, 2, 3, 4, 5
           | std::views::filter(even)       // 0, 2, 4,
           | std::views::transform(square);
  
    std::cout << "\nTst05:(1)  \n";
    std::ostream_iterator<double> output{ std::cout, " " };
    std::ranges::copy(vec, output);  // 0 2 4
}

// https://medium.com/@simontoth/daily-bit-e-of-c-std-views-filter-2ca3fb66bee3
void Tst06()
{
    // std::vector<int> vec{ 1,2,3,4,5,6,7 };
    std::vector<int> vec(7);
    std::iota(std::begin(vec), std::end(vec), 1);
    std::cout << "\nTst06:(1) Vec: \n";
    std::ostream_iterator<double> output{ std::cout, " " };
    std::ranges::copy(vec, output);  // 1 2 3 4 5 6 7

    auto vecFiltered = vec | std::views::filter([](int v) {
        return v % 2 == 0;
        });

    std::cout << "\nTst06:(2) vecFiltered:  \n";
    std::ranges::copy(vecFiltered, output);  // 2 4 6
}

void Tst07()
{
    auto vec = std::views::iota(1) | std::views::take(10) |
        std::views::filter([](int v) {
        return v % 2 == 0;
            });

    std::cout << "\nTst07:(2) vec:  \n";
    std::ostream_iterator<double> output{ std::cout, " " };
    std::ranges::copy(vec, output);  // 2 4 6 8 10
}

void Tst08()
{
    std::vector<int> v{ 0, 1, -2, 3, -4, -5, 6 };
    auto vView = std::views::filter(v, [](int i) {return i > 0; });
    std::cout << "\nTst07:(2) vec:  \n";
    std::ostream_iterator<double> output{ std::cout, " " };
    std::ranges::copy(vView, output);  // 1 3 6
}

void Tst09()
{

}

void Tst10()
{

}

//==============================================================================
int main()
{
    std::cout << ">Main:=====================\n";
    
    //Tst01();
    //Tst02(); 
    //Tst03(vNums);
    //Tst03();
    //Tst04();
    //Tst05();
    //Tst06();
    //Tst07();
    Tst08();
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
