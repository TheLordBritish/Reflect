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

class TestObject final
{
private:
	int         m_value;
	std::string m_string;
	float       m_readonly;

public:
	explicit TestObject() : m_value(0), m_string(), m_readonly(0.0f) {}
	~TestObject() = default;

	int getValue() const { return m_value; }
	void setValue(int value) { m_value = value;  }

	const std::string& getString() const { return m_string; }
	void setString(const std::string& str) { m_string = str; }

	float getReadonly() const { return m_readonly; }
};

namespace reflect
{
	template <>
	inline auto register_class<TestObject>()
	{
		return properties(
			property("value", &TestObject::getValue, &TestObject::setValue),
			property("string", &TestObject::getString, &TestObject::setString),
			property("readonly", &TestObject::getReadonly)
		);
	}
}

#endif//_TEST_OBJECT_HPP_