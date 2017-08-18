/*
* Reflect Library
* 2017 - Benjamin Carter (bencarterdev@outlook.com)
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgement
*    in the product documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _REFLECT_DETAIL_HELPERS_HPP_
#define _REFLECT_DETAIL_HELPERS_HPP_

namespace reflect 
{
    namespace detail 
    {
        //====================
        // Functions
        //====================
        /**
         * @brief Iterates over a collection of variadic arguments and invokes a function upon them.
         * 
         * @param f The lambda function that will be invoked upon each iteration.
         * @param args The arguments to iterate over.
         */
        template <typename F, typename... Args>
        void for_each(F&& f, Args&&... args);

        /**
         * @brief Invokes the given function with the specified tuple object.
         * 
         * @param f     The function to invoke.
         * @param tuple The tuple to pass as an argument.
         */
        template <typename F, typename T>
        void for_tuple(F&& f, T&& tuple);

        /**
         * @brief Invokes the given function with the specified tuple object.
         * 
         * This function is only created to satisfy the condition if a single empty
         * tuple is supplied.
         * 
         * @param f     The function to invoke.
         * @param tuple The tuple to pass as an argument.
         */
        template <typename F>
        void for_tuple(F&& f, const std::tuple<>& tuple);

        /**
         * @brief Calls the specified function with the arguments if the enable condition is true.
         * 
         * @param f    The function to invoke.
         * @param args The arguments to invoke within the function.
         */
        template <bool Test, typename F, typename... Args, typename = std::enable_if_t<Test>>
        void call_if(F&& f, Args&&... args);

        /**
         * @brief Calls the specified function with the arguments if the enable condition is false.
         * 
         * The function declaration for this function is empty. It is only invoked if specific conditions
         * are not met.
         * 
         * @param f    The function to invoke.
         * @param args The arguments to invoke within the function.
         */
        template <bool Test, typename F, typename... Args, typename = std::enable_if_t<!Test>, typename = void>
        void call_if(F&& f, Args&&... args);

    } // namespace detail

} // namespace reflect

//====================
// Reflect includes
//====================
#include "template_helpers.inl" // Method declarations.

#endif//_REFLECT_DETAIL_HELPERS_HPP_