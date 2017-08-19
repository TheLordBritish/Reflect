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

#ifndef _TEST_OBJECT_HPP_
#define _TEST_OBJECT_HPP_

#include <string>
#include <reflect/reflect.hpp>

enum class eColour
{
	RED,
	GREEN,
	BLUE
};

class test_object final
{
private:
	int         m_value;
	std::string m_string;
	float       m_readonly;
	eColour     m_colour;

public:
	explicit test_object() : m_value(0), m_string(), m_readonly(0.0f), m_colour(eColour::RED) {}
	~test_object() = default;

	int get_value() const { return m_value; }
	void set_value(int value) { m_value = value;  }

	const std::string& get_string() const { return m_string; }
	void set_string(const std::string& str) { m_string = str; }

	float get_readonly() const { return m_readonly; }

	eColour get_colour() const { return m_colour; }
	void set_colour(const eColour& colour) { m_colour = colour; }
};

namespace reflect
{
	template <>
	inline auto register_class<test_object>()
	{
		return properties(
			property("value", &test_object::get_value, &test_object::set_value),
			property("string", &test_object::get_string, &test_object::set_string),
			property("readonly", &test_object::get_readonly),
			enum_property("colour", &test_object::get_colour, &test_object::set_colour)
				.set_value("Red", eColour::RED)
				.set_value("Green", eColour::GREEN)
				.set_value("Blue", eColour::BLUE)
		);
	}
}

#endif//_TEST_OBJECT_HPP_