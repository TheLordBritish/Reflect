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

#ifndef _REFLECT_META_DATA_HPP_
#define _REFLECT_META_DATA_HPP_

//====================
// C++ includes
//====================
#include <tuple>  // Each registered property is a tuple.
#include <string> // Registering the name of a class.

namespace reflect
{
    namespace detail
    {
        template <typename T, typename Type>
        struct metadata_t final
        {
            //====================
            // Member variables
            //====================
            /** Invoked to register relevant classes to the meta engine. */
            static Type members;

            //====================
            // Methods
            //====================
            /**
             * @brief Retrieves the name of the registered class within the meta engine.
             * 
             * @returns The registered name.
             */
            static std::string name() 
            {
                return register_name<T>();
            }
        };

        //====================
        // Methods
        //====================
        /**********************************************************/
        template <typename T, typename Type>
        Type metadata_t<T, Type>::members = register_class<T>();

    } // namespace detail
} // namespace reflect

#endif//_REFLECT_META_DATA_HPP_
