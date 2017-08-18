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

#ifndef _REFLECT_DETAIL_META_EXCEPTION_HPP_
#define _REFLECT_DETAIL_META_EXCEPTION_HPP_

//====================
// C++ includes
//====================
#include <stdexcept> // Inherits from runtime_error.

namespace reflect
{
    namespace detail
    {
        class meta_exception final : public std::runtime_error
        {
        public:
            //====================
            // Ctors and dtor
            //====================
            /**
             * @brief Constructor for the exception.
             * 
             * The meta exception class must be constructed with a message as to why
             * the exception was thrown. 
             * 
             * @param msg The reason that the exception was thrown.
             */
            meta_exception(const std::string& msg) : std::runtime_error(msg) {}
    
            /**
             * @brief Default destructor.
             */
            ~meta_exception() = default;
        };

    } // namespace detail
} // namespace reflect


#endif//_REFLECT_DETAIL_META_EXCEPTION_HPP_