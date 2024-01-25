// RangesTst01_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Algorithms equal, mismatch and lexicographical_compare.
#include <algorithm>  // algorithm definitions: count_if
//#include <array>      // array class-template definition
//#include <iterator>   // ostream_iterator

//#include <numeric>
//#include <string>
#include <vector>
//#include <execution>
#include <format> // C++20: This will be #include <format>
//#include <iomanip>
//#include <iostream>
//#include <string>
//#include <random> 

// Guerra23: expert-cpp-proficient-programmer-2nd_Guerra23_R.pdf,  \Expert-C-2nd-edition-main\
// 
//                                     
using MatrixInt = std::vector<std::vector<int>>;

int count_evens(const std::vector<int>& number_line) {
    return std::count_if(number_line.begin(),
        number_line.end(), [](int num) {return num % 2 == 0; });
}

std::vector<int> count_all_evens(const MatrixInt& numbers)
{
    std::vector<int> even_numbers_count;
    for (const auto& number_line : numbers) {
        even_numbers_count.push_back(count_evens(number_line));
    }
    return even_numbers_count;
}

// Guerra23: \Chapter08\2_count_all_evens_short.cpp
void Tst01()
{
    MatrixInt m{ {1, 2, 3}, {4, 5, 6} };
    std::vector<int> CountLine = count_all_evens(m);
    std::string s = std::format("Tst01:(2) CountLine size={}: \n\n", CountLine.size());
    std::cout << s;  // Tst01:(2) CountLine size=2:

    int i{ 0 };
    for (auto item : CountLine) {
        s = std::format("Tst01:(3) item{} = {} \n", i++, item);
        std::cout << s;
          // Tst01:(3) item0 = 1
          // Tst01:(3) item1 = 2
    }
}

// 
void Tst02()
{
   
}

// 
void Tst03()
{
    
 }

// 
void Tst04()
{
    
}

// 
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
