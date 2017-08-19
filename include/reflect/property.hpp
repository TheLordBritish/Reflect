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

#ifndef _REFLECT_PROPERTY_HPP_
#define _REFLECT_PROPERTY_HPP_

//====================
// C++ includes
//====================
#include <string>        // Represents the name of the property.
#include <unordered_map> // Creating a map of enumerated types.

namespace reflect
{
    // Forward declare the enum property for conversion purposes.
    template<typename Class, typename T>
    class enum_property_impl;

    //====================
    // Aliases
    //====================
    /** Alias for a member variable function pointer. */
    template <typename Class, typename T>
    using member_ptr = T Class::*;

    /** Alias for a getter method which returns an object by const reference. */
    template <typename Class, typename T>
    using ref_getter_func_ptr = const T& (Class::*)() const;

    /** Alias for a setter method which takes in an object argument by reference. */
    template <typename Class, typename T>
    using ref_setter_func_ptr = void (Class::*)(const T&);

    /** Alias for a getter method which returns an object by value. */
    template <typename Class, typename T>
    using val_getter_func_ptr = T(Class::*)() const;

    /** Alias for a setter method which takes in an object argument by value. */
    template <typename Class, typename T>
    using val_setter_func_ptr = void (Class::*)(T);

    /** Specifies the type of the member variable. */
    template <typename Type>
    using get_member_type = typename std::decay_t<Type>::member_type;
	
    template <typename Class, typename T>
    class property_impl
	{
    private:
        //====================
        // Member variables
        //====================
        /** The name of the property, which is the name of the value when serialized. */
        std::string                   m_name;
        /** A function pointer for a member variable of a class. */
        member_ptr<Class, T>          m_member;
        /** Whether the property_impl object has a member variable pointer. */
        bool                          m_has_member;
        /** A function pointer for a getter method that returns a reference. */
        ref_getter_func_ptr<Class, T> m_ref_getter;
        /** A function pointer for a setter method that takes in a referenced argument. */
        ref_setter_func_ptr<Class, T> m_ref_setter;
        /** A function pointer for a getter method that returns an object by value. */
        val_getter_func_ptr<Class, T> m_val_getter;
        /** A function pointer for a setter method that takes in an argument by value. */
        val_setter_func_ptr<Class, T> m_val_setter;

    public:
        using class_type = Class;
        using member_type = T;

        //====================
        // Ctors and dtor
        //====================
        /** 
         * @brief Deleting the default constructor for property_impl object.
         * 
         * The default constructor is deleted as the property has to be supplied
         * with values to properly function within the meta-engine.
         */
        explicit property_impl() = delete;

        /**
         * @brief Constructor for creating a new property_impl object with a member variable functor.
         * 
         * When this constructor is invoked, it will create a new property_impl object that binds the member
         * variable of a class for getting and setting when invoked by the meta engine.
         * 
         * @param name   The name of the property when serialized.
         * @param member The member variable to bind to the property.
         */
		explicit property_impl(const std::string& name, member_ptr<Class, T> member);

        /**
         * @brief Constructor for creating a new property_impl object with a getter and setter which uses referenced values.
         * 
         * When this constructor is invoked, it will create a new property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are referred to by reference.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
		explicit property_impl(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

        /**
         * @brief Constructor for creating a new property_impl object with a getter and setter which uses object values.
         * 
         * When this constructor is invoked, it will create a new property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are referred to by reference.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
		explicit property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter);

        /**
         * @brief Constructor for creating a new property_impl object with a getter and setter which uses referenced or object values.
         * 
         * When this constructor is invoked, it will create a new property_impl object that binds the getter and
         * setter of a class that utilises return values and arguments that are either referenced of by value.
         * 
         * @param name   The name of the property when serialized.
         * @param getter The getter function to bind.
         * @param setter The setter function to bind.
         */
        explicit property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

        /**
         * @brief Default destructor for the propert_impl object.
         */
        virtual ~property_impl() = default;
        
        //====================
        // Getters and setters
        //====================
        /**
         * @brief Retrieves a constant reference of the variable registered with this property.
         * 
         * @param obj The object instance to return the data from.
         * 
         * @returns A constant reference to the underlying mapped data.
         */
        const T& get(const Class& obj) const;

        /**
         * @brief Retrieves a copy of the variable registered with this property.
         * 
         * @param obj The object instance to return the data from.
         * 
         * @returns A copy oo the underlying mapped data.
         */
        T get_copy(const Class& obj) const;

        /**
         * @brief Retrieves a reference of the variable registered with this property.
         * 
         * @param obj The object instance to return the data from.
         * 
         * @returns A reference to the underlying mapped data.
         */
        T& get_reference(Class& obj) const;

        /**
         * @brief Retrieves the member variable pointer this property is mapped to.
         * 
         * If the property_impl object was registered with a pointer directly to a member
         * variable of a class, this can be used to retrieve this pointer and access the data.
         * 
         * @return A pointer to the registered member variable function pointer.
         */
        member_ptr<Class, T> get_member() const;

        /**
         * @brief Sets the data of a property with the specified value.
         * 
         * When this method is invoked, it will set the value of a member variable using either
         * a direct member pointer or setter to change the value of the specified class. The method
         * can only be invoked if the value passed in is constructible.
         * 
         * @param obj   The class to set the value within.
         * @param value The value to set within the class.
         */
        template <typename V, typename = std::enable_if_t<std::is_constructible<T, V>::value>>
        void set(Class& obj, V&& value) const;

        /**
         * @brief Retrieves the name of the property object.
         * 
         * When a property is registered with the meta engine, it is paired with a name,
         * which represents the value when the class is serialized.
         * 
         * @returns The name of the property object.
         */      
        const std::string& get_name() const;

        /**
         * @brief Checks whether a member function pointer has been registered with the property.
         * 
         * As the property supports access to member variables with through getters, setters or direct
         * member pointer, this method can be used to check if a member pointer has been registered with the
         * property.
         * 
         * @returns True if a member pointer has been registered.
         */
        bool has_member() const;

        /**
         * @brief Checks whether a getter method has been registered with the property.
         * 
         * As the property supports access to member variables with through getters, setters or direct
         * member pointer, this method can be used to check if a getter method pointer has been registered with the
         * property.
         * 
         * @returns True if a member pointer has been registered.
         */
        bool has_getter() const;

        /**
         * @brief Checks whether a setter method has been registered with the property.
         * 
         * As the property supports access to member variables with through getters, setters or direct
         * member pointer, this method can be used to check if a setter method has been registered with the
         * property.
         * 
         * @returns True if a member pointer has been registered.
         */
        bool has_setter() const;

        /**
         * @brief Checks whether a member function pointer has been registered with the property.
         * 
         * As the property supports access to member variables with through getters, setters or direct
         * member pointer, this method can be used to check if a member pointer has been registered with the
         * property.
         * 
         * @returns True if a member pointer has been registered.
         */
        bool can_get_const_ref() const;

        /**
         * @brief Checks if this property is registered with a enumeration.
         * 
         * Enumerations can be registered in a special manner when exposing classes to the meta-engine.
         * This method will check if this property has wrapped a enumerated type.
         * 
         * @returns True if the property_impl object is exposing an enumerated type.
         */
        bool is_enum() const;

        //====================
        // Methods
        //====================
        /**
         * @brief Converts the property_impl object into a enum_property_impl object.
         * 
         * When the property_impl is cast to the enum property, if the property object is not
         * registered as an enum, it will throw an exception.
         * 
         * @returns A new enum_property_impl object.
         * 
         * @throws meta_exception is the property does not use a registered enumerated type.
         */
        enum_property_impl<Class, T> as_enum() const;
    };

    //====================
    // Functions
    //====================
    /**
     * @brief Convenience method for creating a new property_impl object with a member variable functor.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param member The member variable to bind to the property.
     * 
     * @returns A new property_impl object with a bound member variable functor.
     */
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, member_ptr<Class, T> member);

	/**
	* @brief Convenience method for creating a new property_impl object with reference getter.
	*
	* These functions are used to quickly bind properties on a class, without having to insert the template
	* types when creating property_impl objects. They should only be invoked when registering a new class to the
	* meta-engine. This property is only declared as readonly, attempting to set the value will result in an 
	* exception being thrown.
	*
	* @param name   The name of the property when serialized.
	* @param getter The getter method functor which returns an object by reference.
	* @param setter The setter method functor which takes an object by reference for an argument.
	*
	* @returns A new property_impl object with a bound referenced getter and setter functors.
	*
	* @throws runtime_error If the property is attempting to set the value.
	*/
	template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, ref_getter_func_ptr<Class, T> getter);

	/**
	* @brief Convenience method for creating a new property_impl object with by value getter.
	*
	* These functions are used to quickly bind properties on a class, without having to insert the template
	* types when creating property_impl objects. They should only be invoked when registering a new class to the
	* meta-engine. This property is only declared as readonly, attempting to set the value will result in an 
	* exception being thrown.
	*
	* @param name   The name of the property when serialized.
	* @param getter The getter method functor which returns an object by value.
	* @param setter The setter method functor which takes an object by value for an argument.
	*
	* @returns A new property_impl object with a bound value based getter and setter functors.
	*
	* @throws runtime_error If the property is attempting to set the value.
	*/
	template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter);

    /**
     * @brief Convenience method for creating a new property_impl object with reference getters and setters.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by reference.
     * @param setter The setter method functor which takes an object by reference for an argument.
     * 
     * @returns A new property_impl object with a bound referenced getter and setter functors.
     */
    template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

    /**
     * @brief Convenience method for creating a new property_impl object with by value getters and setters.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by value.
     * @param setter The setter method functor which takes an object by value for an argument.
     * 
     * @returns A new property_impl object with a bound value based getter and setter functors.
     */
    template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter);

    /**
     * @brief Convenience method for creating a new property_impl object with a value getter and a setter which takes a referenced parameter.
     * 
     * These functions are used to quickly bind properties on a class, without having to insert the template
     * types when creating property_impl objects. They should only be invoked when registering a new class to the
     * meta-engine.
     * 
     * @param name   The name of the property when serialized.
     * @param getter The getter method functor which returns an object by value.
     * @param setter The setter method functor which takes an object by reference for an argument.
     * 
     * @returns A new property_impl object with a bound value-based getter and reference-based setter functors.
     */
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter);

} // namespace reflect

//====================
// Reflect includes
//====================
#include "property.inl" // Method declarations.

#endif//_REFLECT_PROPERTY_HPP_