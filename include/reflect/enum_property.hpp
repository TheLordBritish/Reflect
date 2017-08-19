/*
* Reflect Library.
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

#ifndef _REFLECT_ENUM_PROPERTY_HPP_
#define _REFLECT_ENUM_PROPERTY_HPP_

//====================
// C++ includes
//====================
#include <unordered_map> // Storing string representations of enums.

//====================
// Reflect includes
//====================
#include "property.hpp"  // enum property is a type of property.

namespace reflect
{
    //====================
    // Structs
    //====================
    template <typename T>
    struct enum_property_hash
    {
        /**
         * @brief Simple hashing method that will hash enums to a registered string.
         * 
         * @param value The enum value to generate a hash for.
         * 
         * @returns The unique hash of the enum.
         */
        template <typename = std::enable_if_t<std::is_enum<T>::value>>
        std::size_t operator()(T const& value) const;
    };

    template <typename, typename>
    class empty_map
    {
        // Empty.
    };

    //====================
    // Aliases
    //====================
    /** Alias for a map that uses enums as the key with their mapped string values. */
    template <typename T>
    using to_string_map_type = std::unordered_map<T, std::string, enum_property_hash<T>>;

    /** Alias for a map that uses string as the key with their mapped enum values. */
    template <typename T>
    using from_string_map_type = std::unordered_map<std::string, T>;

    template <typename Class, typename T>
    class enum_property_impl final : public property_impl<Class, T>
    {
    private:
        //====================
        // Private methods
        //====================
        /**
         * @brief Errorneous method that is invoked if the template argument is not an enumerated type.
         * 
         * @returns An empty map containing no enum property information.
         */
        template <typename U = T>
        typename std::enable_if<!std::is_enum<U>::value, empty_map<U, U>>::type to_string_map() const;

        /**
         * @brief Creates a static map containing information on how enum types are mapped to strings. 
         * 
         * When this method is invoked, it will lazily load a map to store the conversions from enum types to
         * their respective string representations.
         * 
         * @returns The lazily loaded enum to string map.
         */
        template <typename U = T>
        typename std::enable_if<std::is_enum<U>::value, to_string_map_type<U>&>::type to_string_map() const;

        /**
         * @brief Errorneous method that is invoked if the template argument is not an enumerated type.
         * 
         * @returns An empty map containing no enum property information.
         */
        template <typename U = T>
        typename std::enable_if<!std::is_enum<U>::value, empty_map<U, U>>::type from_string_map() const;

        /**
         * @brief Creates a static map containing information on how strings are mapped to enum types. 
         * 
         * When this method is invoked, it will lazily load a map to store the conversions from strings to their
         * respective enum types.
         * 
         * @returns The lazily loaded string to enum map.
         */
        template <typename U = T>
        typename std::enable_if<std::is_enum<U>::value, from_string_map_type<U>&>::type from_string_map() const;

        /**
         * @brief Errorneous method that is invoked if the template argument is not an enumerated type.
         * 
         * If a value is appended to the property which is not an enumerated type, an exception will be thrown to 
         * prevent this undefined behavior.
         * 
         * @returns Nothing.
         * 
         * @throws meta_exception As an incorrect type has been passed to the method.
         */
        template <typename U = T>
        typename std::enable_if<!std::is_enum<U>::value, enum_property_impl<Class, T>&>::type set_value(const std::string& name, T value);

    public:
        //====================
        // Ctors and dtor
        //====================
        /** 
         * @brief Deleting the default constructor for enum_property_impl object.
         * 
         * The default constructor is deleted as the property has to be supplied
         * with values to properly function within the meta-engine.
         */
        explicit enum_property_impl() = delete;
        
        /**
         * @brief Constructor for creating a new enum_property_impl object with a member variable functor.
         * 
         * When this constructor is invoked, it will create a new enum_property_impl object that binds the member
         * variable of a class for getting and setting when invoked by the meta engine.
         * 
         * @param name   The name of the property when serialized.
         * @param member The member variable to bind to the property.
         */
        explicit enum_property_impl(const std::string& name, member_ptr<Class, T> member);

        /**
         * @brief Constructor for creating a new enum_property_impl object with a getter and setter which uses referenced values.
         * 
         * When this constructor is invoked, it will create a new enum_property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are referred to by reference.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
        explicit enum_property_impl(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

        /**
         * @brief Constructor for creating a new enum_property_impl object with a getter and setter which uses object values.
         * 
         * When this constructor is invoked, it will create a new enum_property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are referred to by reference.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
        explicit enum_property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter);

        /**
         * @brief Constructor for creating a new enum_property_impl object with a getter and setter which uses referenced or object values.
         * 
         * When this constructor is invoked, it will create a new enum_property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are either referenced of by value.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
        explicit enum_property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

        /**
         * @brief Default destructor for the propert_impl object.
         */
        ~enum_property_impl() = default;  

        //====================
        // Methods
        //====================
        /**
         * @brief Registers a enumerated value with the property.
         * 
         * When a enum_property is registered with the meta engine, the values of the enum must also be registered
         * so that the value can be changed either through a variable or the defined string. The strings are added to
         * provide extra information if the class is serialized by a external library. The method will only be invoked
         * if the value passed in is a enumerated type.
         * 
         * @param name  The string literal name of the enum type.
         * @param value The enum variable.
         * 
         * @returns A reference to itself, so that setting values can be chained.
         */
        template <typename U = T>
        typename std::enable_if<std::is_enum<U>::value, enum_property_impl<Class, T>&>::type set_value(const std::string& name, T value);

        /**
         * @brief Converts the specified enum value to its mapped string value.
         * 
         * When this method is invoked, it will retrieve the mapped string equivalent of the enumerated
         * type within the property. If the value has not been registered, an out of range exception is thrown.
         * This method is only invoked if the value passed in is a enumerated type.
         * 
         * @param value The enumerated value to convert to a string.
         * 
         * @returns A string representation of the enum variable.
         * 
         * @throws out_of_range exception If the enum value has not been registered with the property.
         */
        template <typename U = T>
        typename std::enable_if<std::is_enum<U>::value, std::string&>::type to_string(const T value) const;

        /**
         * @brief Errorneous method for retrieving a string from a non enumerated type.
         * 
         * This method is only invoked if the value passed in is not a enumeration. An exception will be thrown
         * upon use of this method.
         * 
         * @param The non-enumerated value.
         * 
         * @returns Nothing.
         * 
         * @throws meta_exception is the method is invoked. 
         */
        template <typename U = T>
        typename std::enable_if<!std::is_enum<U>::value, std::string&>::type to_string(const T value) const;
        
        /**
         * @brief Converts the specified string to its mapped enum value.
         * 
         * When this method is invoked, it will retrieve the mapped enum equivalent of the specified string
         * within the property. If the value has not been registered, an out of range exception is thrown.
         * This method is only invoked if the value passed in is a enumerated type.
         * 
         * @param name The string to convert to a enumerated type.
         * 
         * @returns The enum value mapped to the name.
         * 
         * @throws out_of_range exception If the string value has not been registered with the property.
         */
        template <typename U = T>
        typename std::enable_if<std::is_enum<U>::value, U>::type from_string(const std::string& name) const;

        /**
         * @brief Errorneous method for retrieving a enum from a non registered data-type.
         * 
         * This method is only invoked if the template argument is not a enumeration. An exception will be thrown
         * upon use of this method.
         * 
         * @param The name of the enum.
         * 
         * @returns Nothing.
         * 
         * @throws meta_exception is the method is invoked. 
         */
        template <typename U = T>
        typename std::enable_if<!std::is_enum<U>::value, U>::type from_string(const std::string& name) const;
    };

    //====================
    // Functions
    //====================
    /**
     * @brief Convenience method for creating a new enum_property_impl object with a member variable functor.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param member The member variable to bind to the property.
     * 
     * @returns A new enum_property_impl object with a bound member variable functor.
     */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, member_ptr<Class, T> member);

    /**
    * @brief Convenience method for creating a new enum_property_impl object with reference getter.
    *
    * These functions are used to quickly bind properties on a class, without having to insert the template
    * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
    * meta-engine. This property is only declared as readonly, attempting to set the value will result in an 
    * exception being thrown.
    *
    * @param name   The name of the property when serialized.
    * @param getter The getter method functor which returns an object by reference.
    * @param setter The setter method functor which takes an object by reference for an argument.
    *
    * @returns A new enum_property_impl object with a bound referenced getter and setter functors.
    *
    * @throws runtime_error If the property is attempting to set the value.
    */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, ref_getter_func_ptr<Class, T> getter);

    /**
    * @brief Convenience method for creating a new enum_property_impl object with by value getter.
    *
    * These functions are used to quickly bind properties on a class, without having to insert the template
    * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
    * meta-engine. This property is only declared as readonly, attempting to set the value will result in an 
    * exception being thrown.
    *
    * @param name   The name of the property when serialized.
    * @param getter The getter method functor which returns an object by value.
    * @param setter The setter method functor which takes an object by value for an argument.
    *
    * @returns A new enum_property_impl object with a bound value based getter and setter functors.
    *
    * @throws runtime_error If the property is attempting to set the value.
    */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter);

    /**
     * @brief Convenience method for creating a new enum_property_impl object with reference getters and setters.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by reference.
     * @param setter The setter method functor which takes an object by reference for an argument.
     * 
     * @returns A new enum_property_impl object with a bound referenced getter and setter functors.
     */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

    /**
     * @brief Convenience method for creating a new enum_property_impl object with by value getters and setters.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by value.
     * @param setter The setter method functor which takes an object by value for an argument.
     * 
     * @returns A new enum_property_impl object with a bound value based getter and setter functors.
     */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter);

    /**
     * @brief Convenience method for creating a new enum_property_impl object with a value getter and a setter which takes a referenced parameter.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating enum_property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by value.
     * @param setter The setter method functor which takes an object by reference for an argument.
     * 
     * @returns A new enum_property_impl object with a bound value-based getter and reference-based setter functors.
     */
    template <typename Class, typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);
}

//====================
// Reflect includes
//====================
#include "enum_property.inl" // Method declarations.

#endif//_REFLECT_ENUM_PROPERTY_HPP_