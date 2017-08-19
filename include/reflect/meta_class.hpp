/*
* Reflect library.
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

#ifndef _REFLECT_META_CLASS_HPP_
#define _REFLECT_META_CLASS_HPP_

//====================
// C++ includes
//====================
#include <type_traits>  // Checking the types and enabling of different templates.
#include <tuple>        // Retrieving tuples from the meta engine.
#include <utility>      // Random utility functions.
#include <string>       // Name of the meta class retrieved as a string.

namespace reflect
{
	template <typename Class>
	class meta_class final
	{
	private:
		//====================
		// Member variables
		//====================
		/** The object that this meta-information can read and alter. */
		Class& m_object;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Deleting the default constructor.
		 * 
		 * The default constructor for the meta_class has been deleted, as the meta_class
		 * must always contain a reference to an instance of the templated class.
		 */
		explicit meta_class() = delete;

		/**
		 * @brief Constructor for the meta_class object.
		 * 
		 * When this constructor is invoked, it takes a reference to the class that the meta-data
		 * will represent. When member variables are get or set, the information is altered within the
		 * reference object.
		 * 
		 * If the class has not been registered, the meta-class cannot alter the member variables
		 * of the class.
		 */
		explicit meta_class(Class& object);

		/**
		 * @brief Default destructor for the meta_class object.
		 */
		~meta_class() = default;

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves the name of the registered meta-class.
		 * 
		 * When classes are registered, they can be assigned names that can be used
		 * for serialization or debugging purposes. If no name has been provided, an empty
		 * string is returned.
		 */
		constexpr std::string get_name() const;

		/**
		 * @brief Retrieves the value of the specified member variable.
		 * 
		 * When this method is invoked, it will retrieve the metadata value associated
		 * with the key. If the key is not found, the templated default value is returned.
		 * 
		 * @tparam T   The data-type of the variable to retrieve.
		 * @param name The name of the member variable to retrieve.
		 * 
		 * @returns The associated variable of the metadata.
		 */
		template <typename T>
		T get_member(const std::string& name);

		template <typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
		std::string get_enum_member_as_string(const std::string& name);

		template <typename T, typename = std::enable_if<std::is_enum<T>::value>>
		void set_enum_member_from_string(const std::string& name, const std::string& value);

		/**
		 * @brief Checks for the existence of a registered member variable.
		 *
		 * @param name The name of the member variable to search for.
		 *
		 * @returns True if the member variable with the given name was found.
		 */
		bool has_member(const std::string& name);

		/**
		 * @brief Sets the specified member variable to a desired value.
		 * 
		 * When this method is invoked, it can be used to map a specific value
		 * to a registered member within the meta engine. If the value is not found,
		 * no information is changed.
		 * 
		 * @param name  The name of the registered member variable.
		 * @param value The value to set to the member variable. 
		 * 
		 * @throws runtime_error If no setter has been registered with the member variable.
		 */
		template <typename T, typename V, typename = std::enable_if_t<std::is_constructible<T, V>::value>>
		void set_member(const std::string& name, V&& value);

		//====================
		// Methods
		//====================
		/**
		 * @brief Iterator method that takes a lambda to iterate over the meta-data.
		 * 
		 * When this function is provided with a lambda, it will iterate over each tuple
		 * and property that has been registered with the class. This for_each is only invoked
		 * if the class has been registered with the meta engine.
		 * 
		 * @param f The lambda to iterate the meta-data with.
		 */
		template <typename F, typename = std::enable_if_t<is_registered<Class>()>>
		void for_each(F&& f);

		/**
		 * @brief Iterator method that takes a lambda to iterate over the meta-data.
		 * 
		 * When this function is provided with a lambda, it will iterate over each tuple
		 * and property that has been registered with the class. This for_each is only used
		 * if the class has not been registered with the meta engine, and the definition of the 
		 * method is empty.
		 * 
		 * @param f The lambda to iterate the meta-data with.
		 */
		template <typename F, typename = std::enable_if_t<!is_registered<Class>()>, typename = void>
		void for_each(F&& f);

		/**
		 * @brief Method that will invoke a lambda when the specified member variable is encountered.
		 * 
		 * When the specified member variable is encountered whilst iterating through the meta-data of
		 * the class, the supplied lambda will be invoked for additional behavior.
		 * 
		 * @param name The name of the meta-data member variable.
		 * @param f    The lambda to invoke when the member variable has been found.
		 */
		template <typename T, typename F>
		void for_member(const std::string& name, F&& f);
	};

	//====================
	// Functions
	//====================
	/**
	 * @brief Registers properties of a class and exposes it to the meta-engine.
	 * 
	 * If the register_class function has been over-written within a header file, the return 
	 * result of the function should be this properties function. When invoked, it will variadically
	 * take a list of property_impl objects, which are used to exposed member variables, and getters and
	 * setters of the class to the meta-engine for serialization.
	 * 
	 * @param args The variadic list of property_impl objects.
	 * 
	 * @returns The properties of the meta-class.
	 */
    template <typename... Args>
    auto properties(Args&&... args);

	/**
	 * @brief Registers the meta-data of a class.
	 * 
	 * If the function is supplied within the header file of a class, the information of that
	 * object will be registered to the meta-data system. When a class is registered, it can be
	 * used in conjunction with a meta_class object to alter the member variables of a class. An 
	 * object can be serialized when the class is registered.
	 * 
	 * @param The registration details of the class as meta-information.
	 */
    template <typename Class>
    inline auto register_class();

	/**
	 * @brief Registers a name with the meta engine.
	 * 
	 * A name is a unique value assigned to each class when it is registered with the meta-engine. If
	 * the name is not explicitly stated, it will be set to an empty string.
	 * 
	 * @returns The registered name of the specified class.
	 */
    template <typename Class>
    constexpr std::string register_name();

	/**
	 * @brief Constant expressions that checks whether the specified class has been registered with the meta engine.
	 * 
	 * This constant expression function will check if the specified class has been registered with the
	 * meta engine. If can be used within template arguments for specified or desired behavior.
	 * 
	 * @param True if the class has been registered with the meta-data.
	 */
	template <typename Class>
	constexpr bool is_registered();

	/**
	 * @brief Retrieves a list of registered member variables with the given class.
	 *
	 * When a class is registered with the meta engine, they are all uniquely registered to the class type,
	 * this function will retrieve all properties associated with that class.
	 *
	 * @returns A list of all registered members.
	 */
	template <typename Class>
	const auto& get_members();

} // namespace reflect

//====================
// Meta includes
//====================
#include "meta_class.inl" // Method declarations.

#endif//_REFLECT_META_CLASS_HPP_