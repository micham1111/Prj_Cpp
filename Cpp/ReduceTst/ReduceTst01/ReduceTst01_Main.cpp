// ReduceTst01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <numeric>
#include <string>
#include <vector>
#include <execution>


void Tst01(const std::vector<int>& nums)
{
    int nDifaccumulate32 = std::accumulate(nums.begin() + 1, nums.end(), 32, std::minus<>{});
    std::cout << "nDifaccumulate32=" << nDifaccumulate32 << '\n';  // 32-16-8-4-2-1=1

    int nDifReduce32 = std::reduce(nums.begin() + 1, nums.end(), 32, std::minus<>{});
    std::cout << "nDifReduce32=" << nDifReduce32 << '\n';  // 32-16-8-4-2-1=1

    int nDifaccumulate64 = std::accumulate(nums.begin() + 1, nums.end(), 64, std::minus<>{});  
    std::cout << "nDifaccumulate64=" << nDifaccumulate64 << '\n';  // 64-16-8-4-2-1=33

    int nDifReduce64 = std::reduce(nums.begin() + 1, nums.end(), 64, std::minus<>{});   
    std::cout << "nDifReduce64=" << nDifReduce64 << '\n';    // 64-16-8-4-2-1=33
}

void Tst02(const std::vector<int>& nums)
{
    int nDifReduce_ExcSeq = std::reduce(std::execution::seq, nums.begin() + 1, nums.end(), 32, std::minus<>{});  // 1
    std::cout << "nDifReduce_ExcSeq=" << nDifReduce_ExcSeq << '\n';   //  32-16-8-4-2-1=1

    int nDifReduce_ExcUnseq = std::reduce(std::execution::unseq, nums.begin() + 1, nums.end(), 32, std::minus<>{});      // 1
    std::cout << "nDifReduce_ExcUnseq=" << nDifReduce_ExcUnseq << '\n';  // 1    
}

void Tst03(const std::vector<int>& nums)
{
    int nDifReduce_ExcPar = std::reduce(std::execution::par, nums.begin() + 1, nums.end(), 32, [](int a, int b) {
        std::cout << a << " " << b << '\n';   // 32 16 => 16
                                              // 16 8 => 8                                              
                                              // 8 4 => 4
                                              // 2 1 => 1
                                              // 4 1 -> 3
        return a - b;
        });
    std::cout << "nDifReduce_ExcPar=" << nDifReduce_ExcPar << "\n\n";  // 3    

    auto LamdaMinus = [](int a, int b) {
        std::cout << a << " " << b << '\n';   // 32 16 => 16
        // 16 8 => 8                                              
        // 8 4 => 4
        // 2 1 => 1
        // 4 1 -> 3
        return a - b;
    };


    int nDifReduce_ExcPar_LamdaMinus = std::reduce(std::execution::par, nums.begin() + 1, nums.end(), 32, LamdaMinus);
    std::cout << "nDifReduce_ExcPar_LamdaMinus=" << nDifReduce_ExcPar_LamdaMinus << "\n\n";  // 3    

} // Tst03


int main()
{
    std::cout << ">Main:=====================\n";
    std::vector vNums {32, 16, 8, 4, 2, 1};
    
    //Tst01(vNums);
    //Tst02(vNums); 
    Tst03(vNums);

    std::cout << "<Main:=========\n";
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


