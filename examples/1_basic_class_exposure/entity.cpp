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

#include "entity.hpp"

entity::entity()
    : m_position(), m_name(), m_type(e_entity_type::ALLY)
{
    m_position.x = 0;
    m_position.y = 0;
}

const position_t& entity::get_position() const
{
    return m_position;
}

void entity::set_position(const position_t& position)
{
    m_position = position;
}

const std::string& entity::get_name() const
{
    return m_name;
}

void entity::set_name(const std::string& name)
{
    m_name = name;
}

e_entity_type entity::get_type() const
{
	return m_type;
}

void entity::set_type(e_entity_type type)
{
	m_type = type;
}