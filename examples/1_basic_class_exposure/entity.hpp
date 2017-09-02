/*
* Reflect library
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

#ifndef _EXAMPLE_1_ENTITY_HPP_
#define _EXAMPLE_1_ENTITY_HPP_

#include <string>

enum class e_entity_type
{
    ALLY,
    ENEMY
};

struct position_t
{
    int x;
    int y;
};

class entity final
{
private:
    position_t   m_position;
    std::string  m_name;
    e_entity_type m_type;

public:
    explicit entity();
    ~entity() = default;

    const position_t& get_position() const;
    void set_position(const position_t& position);
    
    const std::string& get_name() const;
    void set_name(const std::string& name);

    e_entity_type get_type() const;
    void set_type(e_entity_type type);
};

/**********************************************************/
#include <reflect/reflect.hpp>

namespace reflect
{
    template <>
    inline auto register_class<position_t>()
    {
        return properties(
            // Directly registering the public member variables.
            property("x", &position_t::x),
            property("y", &position_t::y)
        );
    }

    template <>
    inline auto register_class<entity>()
    {
        return properties(
            // Setting through the getters and setters.
            property("position", &entity::get_position, &entity::set_position),
            property("name", &entity::get_name, &entity::set_name),
            // Registering the enum and its different states.
            enum_property("entity_type", &entity::get_type, &entity::set_type)
                .set_value("ally", e_entity_type::ALLY)
                .set_value("enemy", e_entity_type::ENEMY)
        );
    }
}

#endif//_EXAMPLE_1_ENTITY_HPP_