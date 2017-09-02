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

#include <iostream>
#include "entity.hpp"

int main(int argc, char** argv)
{
    entity e;
    // Set the initial name for the entity.
    e.set_name("player");
    // Changing to an enemy entity.
    e.set_type(e_entity_type::ENEMY);

    // Create a new position.
    position_t pos;
    pos.x = 10;
    pos.y = 50;

    // Create a meta-object for the entity.
    reflect::meta_class<entity> entity_data(e);
	// Loop through the members of the class and print out their names to the terminal.
	entity_data.for_each([](const auto& member) { std::cout << member.get_name() << std::endl; });
	
    // Change the details of the entity with the meta-data.
    entity_data.set_member<position_t>("position", pos); // Position is now [ 10, 50 ]!
    // Wait no he's a friend again now.
    entity_data.set_enum_member_from_string<e_entity_type>("entity_type", "ally");

    return 0;
}
