/**
 * @file container_utilities.hpp
 * @brief This file provides some convenient ways to inject containers content to a @b std::ostream.
 * To do so, it first implements the basic overload of the <b>output stream injection</b> operator (<<).
 * In addition, it provides a fresh new interface for <b>std::queue</b>, <b>std::stack</b> and the good old
 * @b C-style arrays (such as type name[Nb]).
 *
 * As usual, it requires at least <b>-std=c++11</b> to compile.
 * @author MTLCRBN
 * @copyright Copyright 2017 MTLCRBN@n
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice, this list of
 *      conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list
 *      of conditions and the following disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *   3. Neither the name of the copyright holder nor the names of its contributors may be
 *      used to endorse or promote products derived from this software without specific prior
 *      written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef MTL_STL_STREAMING_HPP_INCLUDED
#define MTL_STL_STREAMING_HPP_INCLUDED

#include <array>       // For explicit specialization of ostream<<.
#include <cstdlib>     // For std::size_t.
#include <ostream>     // For std::ostream.
#include <queue>       // For std::queue creation of begin() && end().
#include <stack>       // For std::stack creation of begin() && end().
#include <string>      // For std::basic_string, wchar_t.
#include <tuple>       // For std::tuple interface and utilities (get<> and std::tuple_size<>).
#include <utility>     // For std::declval.


//! @brief Completely disable creation/destruction
#define MTL_UNCREATABLE(type) \
    type(void) = delete;\
    type(const type&) = delete;\
    type(type&&) = delete;\
    type& operator=(const type&) = delete;\
    type& operator=(type&&) = delete


namespace mtl_details
{
    //-----------------------------------------------------------------------------
    /**
     * @class stl_exposer
     * @brief Grants access to the internal container of a @b std::stack or a @b std::queue.
     * It does so by using a cool trick provided by @b AraK (Thanks dude). You could find the full post on :
     * http://stackoverflow.com/questions/4523178/how-to-print-out-all-elements-in-a-stdstack-or-stdqueue-conveniently
     *
     * @warning You shall not use this class by yourself.
     *
     * @tparam S_or_Q A @b std::stack or a @b std::queue.
     * @tparam T      The @b value_type of @b S_or_Q.
     * @tparam C      The container used for @b S_or_Q, which must match the <b>iterator-pair idiom</b>.
     *
     * @todo Fix warnings with -Weffc++ (or shut them up)
     */
    template<template<typename...> class S_or_Q, typename T, typename C>
    struct stl_exposer final : private S_or_Q<T, C>
    {
        //! @{
        /**
         * @brief Exposes the internal container of @b S_or_Q.
         * It defines it for const and none const references.
         */
        static const C& get(const S_or_Q<T, C>& s)
        {
            return s.*&stl_exposer::c;
        }
        static C& get(S_or_Q<T, C>& s)
        {
            return s.*&stl_exposer::c;
        }
        //! @}
        MTL_UNCREATABLE(stl_exposer);
        virtual ~stl_exposer(void) =0;
    };
}

//! @{
/**
 * @brief Implements the <b>iterator-pair idiom</b> for @b std::stack.
 * Applies it for const and none const reference.
 * @tparam T The value_type of the std::stack.
 * @tparam C The internal container of the std::stack.
 * @param[in] stack (const or not) The stack you want the begin/end iterator.
 * @return The desired iterator.
 * @warning Never ever use these functions to remove/add elements, it will break the usage rules of the std::stack.
 *
 * You could use it simply, without providing template arguments :
 * @code
 * std::stack<int> s;
 * for(auto it = begin(s);it != end(s); ++it) ...
 * @endcode
 */
//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator begin(const std::stack<T, C>& stack)
{
    return ::mtl_details::stl_exposer<std::stack, T, C>::get(stack).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator end(const std::stack<T, C>& stack)
{
    return ::mtl_details::stl_exposer<std::stack, T, C>::get(stack).end();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator begin(std::stack<T, C>& stack)
{
    return ::mtl_details::stl_exposer<std::stack, T, C>::get(stack).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator end(std::stack<T, C>& stack)
{
    return ::mtl_details::stl_exposer<std::stack, T, C>::get(stack).end();
}
//! @}

//! @{
/**
 * @brief Implements the <b>iterator-pair idiom</b> for @b std::queue.
 * Applies it for const and none const reference.
 * @tparam T The value_type of the std::queue.
 * @tparam C The internal container of the std::queue.
 * @param[in] queue (const or not) The queue you want the begin/end iterator.
 * @return The desired iterator.
 * @warning Never ever use these functions to remove/add elements, it will break the usage rules of the std::queue.
 *
 * You could use it simply, without providing template arguments :
 * @code
 * std::queue<int> s;
 * for(auto it = begin(s);it != end(s); ++it) ...
 * @endcode
 */
//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator begin(const std::queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::queue, T, C>::get(queue).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator end(const std::queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::queue, T, C>::get(queue).end();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator begin(std::queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::queue, T, C>::get(queue).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator end(std::queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::queue, T, C>::get(queue).end();
}
//! @}

//! @{
/**
 * @brief Implements the <b>iterator-pair idiom</b> for @b std::priority_queue.
 * Applies it for const and none const reference.
 * @tparam T The value_type of the std::priority_queue.
 * @tparam C The internal container of the std::priority_queue.
 * @param[in] queue (const or not) The queue you want the begin/end iterator.
 * @return The desired iterator.
 * @warning Never ever use these functions to remove/add elements, it will break the usage rules of the std::priority_queue.
 *
 * You could use it simply, without providing template arguments :
 * @code
 * std::priority_queue<int> s;
 * for(auto it = begin(s);it != end(s); ++it) ...
 * @endcode
 */
//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator begin(const std::priority_queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::priority_queue, T, C>::get(queue).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::const_iterator end(const std::priority_queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::priority_queue, T, C>::get(queue).end();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator begin(std::priority_queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::priority_queue, T, C>::get(queue).begin();
}

//-----------------------------------------------------------------------------
template<typename T, typename C>
typename C::iterator end(std::priority_queue<T, C>& queue)
{
    return ::mtl_details::stl_exposer<std::priority_queue, T, C>::get(queue).end();
}
//! @}

//! @{
/**
 * @brief Implements the <b>iterator-pair idiom</b> for <b>C-style arrays</b>.
 * Applies it for const and none const reference.
 * @tparam ArrayType The value_type of the C-style array.
 * @tparam N         The number of element sfor this array.
 * @param[in] array (const or not) The C-style array you want the begin/end iterator.
 * @return The desired iterator.
 *
 * You could use it simply, without providing template arguments :
 * @code
 * int arr[50];
 * for(auto it = begin(arr);it != end(arr); ++it) ...
 * @endcode
 */
//-----------------------------------------------------------------------------
template<typename ArrayType, std::size_t N>
const ArrayType* begin(const ArrayType (&array)[N])
{
    return &array[0u];
}

//-----------------------------------------------------------------------------
template<typename ArrayType, std::size_t N>
const ArrayType* end(const ArrayType (&array)[N])
{
    return &array[N];
}

//-----------------------------------------------------------------------------
template<typename ArrayType, std::size_t N>
ArrayType* begin(ArrayType (&array)[N])
{
    return &array[0u];
}

//-----------------------------------------------------------------------------
template<typename ArrayType, std::size_t N>
ArrayType* end(ArrayType (&array)[N])
{
    return &array[N];
}
//! @}

//-----------------------------------------------------------------------------
/**
 * @class array_cast
 * @brief Provides a class with begin() and enarray_castarray_castd() statements to display the array behind a specific pointer.
 * @tparam T The type of your pointer (T = double for double*)
 * It doesn't deal with memory (new or delete) or overflow if you set up a wrong @b size value.
 */
template<typename T>
struct array_cast final
{
    T* ptr;
    const std::size_t n;
    array_cast(T* array, std::size_t size) : ptr(array), n(size)
    {
    }
    ~array_cast(void) = default;
    MTL_UNCREATABLE(array_cast);
};

//! @{
/**
 * @brief Implements the <b>iterator-pair idiom</b> for <b>array_cast</b> helper class.
 * Applies it for const and none const reference.
 * @tparam T The value_type of the array_cast helper.
 * @param[in] p (const or not) The array_cast helper you want the begin/end iterator.
 * @return The desired iterator.
 *
 * @warning Don't call these functions by yourself.
 *
 * Usage :
 * @code
 * double* arr[3] = new double[3];
 * //Fill it
 * std::cout << array_cast<double>(arr, 3) << std::endl;
 *
 * // Don't forget this
 * delete[] arr;
 * @endcode
 */
//-----------------------------------------------------------------------------
template<typename T>
T* begin(array_cast<T>& p)
{
    return &p.ptr[0u];
}

//-----------------------------------------------------------------------------
template<typename T>
T* end(array_cast<T>& p)
{
    return &p.ptr[p.n];
}

 //-----------------------------------------------------------------------------
template<typename T>
const T* begin(const array_cast<T>& p)
{
    return &p.ptr[0u];
}

//-----------------------------------------------------------------------------
template<typename T>
const T* end(const array_cast<T>& p)
{
    return &p.ptr[p.n];
}
//! @}


#define MTL_IS_TUPLE     1u
#define MTL_IS_NOT_TUPLE 0u

namespace mtl_details
{
    //-----------------------------------------------------------------------------
    /**
     * @class Int
     * @brief A helper class to choose which overload to call.
     * @warning You shall not use this class by yourself.
     */
    template<std::size_t N> struct Int final {};

    //-----------------------------------------------------------------------------
    //! @{
    /**
     * @class is_not_char
     * @brief This class helps to avoid ambiguity with already implemented operator<< for char/unsigned char arrays.
     * By using SFINAE idiom, any instanciation with char or unsigned char as specialization reach an error, so
     * my overload for arrays won't be elected as the valid overload to call.
     * @warning You shall not use this class by yourself.
     */
    template<typename T> struct is_not_char final {};
    template<> struct is_not_char<char>;
    template<> struct is_not_char<unsigned char>;
    template<> struct is_not_char<signed char>; // signed char != char
    template<> struct is_not_char<wchar_t>;
    //! @}

    //-----------------------------------------------------------------------------
    /**
     * @brief Valid case of SFINAE idiom, @b T could be use as a std::tuple.
     * auto keyword allows to use a trailing type declaration (->).@n
     * If anything with this declaration fails (error, impossibility, etc), this function won't be
     * elected for this call.@n
     * Here, if @b T doesn't match the calls of std::tuple_size and std::get, it fails.@n
     * std::size_t defines the real return type for this function.
     * @tparam T The type you wanna test.
     * @return A constexpr MTL_IS_TUPLE, which could be use within compilation context.
     * @warning You shall not use this function by yourself.
     */
    template<typename T>
    constexpr auto is_tuple(int) -> decltype(std::ignore = std::tuple_size<T>::value,
                                             std::ignore = std::get<0>(std::declval<T>()),
                                             std::size_t())
    {
        return MTL_IS_TUPLE;
    }

    //-----------------------------------------------------------------------------
    /**
     * @brief Invalid case of SFINAE idiom, @b T couldn't be use as a std::tuple.
     * Here, the ellipsis defines the very last overload possible to be call. It means that the
     * above overload will be try first (and this one only if this first overload fails).@n
     * We could define ellipsis as the ultimate variable black hole.
     * @tparam T The type you wanna test.
     * @return A constexpr MTL_IS_NOT_TUPLE, which could be use within compilation context.
     * @warning You shall not use this function by yourself.
     */
    template<typename T>
    constexpr std::size_t is_tuple(...)
    {
        return MTL_IS_NOT_TUPLE;
    }

    //-----------------------------------------------------------------------------
    /**
     * @brief The terminal case of tuple recursion (shows last element).
     * @tparam T Any kind of @b std::tuple.
     * @param[in,out]  out   The output stream you wanna use.
     * @param[in]      tuple The @b std::tuple you wanna display.
     * @param[useless] Isn't use at all, just here to handle the current element number.
     * warning You shall not use this function by yourself.
     */
    template<typename T>
    void tuple_print_rec(std::ostream& out, const T& tuple, ::mtl_details::Int<1>)
    {
        out << std::get<std::tuple_size<T>::value-1>(tuple);
    }

    //-----------------------------------------------------------------------------
    /**
     * @brief The general case of tuple recursion (shows current element).
     * @tparam T Any kind of @b std::tuple.
     * @tparam NThe number of element left to display.
     * @param[in,out]  out   The output stream you wanna use.
     * @param[in]      tuple The @b std::tuple you wanna display.
     * @param[useless] Isn't use at all, just here to handle the current element number.
     * @warning You shall not use this function by yourself.
     */
    template<typename T, std::size_t N>
    void tuple_print_rec(std::ostream& out, const T& tuple, ::mtl_details::Int<N>)
    {
        out << std::get<std::tuple_size<T>::value - N>(tuple) << ' ';
        ::mtl_details::tuple_print_rec(out, tuple, ::mtl_details::Int<N-1>());
    }

    //-----------------------------------------------------------------------------
    /**
     * @brief Prints a container which match the std::tuple interface.
     * @tparam Container The container you wanna display.
     * @param[in,out]  out       The output stream you wanna use.
     * @param[in]      container The container you wanna display.
     * @param[useless]           Isn't use at all, just here to select this function.
     * @warning You shall not use this function by yourself.
     */
    template<typename Container>
    std::ostream& print(std::ostream& out, const Container& container, ::mtl_details::Int<0u>)
    {
        out << "[ ";
        auto iterator_end = end(container);
        for(auto it=begin(container);it!=iterator_end;++it)
        {
            out << *it << ' ';
        }
        return out << ']';
    }

    //-----------------------------------------------------------------------------
    /**
     * @brief Prints a container which doesn't the std::tuple interface.
     * @tparam Container The container you wanna display.
     * @param[in,out]  out       The output stream you wanna use.
     * @param[in]      container The container you wanna display.
     * @param[useless]           Isn't use at all, just here to select this function.
     * @warning You shall not use this function by yourself.
     */
    template<typename Container>
    std::ostream& print(std::ostream& out, const Container& container, ::mtl_details::Int<1u>)
    {
        out << "( ";
        ::mtl_details::tuple_print_rec(out, container,
                                       ::mtl_details::Int<std::tuple_size<Container>::value>());
        return out << " )";
    }

    //-----------------------------------------------------------------------------
    /**
     * @class is_tuplable
     * @brief A wrapper to check with SFINAE if @b T matches std::tuple interface.
     * @tparam T The type you wanna test.
     * @warning You shall not use this class by yourself.
     */
    template<typename T>
    struct is_tuplable final
    {
        enum : std::size_t {value = ::mtl_details::is_tuple<T>(0)};
        MTL_UNCREATABLE(is_tuplable);
    };

    //-----------------------------------------------------------------------------
    /**
     * @class enable_if_not_same
     * @brief Defines @b type if and only if C1 != C2. Implicitly, this allows to use SFINAE
     * to exclude different kind of "containers".
     * @tparam C1 A random type which accepts multiple template parameters.
     * @tparam C2 A random type which accepts multiple template parameters.
     * @warning You shall not use this function by yourself.
     */
    template<template<typename...> class C1, template<typename...> class C2>
    struct enable_if_not_same final
    {
        MTL_UNCREATABLE(enable_if_not_same);
        typedef int type;
    };
    //! @brief No such implementation, it will fail overload selection.
    template<template<typename...> class C1>
    struct enable_if_not_same<C1, C1>;

    //-----------------------------------------------------------------------------
    /**
     * @class has_iterators
     * @brief Set @b ::value to true if @b T has iterators, @b false otherwise.
     * @tparam T The type you wanna check for iterators.
     * @warning You shall not use this function by yourself.
     */
    template<typename T>
    struct has_iterators final
    {
        private:
            template<typename C, typename b = decltype(begin(std::declval<C>())),
                                 typename e = decltype(end(std::declval<C>()))>
            static constexpr bool check(int)
            {
                return true;
            }
            template<typename C>
            static constexpr bool check(...)
            {
                return false;
            }
        public:
            MTL_UNCREATABLE(has_iterators);
            enum {value = has_iterators<T>::check<T>(0)};
    };

    //-----------------------------------------------------------------------------
    /**
     * @class grant_access
     * @brief  Defines @b granted type if and only if the boolean template parameter is @b true.
     * @tparam B The boolean value pre calculated.
     * @warning You shall not use this function by yourself.
     */
    template<bool B> struct grant_access;
    template<> struct grant_access<true> final
    {
        MTL_UNCREATABLE(grant_access);
        typedef int granted;
    };
}

//-----------------------------------------------------------------------------
/**
 * @brief Defines an overload for C-style arrays, but not for char and unsigned char arrays.
 * Because it conflicts with current implementation of the STL.
 * @tparam ArrayType The type of your array.
 * @tparam N         The number of element of this array.
 * @param[in,out] out   The output stream you wanna use.
 * @param[in]     array The C-style array you wanna display.
 *
 * The trailing return type (auto and ->) ensures than ArrayType isn't char or unsigned char.@n
 * (out) ensures than we create a std::ostream& as return type.@n
 * Anyway, you could use it simply :
 * @code
 * int zeInts[8] = {1, 2, 3, 4, 5, 6, 7, 8};
 * std::cout << zeInts << std::endl;
 * // Output : [ 1 2 3 4 5 6 7 8 ]
 * @endcode
 * @return @b out as std::ostream& (I sware it does).
 */
template<typename ArrayType, std::size_t N>
auto operator<<(std::ostream& out, const ArrayType (&array)[N])
    -> decltype(::mtl_details::is_not_char<ArrayType>(), (out))
{
    return ::mtl_details::print(out, array, ::mtl_details::Int<MTL_IS_NOT_TUPLE>());
}

//-----------------------------------------------------------------------------
/**
 * @brief Defines an overload for std::array.
 * @tparam ArrayType The type of your array.
 * @tparam N         The number of element of this array.
 * @param[in,out] output The output stream you wanna use.
 * @param[in]     array  The std::array array you wanna display.
 *
 * You could use it simply :
 * @code
 * std::array<int, 8> array;
 * // Fill it with 1 2 3 4 5 6 7 8
 * std::cout << array << std::endl;
 * // Output : ( 1 2 3 4 5 6 7 8 )
 * @endcode
 * @return @b output
 */
template<typename T, std::size_t S>
std::ostream& operator<<(std::ostream& output, const std::array<T, S>& array)
{
    return ::mtl_details::print(output, array, ::mtl_details::Int<MTL_IS_TUPLE>());
}

//-----------------------------------------------------------------------------
/**
 * @brief Defines an overload for most of STL containers (except std::array).
 * @tparam Container A type which accept multiple template arguments.
 * @tparam Values    Every @b Container template argument types.
 * @param[in,out] out The output stream you wanna use.
 * @param[in]     c   The STL container you wanna display.
 *
 * It works on :
 *   - std::vector
 *   - std::list
 *   - std::forward_list
 *   - std::deque
 *   - std::queue
 *   - std::stack
 *   - std::set
 *   - std::unordered_set
 *   - std::map
 *   - std::unordered_map
 *   - std::valarray
 *   - std::pair
 *   - std::tuple
 *   - std::priority_queue
 *   - std::multiset
 *   - std::unordered_multiset
 *   - std::multimap
 *   - std::unordered_multimap
 *
 * It is simply to use either :
 * @code
 * // Create any container as cont;
 * // Fill it
 * std::cout << cont << std::endl;
 * @endcode
 * @return @b output
 */
template<template<typename...> class Container, typename... Types>
auto operator<<(std::ostream& output, const Container<Types...>& c)
    -> decltype(std::ignore = typename mtl_details::enable_if_not_same<std::basic_string, Container>::type{},
                std::ignore = typename mtl_details::grant_access<
                    mtl_details::has_iterators<Container<Types...>>::value ||
                    mtl_details::is_tuplable<Container<Types...>>::value>::granted{},
                (output))
{
    typedef typename std::decay<decltype(c)>::type RawType;
    constexpr std::size_t N = ::mtl_details::is_tuplable<RawType>::value;
    return ::mtl_details::print(output, c, ::mtl_details::Int<N>());
}

#undef MTL_IS_NOT_TUPLE
#undef MTL_IS_TUPLE
#undef MTL_UNCREATABLE

#endif
/**
 * @page page_container_utilities Container Utilities
 * This header provides a tons of template to offers a simple interface to use STL containers and C-style arrays
 * with output stream injectors (<<).
 * By using it, display the most complex and bizarre stl structure simply !
 * @code
 * std::tuple<std::vector<std::string>, std::pair<int, int>, std::string, std::map<std::string, int>> ohshit(...);
 * // And the solution is :
 * std::cout << ohshit << std::endl;
 * @endcode
 * @tableofcontents
 * @section section1 Compilation
 *
 * Not very complicated, it just requires @b -std=c++11 or any further version.
 * So far, it is certified with no warnings with the following options :
 *   - -Wall
 *   - -Wextra
 *
 * With -Weffc++, it's a work in progress to remove useless warning about non virtual destructor of the STL containers.
 *
 * @section section2 Tests
 * If you're  a developer, and want to enhance this code, you could run tests to ensure than you don't break anything.@n
 * To do so, just compile the file @b container_utilities_test.cpp :
 * @code
 * g++ -Wall -Wextra -std=c++11 container_utilities_test.cpp -o tests.out
 * ./tests.out
 * @endcode
 * A typical output may look like :
 * @code
 *
 * @endcode
 *
 * @section section3 Supported Containers
 * The following containers are supported :
 *   - std::vector
 *   - std::array
 *   - std::list
 *   - std::forward_list
 *   - std::deque
 *   - std::queue
 *   - std::stack
 *   - std::set
 *   - std::unordered_set
 *   - std::map
 *   - std::unordered_map
 *   - std::valarray
 *   - std::pair
 *   - std::tuple
 *   - std::priority_queue
 *   - std::multiset
 *   - std::unordered_multiset
 *   - std::multimap
 *   - std::unordered_multimap
 *
 * In addition, except char[] and unsigned char[] (because it conflicts with current STL implementation), every possible
 * <b>C-style arrays</b> are supported (as long as the type of your array implements the operator<<(std::ostream&)).@n
 * Keep in mind than this file won't help you for pointers, this in particular won't work at all :
 * @code
 * int* array = new int[6];
 * // fill it.
 * std::cout << array << std::endl;
 * // display a random memory address.
 * @endcode
 * You're maybe thinking : "Oh why ?". This is because I'm using template inference on C-style array to deduce their length.
 * It is typically impossible with such pointers. Even worse, it could collide with another intention of your, showing
 * the address of this pointer for instance.
 * For these cases, it is less user friendly, because you'll have to specify by yourself :
 *   - The array length.
 *   - Your intention of displaying the content and not the address of the first element.
 *
 * @code
 * double* arr = new double[5];
 * // Fill it with whatever you want
 * std::cout << array_cast<double>(arr, 5) << std::endl;
 * // Here is the content of your array.
 * @endcode
 *
 * In addition, "tuple" containers (such as std::pair, std::array and ... std::tuple !) will be display like this :
 * @code
 * ( value1 value2 value3 ... valueX )
 * @endcode
 * And containers which has a iterator-pair idiom (all remaining containers, C-style arrays, array_cast helper) :
 * @code
 * [ value1 value2 value3 ... valueX ]
 * @endcode
 *
 * @section section4 Author && Contributors
 * Made by MTLCRBN
 * Here is the <a href="https://github.com/Lbardoux/container_utilities.git">github repository</a>.
 */
