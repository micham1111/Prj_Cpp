
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <execution>
#include <format> // C++20: This will be #include <format>

// Guerra23: expert-cpp-proficient-programmer-2nd_Guerra23_R.pdf,  \Expert-C-2nd-edition-main\

// 
void Tst01()
{
    std::vector nums{ 32, 16, 8, 4, 2, 1 };
    int nAccumulate_Minus = std::accumulate(std::begin(nums) + 1, std::end(nums), 32, std::minus<>{});  // 1
    std::cout << std::format("\nTst01:(2) nAccumulate_Minus = {} \n", nAccumulate_Minus);

    int nReduce_Minus = std::reduce(std::begin(nums) + 1, std::end(nums), 32, std::minus<>{});      // 1
    std::cout << std::format("Tst01:(3) nReduce_Minus = {} \n", nReduce_Minus);

    int nReduce_Minus_Seq = std::reduce(std::execution::seq, std::begin(nums) + 1, std::end(nums), 32, std::minus<>{});   // 1
    std::cout << std::format("Tst01:(4) nReduce_Minus_Seq = {} \n", nReduce_Minus_Seq);

    int nReduce_Minus_Unseq = std::reduce(std::execution::unseq, std::begin(nums) + 1, std::end(nums), 32, std::minus<>{}); // 1
    std::cout << std::format("Tst01:(5) nReduce_Minus_Unseq = {} \n", nReduce_Minus_Unseq);

    //std::cout << std::reduce(std::execution::par, nums.begin() + 1, nums.end(), 32, [](int a, int b) {
        //std::cout << a << " " << b << '\n'; 
        //return a - b;
        //}) << '\n';

    int nReduce_Minus_Par = std::reduce(std::execution::par, nums.begin() + 1, nums.end(), 32, [](int a, int b) {
        std::cout << a << " " << b << '\n';
        return a - b;
        });
    // 32 16
    // 16 8
    // 8 4
    // 2 1
    // 4 1
    std::cout << "Tst01:(7) nReduce_Minus_Par=" << nReduce_Minus_Par << '\n'; // nReduce_Minus_Par=3/nReduce_Minus_Par=1

    int nAccumulate_Minus64 = std::accumulate(std::begin(nums), std::end(nums), 64, std::minus<>{});  // 1
    std::cout << std::format("\nTst01:(8) nAccumulate_Minus64 = {} \n", nAccumulate_Minus64);
} // Tst01

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

//==============================================================================

int main()
{
    Tst01();
    
}




