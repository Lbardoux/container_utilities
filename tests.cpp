#include <bits/stdc++.h> // Brute force includes

#include "containers_ostream.hpp"


//-----------------------------------------------------------------------------
#define CHECK(cond)\
if (!(cond)){std::cout << "Test " #cond " Fails at line " << __LINE__ << std::endl;}

//-----------------------------------------------------------------------------
#define COMPARE(obj, oracle)\
do{\
    std::stringstream stream;\
    stream << obj;\
    CHECK(stream.str() == oracle);\
}while(false)

//-----------------------------------------------------------------------------
template<typename... Primitives>
void testPrimitivesNoCollision(void)
{
    std::stringstream sstream;
    auto n = {(sstream << Primitives{} , 1)...};
    (void)n;
}

//-----------------------------------------------------------------------------
void testStringNoCollisions(void)
{
    std::string str("No collision for std::string");
    COMPARE(str, "No collision for std::string");
}

//-----------------------------------------------------------------------------
void testReturnValue(void)
{
    std::vector<int> v;
    int arr[5] = {1, 2, 3, 4, 5};
    std::map<int, int> m;
    COMPARE((std::is_same<decltype(std::cout << v), std::ostream&>::value), "1");
    COMPARE((std::is_same<decltype(std::cout << arr), std::ostream&>::value), "1");
    COMPARE((std::is_same<decltype(std::cout << m), std::ostream&>::value), "1");
}

//-----------------------------------------------------------------------------
void testTupleSimple(void)
{
    std::tuple<int, int, int> t1(5, 10, 15);
    COMPARE(t1, "( 5 10 15 )");
}

//-----------------------------------------------------------------------------
void testTupleComposite(void)
{
    std::tuple<std::pair<std::string, char>, const char*, std::vector<float>> t1(
      std::make_pair("std::string", 'u'), "Oh yeah !", {0.0f, 1.0f, 2.0f});
    COMPARE(t1, "( ( std::string u ) Oh yeah ! [ 0 1 2 ] )");
}

//-----------------------------------------------------------------------------
void testStack(void)
{
    std::stack<double> st;
    st.push(1.0);
    st.push(2.0);
    st.push(3.0);
    COMPARE(st, "[ 1 2 3 ]");
}

//-----------------------------------------------------------------------------
void testQueue(void)
{
    std::queue<int> q;
    q.push(25);
    q.push(50);
    q.push(75);
    COMPARE(q, "[ 25 50 75 ]");
}

//-----------------------------------------------------------------------------
void testList(void)
{

}

//-----------------------------------------------------------------------------
void testForwardList(void)
{

}

//-----------------------------------------------------------------------------
void testDeque(void)
{

}

//-----------------------------------------------------------------------------
void testSet(void)
{

}

//-----------------------------------------------------------------------------
void testUnorderedSet(void)
{

}

//-----------------------------------------------------------------------------
void testUnorderedMap(void)
{

}

//-----------------------------------------------------------------------------
void testValarray(void)
{

}

//-----------------------------------------------------------------------------
void testMultiSet(void)
{

}

//-----------------------------------------------------------------------------
void testMultiMap(void)
{

}

//-----------------------------------------------------------------------------
void testUnorderedMultiMap(void)
{

}

//-----------------------------------------------------------------------------
void testUnorderedMultiSet(void)
{

}

//-----------------------------------------------------------------------------
void testPriorityQueue(void)
{
    std::priority_queue<int> pq;
    pq.push(25);
    pq.push(26);
    pq.push(27);
    COMPARE(pq, "[ 27 25 26 ]");
}

//-----------------------------------------------------------------------------
void testMap(void)
{
    std::map<int, std::pair<int, int>> m;
    m.insert(std::make_pair(1, std::make_pair(1, 1)));
    m.insert(std::make_pair(2, std::make_pair(2, 2)));
    m.insert(std::make_pair(3, std::make_pair(3, 3)));
    COMPARE(m, "[ ( 1 ( 1 1 ) ) ( 2 ( 2 2 ) ) ( 3 ( 3 3 ) ) ]");
}

//-----------------------------------------------------------------------------
void testPointerArray(void)
{
    double t[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double* ptr = t;
    //COMPARE(array_cast<double>(ptr, 5), "[ 1 2 3 4 5 ]");
    int eight[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int* peight = eight;
    array_cast<int> arr(peight, 8);
    for(int* it = begin(arr);it != end(arr); ++it)
    {
        *it *= 2;
    }
    COMPARE(arr, "[ 2 4 6 8 10 12 14 16 ]");
}

//-----------------------------------------------------------------------------
void testCStyleArray(void)
{
    double tab[2] = {1.0, 3.0};
    COMPARE(tab, "[ 1 3 ]");
}

//-----------------------------------------------------------------------------
void testNoCStringCollision(void)
{
    // Check if it doesn't generate ambiguity.
    std::stringstream ostream;
    ostream << "Random String";
    const char str[3] = {'a', 'b', '\0'};
    ostream << str;
}

//-----------------------------------------------------------------------------
void testArray(void)
{
    std::array<int, 15> arr;
    arr.fill(12);
    COMPARE(arr, "( 12 12 12 12 12 12 12 12 12 12 12 12 12 12 12 )");
}

//-----------------------------------------------------------------------------
void testVector(void)
{
    std::vector<float> v(5, 0.0f);
    COMPARE(v, "[ 0 0 0 0 0 ]");
}

//-----------------------------------------------------------------------------
void testPair(void)
{
    std::pair<int, std::string> p(18, "Hello world");
    COMPARE(p, "( 18 Hello world )");
}


//-----------------------------------------------------------------------------
int main()
{
    testReturnValue();
    testPrimitivesNoCollision<
      int, unsigned int, short, unsigned short, char, unsigned char, long, unsigned long, long long,
      unsigned long long, float, double, long double, void*, bool, signed char, wchar_t, char16_t, char32_t>();
    testStringNoCollisions();
    testNoCStringCollision();
    testTupleSimple();
    testTupleComposite();
    testStack();
    testQueue();
    testPair();
    testArray();
    testVector();
    testMap();
    testPriorityQueue();
    testPointerArray();
    testCStyleArray();
    testList();
    testForwardList();
    testDeque();
    testSet();
    testUnorderedSet();
    testUnorderedMap();
    testValarray();
    testMultiSet();
    testMultiMap();
    testUnorderedMultiMap();
    testUnorderedMultiSet();
    return EXIT_SUCCESS;
}
