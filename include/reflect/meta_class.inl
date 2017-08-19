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

//====================
// C++ includes
//====================
#include <cassert> // Asserting if the member is not the designated type.

//====================
// Meta includes
//====================
#include "property.hpp"                // Retrieving the name from the property.
#include "enum_property.hpp"           // Retrieving information on enum properties.
#include "detail/template_helpers.hpp" // Methods for iterating tuples.
#include "detail/metadata.hpp"         // Stores the information of each meta_class.

namespace reflect
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	template <typename Class>
	meta_class<Class>::meta_class(Class& object)
		: m_object(object)
	{
		// Empty.
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	template <typename Class>
	constexpr std::string meta_class<Class>::get_name() const
	{
		return detail::metadata_t<Class, decltype(register_class<Class>())>::name();
	}

	/**********************************************************/
	template <typename Class>
	template <typename T>
	T meta_class<Class>::get_member(const std::string& name)
	{
		T value;
		this->for_member<T>(name, [&value, this](const auto& member) {
			value = member.get(m_object);
		});

		return value;
	}

	/**********************************************************/
	template <typename Class>
	template <typename T, typename>
	std::string meta_class<Class>::get_enum_member_as_string(const std::string& name)
	{
		std::string value;
		this->for_member<T>(name, [&value, this](const auto& member) {
			value = member.to_string(member.get(m_object));
		});

		return value;
	}

	/**********************************************************/
	template <typename Class>
	template <typename T, typename>
	void meta_class<Class>::set_enum_member_from_string(const std::string& name, const std::string& value)
	{
		this->for_member<T>(name, [&value, this](const auto& member) {
			member.set(m_object, member.from_string(value));
		});
	}

	/**********************************************************/
	template <typename Class>
	bool meta_class<Class>::has_member(const std::string& name)
	{
		bool result = false;
		this->for_each([&result, name, this](const auto& member) {
			if (member.get_name() == name) {
				result = true;
			}
		});

		return result;
	}

	/**********************************************************/
	template <typename Class>
	template <typename T, typename V, typename>
	void meta_class<Class>::set_member(const std::string& name, V&& value)
	{
		this->for_member<T>(name, [this, value = std::forward<V>(value)](const auto& member) {
			member.set(m_object, value);
		});
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	template <typename Class>
	template <typename F, typename>
	void meta_class<Class>::for_each(F&& f)
	{
		detail::for_tuple(std::forward<F>(f), get_members<Class>());
	}

	/**********************************************************/
	template <typename Class>
	template <typename F, typename, typename>
	void meta_class<Class>::for_each(F&& f)
	{
		// Empty.
	}

	/**********************************************************/
	template <typename Class>
	template <typename T, typename F>
	void meta_class<Class>::for_member(const std::string& name, F&& f)
	{
		this->for_each([&](const auto& member) {
			if (name == member.get_name()) 
			{
				if (!std::is_same<get_member_type<decltype(member)>, T>::value)
				{
					std::string err = std::string("Member variable: ") + name + std::string("does not match the supplied datatype.");
					throw detail::meta_exception(err);
				}

				detail::call_if<std::is_same<get_member_type<decltype(member)>, T>::value>(std::forward<F>(f), member);
			}
		});
	}

	//====================
	// Functions
	//====================
	/**********************************************************/
	template <typename... Args>
	auto properties(Args&&... args)
	{
		return std::make_tuple(std::forward<Args>(args)...);
	}

	/**********************************************************/
	template <typename Class>
	inline auto register_class()
	{
		return std::make_tuple();
	}

	/**********************************************************/
	template <typename Class>
	constexpr std::string register_name()
	{
		return std::string();
	}

	/**********************************************************/
	template <typename Class>
	constexpr bool is_registered()
	{
		return !std::is_same<std::tuple<>, decltype(register_class<Class>())>::value;
	}

	/**********************************************************/
	template <typename Class>
	const auto& get_members()
	{
		return detail::metadata_t<Class, decltype(register_class<Class>())>::members;
	}

} // end of namespace reflect
