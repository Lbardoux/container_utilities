/**
 * @file stl_streaming.hpp
 * @brief Defines some overload of the << operator for each STL container.
 * Of course, this is template based, so I believe this is for debug mode only.
 * As usual, you'll need at least @b -std=c++11 in order to use this header.
 * @details Despites this basic statement, this module has more to offers.
 *    - A way to iterate without any copy or loss on <b>std::stack and std::queue</b>.
 *      Beware, if you decide to do so, order doesn't count anymore, because it's based on the internal
 *      container.
 *    - A trait to ensure a specific type is valid through std::tuple interface.
 * 
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

#include <array>
#include <ostream>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>


namespace __impl_details
{
    template<template<typename...> class S_or_Q, typename T, typename C>
    struct __stl_exposer final : private S_or_Q<T, C>
    {
        //! Thanks to @b AraK for this trick.
        //! Original post : http://stackoverflow.com/questions/4523178/how-to-print-out-all-elements-in-a-stdstack-or-stdqueue-conveniently
        static const C& get(const S_or_Q<T, C>& s)
        {
            return s.*&__stl_exposer::c;
        }
        static C& get(S_or_Q<T, C>& s)
        {
            return s.*&__stl_exposer::c;
        }
    };
}

template<typename T, typename C>
typename C::const_iterator begin(const std::stack<T, C>& stack)
{
    return ::__impl_details::__stl_exposer<std::stack, T, C>::get(stack).begin();
}

template<typename T, typename C>
typename C::const_iterator end(const std::stack<T, C>& stack)
{
    return ::__impl_details::__stl_exposer<std::stack, T, C>::get(stack).end();
}

template<typename T, typename C>
typename C::const_iterator begin(const std::queue<T, C>& queue)
{
    return ::__impl_details::__stl_exposer<std::queue, T, C>::get(queue).begin();
}

template<typename T, typename C>
typename C::const_iterator end(const std::queue<T, C>& queue)
{
    return ::__impl_details::__stl_exposer<std::queue, T, C>::get(queue).end();
}

template<typename T, typename C>
typename C::iterator begin(std::stack<T, C>& stack)
{
    return ::__impl_details::__stl_exposer<std::stack, T, C>::get(stack).begin();
}

template<typename T, typename C>
typename C::iterator end(std::stack<T, C>& stack)
{
    return ::__impl_details::__stl_exposer<std::stack, T, C>::get(stack).end();
}

template<typename T, typename C>
typename C::iterator begin(std::queue<T, C>& queue)
{
    return ::__impl_details::__stl_exposer<std::queue, T, C>::get(queue).begin();
}

template<typename T, typename C>
typename C::iterator end(std::queue<T, C>& queue)
{
    return ::__impl_details::__stl_exposer<std::queue, T, C>::get(queue).end();
}

namespace __impl_details
{
    typedef std::size_t Int_ttype;
    
    //! @brief int wrapper and conditional template branchement.
    template<__impl_details::Int_ttype N> struct Int final {};
    
    //! @brief Called only and only if T does match tuple's interface.
    template<typename T>
    constexpr auto __is_tuple(int) -> decltype(std::tuple_size<T>::value, std::get<0>(std::declval<T>()),
                                               ::__impl_details::Int_ttype())
    {
        return 1;
    }
    
    //! @brief SFINAE variable dark vaccuum, T doesn't match tuple's interface.
    template<typename T>
    constexpr ::__impl_details::Int_ttype __is_tuple(...)
    {
        return 0;
    }
    
    //! @brief Terminal case for static size containers.
    template<typename T>
    void tuple_print_rec(std::ostream& out, const T& tuple, ::__impl_details::Int<1>)
    {
        out << std::get<std::tuple_size<T>::value-1>(tuple);
    }
    
    //! @brief General case for static size containers.
    template<typename T, __impl_details::Int_ttype N>
    void tuple_print_rec(std::ostream& out, const T& tuple, ::__impl_details::Int<N>)
    {
        out << std::get<std::tuple_size<T>::value - N>(tuple) << ", ";
        ::__impl_details::tuple_print_rec(out, tuple, ::__impl_details::Int<N-1>());
    }
    
    //! @brief Prints an iterable container (begin && end).
    template<typename Container>
    std::ostream& print(std::ostream& out, const Container& container, ::__impl_details::Int<0>)
    {
        out << "[ ";
        auto iterator_end = end(container);
        for(auto it=begin(container);it!=iterator_end;++it)
        {
            out << *it << ' ';
        }
        return out << ']';
    }
    
    //! @brief Prints a static size container, such as array, pair, tuple.
    template<typename Container>
    std::ostream& print(std::ostream& out, const Container& container, ::__impl_details::Int<1>)
    {
        out << '(';
        ::__impl_details::tuple_print_rec(out, container, 
                                          ::__impl_details::Int<std::tuple_size<Container>::value>());
        return out << ')';
    }
}

/**
 * @class is_tuplable
 * @tparam T Any type, primitives or class.
 * @brief Checks if @b T does match with tuple's interface of the STL.
 * So far, only <b>std::tuple</b>, <b>std::pair</b> and <b>std::array</b> are fine.@n
 * Usage:
 * @code
 * // not valid but self explonatory C++ code :
 * is_tuplable< std::pair<T, T> >::value == true
 * is_tuplable< std::array<T, Size> >::value == true
 * is_tuplable< std::tuple<...> >::value == true
 * is_tuplable< Whatever >::value == false
 * @endcode
 */
template<typename T>
struct is_tuplable final
{
    enum : ::__impl_details::Int_ttype {value = ::__impl_details::__is_tuple<T>(0)};
    is_tuplable(void) = delete;
};

// TODO : Find a way to generalize this ugly specialization.
template<typename T, std::size_t S>
std::ostream& operator<<(std::ostream& output, const std::array<T, S>& array)
{
    return ::__impl_details::print(output, array, ::__impl_details::Int<1>());
}

template<template<typename...> class Container, typename... Values>
std::ostream& operator<<(std::ostream& output, const Container<Values...>& c)
{
    typedef typename std::decay<decltype(c)>::type RawType;
    constexpr const ::__impl_details::Int_ttype N = is_tuplable<RawType>::value;
    return ::__impl_details::print(output, c, ::__impl_details::Int<N>());
}


#endif
