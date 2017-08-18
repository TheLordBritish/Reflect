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

#define CATCH_CONFIG_MAIN
#include <catch.hpp>            // Unit-testing framework.
#include "test_object.hpp"      // Test object.
#include <reflect/reflect.hpp>  // Reflect framework.

/**********************************************************/
TEST_CASE("Check class is registered.", "[reflect]")
{
	// Assert.
	REQUIRE(reflect::is_registered<TestObject>());
}

/**********************************************************/
TEST_CASE("Check class is not registered.", "[reflect]")
{
	// Arrange.
	struct Object {};

	// Assert.
	REQUIRE(!reflect::is_registered<Object>());
}

/**********************************************************/
TEST_CASE("Checking members exist.", "[reflect]")
{
	// Arrange.
	TestObject object;
	reflect::meta_class<TestObject> data(object);

	// Assert.
	REQUIRE(data.has_member("value"));
	REQUIRE(data.has_member("string"));
	REQUIRE(data.has_member("readonly"));
}

/**********************************************************/
TEST_CASE("Getting variable through meta-class.", "[reflect]")
{
	// Arrange.
	TestObject object;
	object.setValue(10);
	object.setString("word");

	reflect::meta_class<TestObject> data(object);

	// Act.
	int value = data.get_member<int>("value");
	std::string str = data.get_member<std::string>("string");

	// Assert.
	REQUIRE(value == object.getValue());
	REQUIRE(str == object.getString());
}

/**********************************************************/
TEST_CASE("Setting variables through meta-class.", "[reflect]")
{
	// Arrange.
	TestObject object;
	reflect::meta_class<TestObject> data(object);

	// Act.
	data.set_member<int>("value", 10);
	data.set_member<std::string>("string", "word");

	// Assert.
	REQUIRE(object.getValue() == data.get_member<int>("value"));
	REQUIRE(object.getString() == data.get_member<std::string>("string"));
}

/**********************************************************/
TEST_CASE("Setting variable through meta-class with incorrect data-type.", "[reflect]")
{
	// Arrange.
	TestObject object;
	reflect::meta_class<TestObject> data(object);

	// Assert.
	REQUIRE_THROWS_AS(data.set_member<float>("value", 1.0f), reflect::detail::meta_exception);
}

/**********************************************************/
TEST_CASE("Setting value on readonly variable.", "[reflect]")
{
    // Arrange.
    TestObject object;
    reflect::meta_class<TestObject> data(object);

    // Assert.
	REQUIRE_THROWS_AS(data.set_member<float>("readonly", 1.0f), reflect::detail::meta_exception);
}