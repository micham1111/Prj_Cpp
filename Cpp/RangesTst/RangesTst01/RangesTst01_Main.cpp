// RangesTst01_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Algorithms equal, mismatch and lexicographical_compare.
#include <algorithm>  // algorithm definitions
#include <array>      // array class-template definition
#include <iterator>   // ostream_iterator

//#include <numeric>
//#include <string>
#include <vector>
//#include <execution>
#include <format> // C++20: This will be #include <format>
//#include <iomanip>
//#include <iostream>
#include <string>
#include <random> 

// c20-programmers-3rd_Deitel22_C.pdf, *SC:CPlusPlus20ForProgrammers-master 
// Guerra23: expert-cpp-proficient-programmer-2nd_Guerra23_R.pdf,  *SC:Expert-C-2nd-edition-main\

// create variable to store lambda for reuse later
auto LambdaIsGreaterThan1{ [](auto x) {return x > 1; } };

auto LambdaGreaterThan9{ [](auto x) {return x > 9; } };

auto LambdaIsGreaterThan10{ [](auto x) {return x > 10; } };


// Deitel22: CPlusPlus20ForProgrammers-master:
// fig14_01.cpp
void Tst01()
{
    std::ostream_iterator<int> output{ std::cout, " " };
    std::array arValues{ 1, 2, 3, 4 }; // initialize values
    
    std::cout << "\nTst01: arValues contains:(1) ";
    std::ranges::copy(arValues, output);  //  1 2 3 4

    // add each element to sum
    int sum{ 0 }; // initialize sum to zero
    std::ranges::for_each(arValues, [&sum](auto i) {sum += i; });
    std::cout << "\nTst01: Sum of value's elements is: " << sum << "\n";

    // output each element multiplied by two
    std::cout << "\nTst01: Display each element multiplied by two: ";
    std::ranges::for_each(arValues, [](auto i) { std::cout << i * 2 << " "; });  // 2 4 6 8

    std::ranges::for_each(arValues, [](auto i) {  i = i * 3; });  
    std::cout << "\nTst01: arValues contains:(3) ";
    std::ranges::copy(arValues, output);  //  1 2 3 4

    std::ranges::for_each(arValues, [](auto& i) {  i = i * 3; });
    std::cout << "\nTst01: arValues contains:(4) ";
    std::ranges::copy(arValues, output);  //   3 6 9 12
}

// fig14_02.cpp
void Tst02()
{
    std::ostream_iterator<int> output{ std::cout, " " };
    std::array arValues{ 1, 2, 3, 4 }; // initialize values
    std::cout << "\nTst02: arValues contains:(1) ";
    std::ranges::copy(arValues, output);  //  1 2 3 4


    std::ranges::fill(arValues, 5); // fill with 5
    std::cout << "\nTst02: arValues contains:(2) ";
    std::ranges::copy(arValues, output);  //  5 5 5 5

    // fill first five elements of chars with 'A's
    std::ranges::fill_n(arValues.begin(), 2, 3);
    std::cout << "\nTst02: arValues contains:(3) ";
    std::ranges::copy(arValues, output);  //  3 3 5 5

    // generate values:
    int nInitValue{ 1 };
    auto lambdaGenerate = [&nInitValue]() {  
        nInitValue += 2;
        return nInitValue; 
    };
    std::ranges::generate(arValues, lambdaGenerate);
    std::cout << "\nTst02: after generating:(4) ";
    std::ranges::copy(arValues, output);  // 3 5 7 9


    // generate values:
    nInitValue = 2;
    std::ranges::generate_n(arValues.begin(), 2, lambdaGenerate);
    std::cout << "\nTst02: after generating:(5) ";
    std::ranges::copy(arValues, output);  // 4 6 7 9
}

// fig14_03.cpp
void Tst03()
{
    std::ostream_iterator<int> output{ std::cout, " " };
    std::array arA1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array arA2{ arA1 }; // initializes a2 with copy of a1
    std::array arA3{ 1, 2, 3, 4, 1000, 6, 7, 8, 9, 10 };
  
    std::cout << "Tst03: arA1 contains: ";
    std::ranges::copy(arA1, output);
    std::cout << "\nTst03: arA2 contains: ";
    std::ranges::copy(arA2, output);
    std::cout << "\nTst03: arA3 contains: ";
    std::ranges::copy(arA3, output);
 
    bool bFlag = std::ranges::equal(arA1, arA2);
    // compare a1 and a2 for equality                        
    std::cout << std::format("\nTst03 arA1 is equal to arA2: {}\n", bFlag);  // True

    // check for mismatch between a1 and a3 
    auto location{ std::ranges::mismatch(arA1, arA3) };
    auto nMismatchIndexA1 = (location.in1 - arA1.begin());
    std::cout << std::format("\nTst03: arA1 and arA3 mismatch at index {} ({} vs. {})\n",
                     nMismatchIndexA1, *location.in1, *location.in2); // Tst03: arA1 and arA3 mismatch at index 4 (5 vs. 1000)
 }

// fig14_03.cpp
void Tst04()
{
    std::string s1{ "HELLO" };
    std::string s2{ "BYE BYE" };

    // perform lexicographical comparison of c1 and c2  
    bool bFlag = std::ranges::lexicographical_compare(s1, s2);
    std::cout << std::format("\"{}\" < \"{}\": {}\n", s1, s2, bFlag);  // "HELLO" < "BYE BYE": false
    
}

// fig14_04.cpp
void Tst05()
{
    std::vector v0{ 10, 2, 10, 4, 10, 6, 9, 15 };
    std::vector v1{ v0 }; // initialize with copy of v0

    std::ostream_iterator<int> output{ std::cout, " " };
    std::string s = std::format("\nTst05:(1) v1(size={}): ", v1.size());  
    std::cout << s;
    std::ranges::copy(v1, output);  // Tst05:(1) v1(size=8): 10 2 10 4 10 6 9 15

    // remove all 10s from v1                                
    auto removeV1{ std::ranges::remove(v1, 10) };
    s = std::format("\nTst05:(2) After remove 10 from v1(size={}): ", v1.size());
    std::cout << s;
    std::ranges::copy(v1, output);  // Tst05:(2) After remove 10 from v1(size=8): 2 4 6 9 15 6 9 15
    s = std::format("\nTst05:(3) index {} {}\n",
             std::begin(removeV1)-std::begin(v1), std::end(removeV1) - std::begin(v1)); 
    std::cout << s;  // Tst05:(3) index 5 8

    //v1.erase(removeV1.begin(), removeV1.end());
    v1.erase(std::begin(removeV1), std::end(removeV1));
    s = std::format("\nTst05:(4) v1 after erase 10s,(v1 size={}): ", v1.size());
    std::cout << s;
    std::ranges::copy(v1, output); // Tst05: (4) v1 after erase 10s, (v1 size = 5) : 2 4 6 9 15

    std::vector v3{ v0 }; // initialize with copy of v0
    v3.clear();
    s = std::format("\nTst05:(5) v3 after Clear(size={}): ", v3.size());
    std::cout << s;
    std::ranges::copy(v3, output);  // Tst05:(5) v3 after Clear(size=0):
}

// fig14_04.cpp
void Tst06()
{
    std::vector v0{ 10, 2, 10, 4, 10, 6, 9, 15 };
    std::vector v1{ v0 }; // initialize with copy of v0

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst06:(1) v1: ";
    std::ranges::copy(v1, output);  // Tst06:(1) v1: 10 2 10 4 10 6 9 15

    // copy from v2 to c1, removing 10s in the process    
    std::vector<int> v2{};
    std::ranges::remove_copy(v1, std::back_inserter(v2), 10);
    std::cout << "\nTst06:(2) v2-after copying v1 without 10s: ";
    std::ranges::copy(v2, output);
} // Tst06

// fig14_04.cpp
void Tst07()
{
    std::vector v0{ 10, 2, 10, 4, 10, 6, 9, 15 };
    std::vector v1{ v0 }; // initialize with copy of v0

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst07:(1) v1: ";
    std::ranges::copy(v1, output);  // Tst07:(1) v1: 10 2 10 4 10 6 9 15

    // remove elements greater than 9 from v1                    
    auto removed_if_v1{ std::ranges::remove_if(v1, LambdaGreaterThan9) };
    std::cout << "\nTst07:(2) v1-After removed_if: ";
    std::ranges::copy(v1, output);  // Tst07:(2) v1-After removed_if: 2 4 6 9 10 6 9 15

    std::cout << std::format("\nTst07:(3) index {} {}\n",
        std::begin(removed_if_v1) - std::begin(v1), std::end(removed_if_v1) - std::begin(v1)); // Tst05: (3) index 4 8

    v1.erase(std::begin(removed_if_v1), std::end(removed_if_v1));
    std::cout << "\nTst07:(4) v1-after erasing elements greater than 9 : ";
    std::ranges::copy(v1, output);  // Tst07:(4) v1-after erasing elements greater than 9 : 2 4 6 9
} // Tst07

// fig14_04.cpp
void Tst08()
{
    std::vector v0{ 10, 2, 10, 4, 10, 6, 9, 15 };
    std::vector v1{ v0 }; // initialize with copy of v0

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst08:(1) v1: ";
    std::ranges::copy(v1, output);  // Tst08:(1) v1: 10 2 10 4 10 6 9 15

    // copy elements from v4 to c2, removing elements greater than 9
    std::vector<int> v2{};
    std::ranges::remove_copy_if(v1, std::back_inserter(v2), LambdaGreaterThan9);
    std::cout << "\nTst08:(2) v2-After remove_copy_if v1 without elements greater than 9: ";
    std::ranges::copy(v2, output);  // Tst08:(2) v2-After remove_copy_if v1 without elements greater than 9: 2 4 6 9
} // Tst08


// fig14_05.cpp
void Tst09()
{
    std::array a0{ 10, 2, 15, 4, 10, 6 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst09:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst09:(1) a1: 10 2 15 4 10 6

    // replace all 10s in a1 with 100    
    std::ranges::replace(a1, 10, 100);
    std::cout << "\nTst09:(2) a1-after replacing 10s with 100s: ";
    std::ranges::copy(a1, output); // Tst09:(2) a1-after replacing 10s with 100s: 100 2 15 4 100 6
   
    std::array a2{ a0 };
    std::array<int, a2.size()> a3{};
    std::cout << "\nTst09:(3) a2: ";
    std::ranges::copy(a2, output);  // Tst09:(3) a2: 10 2 15 4 10 6

    // copy from a2 to a3, replacing 10s with 100s              
    std::ranges::replace_copy(a2, std::begin(a3), 10, 100);
    std::cout << "\nTst09:(4) a3: after replacing a2's 10s with 100s: ";
    std::ranges::copy(a3, output); // Tst09:(4) a3: after replacing a2's 10s with 100s: 100 2 15 4 100 6
 
    std::array a4{ a0 };  // 10, 2, 15, 4, 10, 6
    // replace values greater than 9 in a4 with 100   
    std::ranges::replace_if(a4, LambdaGreaterThan9, 100);
    std::cout << "\nTst09:(5) a4-after replace values greater than 9 in a4 with 100: ";
    std::ranges::copy(a4, output); // Tst09:(5) a4-after replace values greater than 9 in a4 with 100: 100 2 100 4 100 6

    std::array a5{ a0 };  // 10, 2, 15, 4, 10, 6
    std::array<int, a5.size()> a6{};

    // copy a5 to a6, replacing elements greater than 9 with 100  
    std::ranges::replace_copy_if(a5, std::begin(a6), LambdaGreaterThan9, 100);
    std::cout << "\nTst09:(6) a6-copy a5 to a6, replacing elements greater than 9 with 100: ";
    std::ranges::copy(a6, output); // Tst09:(6) a6-copy a5 to a6, replacing elements greater than 9 with 100: 100 2 100 4 100 6

    std::cout << '\n';
} // Tst09

// fig14_06.cpp
void Tst10()
{
    std::array a0{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst10:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst10:(1) a1: 1 2 3 4 5 6 7 8 9 10

    // create random-number engine and use it to help shuffle a1
    std::default_random_engine randomEngine{ std::random_device{}() };
    std::ranges::shuffle(a1, randomEngine);  // randomly order elements

    std::cout << "\nTst10:(2) a1-shuffled: ";
    std::ranges::copy(a1, output);  // Tst10:(2) a1 - shuffled : 7 4 6 8 2 5 9 10 3 1
    
    std::cout << '\n';
} // Tst10

// fig14_06.cpp
void Tst11()
{
    std::array a0{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst11:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst11:(1) a1: 1 2 3 4 5 6 7 8 9 10
  
    // create random-number engine and use it to help shuffle a1
    std::default_random_engine randomEngine{ std::random_device{}() };
    std::ranges::shuffle(a1, randomEngine); // randomly order elements
    std::cout << "\nTst11:(2) a1-shuffled: ";
    std::ranges::copy(a1, output); // Tst11:(2) a1-shuffled:  10 4 9 8 6 5 2 7 3 1

    std::cout << '\n';
} // Tst11


// fig14_06.cpp
void Tst12()
{
    std::array a0{ 100, 2, 8, 1, 50, 3, 8, 8, 9, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst12:(1) a1: ";
    std::ranges::copy(a1, output); 

    // count number of elements in a2 with value 8  
    auto result1{ std::ranges::count(a1, 8) };
    std::cout << "\nTst12:(2) Count of 8s in a1: " << result1;
                 // Tst12:(2) Count of 8s in a1 : 3

    // count number of elements in a2 that are greater than 9
    auto result2{ std::ranges::count_if(a1, [](auto x) {return x > 9; }) };
    std::cout << "\nTst12:(3-Lambda) Count of a2 elements greater than 9: " << result2;  
               // Tst12:(3-Lambda) Count of a2 elements greater than 9: 3

    std::cout << '\n';
} // Tst12

// fig14_06.cpp
void Tst13()
{
    std::array a0{ 100, 2, 8, 1, 50, 1, 8, 8, 100, 10 };
    std::array a1{ a0 };

    //std::ostream_iterator<int> output{ std::cout, " " };
    //std::cout << "\nTst13:(1) a1: ";
    //std::ranges::copy(a1, output);

    // locate minimum element in a1
    if (auto result{ std::ranges::min_element(a1) }; result != std::end(a1)) {
        std::cout << "\nTst13:(2) minimum element: " << *result;   // Tst13:(2) minimum element: 1    
    }

    // locate maximum element in a1
    if (auto result{ std::ranges::max_element(a1) }; result != std::end(a1)) {
        std::cout << "\nTst13:(3) a1 maximum element: " << *result;  // Tst13:(3) a1 maximum element : 100
    }

    // locate minimum and maximum elements in a1
    auto [min, max] {std::ranges::minmax_element(a1)};
    std::cout << "\nTst13:(4) a1 minimum and maximum elements: "  
        << *min << " and " << *max;  // Tst13:(4) a1 minimum and maximum elements: 1 and 100

    std::cout << '\n'; 
} // Tst13

// fig14_06.cpp
void Tst14()
{
    std::array a0{ 100, 2, 8, 1, 50, 1, 8, 8, 100, 10 };
    std::array a1{ a0 };

    //std::ostream_iterator<int> output{ std::cout, " " };
    //std::cout << "\nTst14:(1) a1: ";
    //std::ranges::copy(a1, output);

    // locate minimum element in a1
    if (auto result{ std::ranges::min_element(a1) }; result != std::end(a1)) {
        std::cout << "\nTst14:(2) minimum element: " << *result;   // Tst14:(2) minimum element: 1    
    }

    // locate maximum element in a1
    if (auto result{ std::ranges::max_element(a1) }; result != std::end(a1)) {
        std::cout << "\nTst14:(3) a1 maximum element: " << *result;  // Tst14:(3) a1 maximum element : 100
    }

    // locate minimum and maximum elements in a1
    auto [min, max] {std::ranges::minmax_element(a1)};
    std::cout << "\nTst14:(4) a1 minimum and maximum elements: "
        << *min << " and " << *max;  // Tst14:(4) a1 minimum and maximum elements: 1 and 100

    std::cout << '\n';
} // Tst14

// fig14_06.cpp
void Tst15()
{
    std::array a0{ 100, 2, 8, 1, 50, 1, 8, 8, 100, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst15:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst15:(1) a1: 100 2 8 1 50 1 8 8 100 10

   // calculate cube of each element in a1; place results in cubes
    std::array<int, a1.size()> arSqr{};
    std::ranges::transform(a1, std::begin(arSqr),
                  [](auto x) { return x * x; });
    std::cout << "\nTst15:(2) arSqr: a1 values Squared: ";
    std::ranges::copy(arSqr, output); // Tst15:(2) arSqr: a1 values Squared: 10000 4 64 1 2500 1 64 64 10000 100
} // Tst15


// fig14_07.cpp
void Tst16()
{
    std::array a0{ 10, 2, 17, 5, 16, 8, 13, 11, 20, 7 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst16:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst16:(1) a1: 10 2 17 5 16 8 13 11 20 7


    // locate first occurrence of 16 in a1          
    if (auto loc1{ std::ranges::find(a1, 16) }; loc1 != a1.cend()) {
        std::cout << "\nTst16:(2) 16 Found in a1 at index: " << (loc1 - a1.cbegin());
           // Tst16:(2) 16 Found in a1 at index : 4
    }
    else { // 16 not found
        std::cout << "\nTst16:(3) 16 not found in a1";
    }

    // locate first occurrence of 4 in a1          
    if (auto loc1{ std::ranges::find(a1, 4) }; loc1 != a1.cend()) {
        std::cout << "\nTst16:(4) 4 Found in a1 at index: " << (loc1 - a1.cbegin());
    }
    else { // 16 not found
        std::cout << "\nTst16:(5) 4 not found in a1";
            // Tst16:(5) 4 not found in a1
    }

    
    // locate first occurrence of value greater than 10 in a1
    auto loc3{ std::ranges::find_if(a1, LambdaIsGreaterThan10) };

    if (loc3 != a1.cend()) { // found value greater than 10
        std::cout << "\n\nTst16:(6) First value on a1 greater than 10: " << *loc3
            << "\nfound at index: " << (loc3 - a1.cbegin());
            // Tst16:(6) First value on a1 greater than 10: 17
            //   found at index: 2
    }
    else { // value greater than 10 not found
        std::cout << "\n\nTst16:(7) No values in a1 greater than 10 were found";
    }

    // locate first occurrence of value that is not greater than 10
    auto loc4{ std::ranges::find_if_not(a1, LambdaIsGreaterThan10) };

    if (loc4 != a1.cend()) { // found a value less than or equal to 10
        std::cout << "\n\nTst16:(8) First value not greater than 10: " << *loc4
            << "\nfound at index: " << (loc4 - a1.cbegin());
           // Tst16:(8) First value not greater than 10: 10
           // found at index : 0
    }
    else { // no values less than or equal to 10 were found
        std::cout << "\n\nTst16:(9) Only values greater than 10 were found";
    }
} // Tst16


// fig14_07.cpp
void Tst17()
{
    std::array a0{ 10, 2, 17, 5, 16, 8, 13, 11, 20, 7 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst17:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst17:(1) a1: 10 2 17 5 16 8 13 11 20 7

    // sort elements of a1
    std::ranges::sort(a1);
    std::cout << "\nTst17:(2) a1 after sort: ";
    std::ranges::copy(a1, output); // Tst17:(2) a1 after sort: 2 5 7 8 10 11 13 16 17 20

    // use binary_search to check whether 13 exists in a1
    if (std::ranges::binary_search(a1, 13)) {
        std::cout << "\n\nTst17:(3) 13 was found in a1";  // Tst17:(3) 13 was found in a1
    }
    else {
        std::cout << "\n\nTst17:(4) 13 was not found in a1";
    }
    
    // use binary_search to check whether 100 exists in a1
    if (std::ranges::binary_search(a1, 100)) {
        std::cout << "\n\nTst17:(5) 13 was found in a1";
    }
    else {
        std::cout << "\n\nTst17:(6) 13 was not found in a1";  // Tst17:(6) 13 was not found in a1
    }
} // Tst17


// fig14_07.cpp
void Tst18()
{
    std::array a0{ 10, 2, 17, 5, 16, 8, 13, 11, 20, 7 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst18:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst18:(1) a1: 10 2 17 5 16 8 13 11 20 7

    // determine whether all of values' elements are greater than 1
    if (std::ranges::all_of(a1, LambdaIsGreaterThan1)) {
        std::cout << "\nTst18:(2) All values elements in a1 are greater than 1";
            // Tst18:(2) All values elements in a1 are greater than 1
    }
    else {
        std::cout << "\nTst18:(3) values elements in a1 are not greater than 1";
    }

    // determine whether all of values' elements are greater than 10
    if (std::ranges::all_of(a1, LambdaIsGreaterThan10)) {
        std::cout << "\nTst18:(4) All values elements in a1 are greater than 10";
    }
    else {
        std::cout << "\nTst18:(5) values elements in a1 are not greater than 10";
          // Tst18:(5) values elements in a1 are not greater than 10
    }

    // determine whether any of values' elements are greater than 10
    if (std::ranges::any_of(a1, LambdaIsGreaterThan10)) {
        std::cout << "\n\nTst18:(6) Some values elements in a1 are greater than 10";
           // Tst18:(6) Some values elements in a1 are greater than 10
    }
    else {
        std::cout << "\nTst18:(7) No values elements in a1 are  greater than 10";
    }

    // determine whether none of values' elements are greater than 10
    if (std::ranges::none_of(a1, LambdaIsGreaterThan10)) {
        std::cout << "\n\nTst18:(8) No values elements are greater than 10";
    }
    else {
        std::cout << "\n\nTst18:(9) Some values elements are greater than 10";
           // Tst18:(9) Some values elements are greater than 10
    }

} // Tst18

// fig14_08.cpp
void Tst19()
{
    std::array a0{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst19:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst19:(1) a1: 1 2 3 4 5 6 7 8 9 10

    // swap first 3 elements of a1
    std::ranges::swap_ranges(std::begin(a1), std::begin(a1)+3,
        std::end(a1)-3, std::end(a1));
        //std::begin(a1)+5, std::begin(a1) + 8);  // 6 7 8 4 5 1 2 3 9 10

    std::cout << "\n\nTst19:(2) a1: After swap_ranges for 3 elements contains:\n";
    std::ranges::copy(a1, output);  
       // Tst19:(2) a1: After swap_ranges for 3 elements contains:
       // 8 9 10 4 5 6 7 1 2 3

    std::array a2{ a0 };
    // swap first 3 elements of a2
    std::ranges::swap_ranges(std::begin(a2), std::begin(a2) + 3,
           std::begin(a2)+5, std::begin(a2) + 8);  
    std::cout << "\n\nTst19:(3) a2: After swap_ranges for 3 elements contains:\n";
    std::ranges::copy(a1, output);  // 6 7 8 4 5 1 2 3 9 10


    std::array a3{ a0 };
    std::array a4{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::cout << "\n\nTst19:(4) a3: ";
    std::ranges::copy(a3, output);  // Tst19:(4) a3 : 1 2 3 4 5 6 7 8 9 10
    std::cout << "\nTst19:(5) a4: ";
    std::ranges::copy(a4, output);  // Tst19: (5) a4 : 10 9 8 7 6 5 4 3 2 1

    std::ranges::swap_ranges(a3, a4);
    std::cout << "\nTst19:(6) a3: After swap_ranges: ";
    std::ranges::copy(a3, output);  // Tst19: (6) a3: After swap_ranges : 10 9 8 7 6 5 4 3 2 1
    std::cout << "\nTst19:(7) a4: After swap_ranges: ";
    std::ranges::copy(a4, output);  // Tst19: (7) a4 : After swap_ranges : 1 2 3 4 5 6 7 8 9 10

    std::cout << '\n';
} // Tst19

// fig14_09.cpp
void Tst20()
{
    std::array a1{ 1, 3, 5, 7, 9 };
    std::array a2{ 2, 4, 5, 7, 9 };
    std::ostream_iterator<int> output{ std::cout, " " };

    // place elements of a1 into results in reverse order  
    std::array<int, a1.size()> a3{};
    std::ranges::copy_backward(a1, std::end(a3));
    std::cout << "\nTst20:(3) a3: After copy_backward, a3 contains: ";
    std::ranges::copy(a3, output);  // Tst20:(3) a3: After copy_backward, a3 contains: 1 3 5 7 9

    // merge elements of a1 and a2 into results2 in sorted order
    std::array<int, a1.size() + a2.size()> a4{};
    std::ranges::merge(a1, a2, std::begin(a4));
    std::cout << "\n\nTst20:(4) a4: After merge of a1 and a2, a4 contains: ";
    std::ranges::copy(a4, output); // Tst20:(4) a4 : After merge of a1 and a2, a4 contains : 1 2 3 4 5 5 7 7 9 9
 
    std::cout << '\n';
} // Tst20

// fig14_09.cpp
void Tst21()
{
    std::vector v1{ 1, 2, 3, 4, 5, 5, 7, 7, 9, 9 };
    
    // eliminate duplicate values from v 
    auto [first, last] {std::ranges::unique(v1)};
    v1.erase(first, last); // remove elements that no longer contain values
    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\n\nTst21:(2) v1 After unique, v1 contains: ";
    std::ranges::copy(v1, output);  // Tst21:(2) v1 After unique, v1 contains: 1 2 3 4 5 7 9

    std::cout << '\n';
} // Tst21

// fig14_09.cpp
void Tst22()
{
    std::array a0{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a1{ a0 };

    std::ranges::reverse(a1); // reverse elements of a1

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst22:(2) a1: After reverse:";
    std::ranges::copy(a1, output);  // Tst22:(2) a1: After reverse:10 9 8 7 6 5 4 3 2 1
} // Tst22

// fig14_09.cpp
void Tst23()
{
    std::array a2{ 1, 2, 4, 5, 7, 9 };

    // copy odd elements of a2 into v2
    std::vector<int> v2{};    
    std::ranges::copy_if(a2, std::back_inserter(v2),
                        [](auto x) {return x % 2 == 0; });
    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\n\nTst23:(2) v2: After copy_if, v2 contains: ";
    std::ranges::copy(v2, output); // Tst23:(2) v2: After copy_if, v2 contains: 2 4

    // copy three elements of a2 into v3
    std::vector<int> v3{};    
    std::ranges::copy_n(std::begin(a2), 3, std::back_inserter(v3));
    std::cout << "\n\nTst23:(3) v3: After copy_n, v3 contains: ";
    std::ranges::copy(v3, output); // Tst23:(3) v3: After copy_n, v3 contains: 1 2 4
} // Tst23

// fig14_10.cpp
void Tst24()
{
    std::array a0{ 1, 3, 5, 7, 9, 1, 3, 5, 7, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst24:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst24:(1) a1: 1 3 5 7 9 1 3 5 7 10

    // merge first half of a1 with second half of a1 such that
   // a1 contains sorted set of elements after merge         
    std::ranges::inplace_merge(a1, a1.begin() + 5);
    std::cout << "\nTst24:(2) a1: After inplace_merge, a1 contains: ";
    std::ranges::copy(a1, output);
      // Tst24:(2) a1 : After inplace_merge, a1 contains : 1 1 3 3 5 5 7 7 9 10

    // copy only unique elements of a1 into results1                 
    std::vector<int> a3{};
    std::ranges::unique_copy(a1, std::back_inserter(a3)); // a1 need to be sorted
    std::cout << "\nTst24:(3) a3: After unique_copy, a3 contains: ";
    std::ranges::copy(a3, output); 
       // Tst24:(3) a3: After unique_copy, a3 contains: 1 3 5 7 9 10

    std::vector<int> a4{};
    std::ranges::unique_copy(a0, std::back_inserter(a4)); 
    std::cout << "\nTst24:(4) a4: After unique_copy, a4 contains: ";
    std::ranges::copy(a4, output); 
        // Tst24:(4) a4 : After unique_copy, a4 contains : 1 3 5 7 9 1 3 5 7 10

    // copy elements of a1 into results2 in reverse order             
    std::vector<int> a5{};
    std::ranges::reverse_copy(a0, std::back_inserter(a5));
    std::cout << "\nTst24:(5) a5: After reverse_copy, a5 contains: ";
    std::ranges::copy(a5, output); 
      // Tst24:(5) a5: After reverse_copy, a5 contains: 10 7 5 3 1 9 7 5 3 1
} // Tst24

// fig14_11.cpp
void Tst25()
{
    std::array a1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a2{ 4, 5, 6, 7, 8 };
    std::array a3{ 4, 5, 6, 11, 15 };
    std::ostream_iterator<int> output{ std::cout, " " };

    // determine whether a2 is completely contained in a1
    bool bA1IncludeA2 = std::ranges::includes(a1, a2);
    std::string s = std::format("\nTst25:(3) a1 {} a2\n",
        bA1IncludeA2 ? "includes" : "does not include");
    std::cout << s;  // Tst25:(3) a1 includes a2


    // determine whether a3 is completely contained in a1
    bool bA1IncludeA3 = std::ranges::includes(a1, a3);
    s = std::format("\nTst25:(4)  a1 {} a3\n",
           bA1IncludeA3 ? "includes" : "does not include");
    std::cout << s;  // Tst25:(4)  a1 does not include a3

    // determine elements of a1 not in a2 
    std::vector<int> vDifference{};
    std::ranges::set_difference(a1, a2, std::back_inserter(vDifference));
    std::cout << "\nTst25:(5) set_difference of a1 and a2 is: ";
    std::ranges::copy(vDifference, output);
       // Tst25:(5) set_difference of a1 and a2 is: 1 2 3 9 10

    // determine elements in both a1 and a2                 
    std::vector<int> vIntersection{};
    std::ranges::set_intersection(a1, a2,
                         std::back_inserter(vIntersection));
    std::cout << "\nTst25:(6) set_intersection of a1 and a2 is: ";
    std::ranges::copy(vIntersection, output);
       // Tst25:(6) set_intersection of a1 and a2 is: 4 5 6 7 8

    // determine elements of a1 that are not in a3 and              
   // elements of a3 that are not in a1                            
    std::vector<int> vSymmetricDifference{};
    std::ranges::set_symmetric_difference(a1, a3,
        std::back_inserter(vSymmetricDifference));
    std::cout << "\nTst25:(7) set_symmetric_difference of a1 and a3 is: ";
    std::ranges::copy(vSymmetricDifference, output);
       // Tst25:(7) set_symmetric_difference of a1 and a3 is: 1 2 3 7 8 9 10 11 15

    vSymmetricDifference.clear();
    std::ranges::set_symmetric_difference(a1, a2,
        std::back_inserter(vSymmetricDifference));
    std::cout << "\nTst25:(8) set_symmetric_difference of a1 and a2 is: ";
    std::ranges::copy(vSymmetricDifference, output);
 
} // Tst25

// fig14_11.cpp
void Tst26()
{
    std::array a1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a2{ 4, 5, 6, 7, 8 };
    std::array a3{ 4, 5, 6, 11, 15 };
 

    std::ostream_iterator<int> output{ std::cout, " " };
    //std::cout << "\nTst26:(1) a1: ";
    //std::ranges::copy(a1, output);  // 

    // determine elements that are in either or both sets
    std::vector<int> v1{};
    std::ranges::set_union(a1, a3, std::back_inserter(v1));
    std::string s = std::format("\nTst26:(2) set_union of a1 and a3 is v1(size={}):  ", v1.size());
    std::cout << s;
    std::ranges::copy(v1, output);
      // Tst26:(2) set_union of a1 and a3 is v1(size = 12) : 1 2 3 4 5 6 7 8 9 10 11 15
} // Tst26

// fig14_12.cpp
void Tst27()
{
    std::array a0{ 2, 2, 4, 4, 4, 6, 6, 6, 6, 8 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst27:(1) a1: ";
    std::ranges::copy(a1, output);  // Tst27:(1) a1: 2 2 4 4 4 6 6 6 6 8

    // determine lower-bound insertion point for 6 in values 
    auto lower{ std::ranges::lower_bound(a1, 6) };
    std::cout << "\nTst27:(2) Lower bound of 6 is index: "
        << (lower - a1.begin());
           // Tst27:(2) Lower bound of 6 is index : 5
} // Tst27

/*
// fig14_12.cpp
void Tst21()
{
    std::array a0{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array a1{ a0 };

    std::ostream_iterator<int> output{ std::cout, " " };
    std::cout << "\nTst21:(1) a1: ";
    std::ranges::copy(a1, output);  // 

    
    std::cout << '\n';
} // Tst21
*/
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
    //Tst08();
    //Tst09();
    //Tst10();
    //Tst11();
    //Tst12();
    //Tst13();
    //Tst14();
    //Tst15();
    //Tst16();
    //Tst17();
    //Tst18();
    //Tst19();
    //Tst20();
    //Tst21();
    //Tst22();
    //Tst23();
    //Tst24();
    //Tst25();
    //Tst26();
    Tst27();
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
