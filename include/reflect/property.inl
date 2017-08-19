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
#include "detail/meta_exception.hpp" // Throwing meta exceptions.

namespace reflect
{
    //====================
    // Ctors and dtor
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T>::property_impl(const std::string& name, member_ptr<Class, T> member) 
        : m_name(name), m_member(member), m_has_member(true), m_ref_getter(nullptr), m_ref_setter(nullptr), m_val_getter(nullptr), m_val_setter(nullptr)
    { 
        // Empty.
    }

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T>::property_impl(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter) 
        : m_name(name), m_member(nullptr), m_has_member(false), m_ref_getter(getter), m_ref_setter(setter), m_val_getter(nullptr), m_val_setter(nullptr)
    {
        // Empty.
    }

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T>::property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter) 
        : m_name(name), m_member(nullptr), m_has_member(false), m_ref_getter(nullptr), m_ref_setter(nullptr), m_val_getter(getter), m_val_setter(setter)
    { 
        // Empty.
    }

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T>::property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter) 
        : m_name(name), m_member(nullptr), m_has_member(false), m_ref_getter(nullptr), m_ref_setter(setter), m_val_getter(getter), m_val_setter(nullptr)
    { 
        // Empty.
    }

    //====================
    // Getters and setters
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    const T& property_impl<Class, T>::get(const Class& obj) const
    {
        if (m_ref_getter) 
        {
            return (obj.*m_ref_getter)();
        } 
		else if (m_val_getter)
		{
			return (obj.*m_val_getter)();
		}
        else if (m_has_member) 
        {
            return obj.*m_member;
        }

        throw detail::meta_exception("Cannot return const reference to member variable: no getter function or member pointer set.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    T property_impl<Class, T>::get_copy(const Class& obj) const
    {
        if (m_val_getter)
        {
            return (obj.*m_val_getter)();
        } 
        else if (m_ref_getter) 
        {
            return (obj.*m_ref_getter)();
        } 
        else if (this->has_member()) 
        {
            return obj.*m_member;
        }

        throw detail::meta_exception("Cannot return copy of member variable: no getter function or member pointer set.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    T& property_impl<Class, T>::get_reference(Class& obj) const
    {
        if(this->has_member()) 
        {
            return obj.*m_member;
        }

        throw detail::meta_exception("Cannot return reference of member variable: no member pointer set.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    member_ptr<Class, T> property_impl<Class, T>::get_member() const {
        if (this->has_member()) 
        {
            return m_member;
        }

        throw detail::meta_exception("Cannot retrieve pointer to member variable: no member pointer set.");
    }

    /**********************************************************/
    template<typename Class, typename T>
    template <typename V, typename>
    void property_impl<Class, T>::set(Class& obj, V&& value) const
    {
        if (m_ref_setter) 
        {
            (obj.*m_ref_setter)(value);
        } 
        else if (m_val_setter) 
        {
            (obj.*m_val_setter)(value);
        } 
        else if (this->has_member()) 
        {
            obj.*m_member = value;
        }
		else
		{
			throw detail::meta_exception("Cannot set value: no setters or member pointer set.");
		}
    }

    /**********************************************************/
    template<typename Class, typename T>
    const std::string& property_impl<Class, T>::get_name() const
    {
        return m_name;
    }

    /**********************************************************/
    template<typename Class, typename T>
    bool property_impl<Class, T>::has_member() const
    {
        return m_has_member || m_member; 
    }

    /**********************************************************/
    template <typename Class, typename T>
    bool property_impl<Class, T>::has_getter() const
    {
        return m_ref_getter || m_val_getter;
    }

    /**********************************************************/
    template <typename Class, typename T>
    bool property_impl<Class, T>::has_setter() const
    {
        return m_ref_setter || m_val_setter;
    }

    /**********************************************************/
    template <typename Class, typename T>
    bool property_impl<Class, T>::can_get_const_ref() const
    {
        return m_has_member || m_ref_getter;
    }

    /**********************************************************/
    template <typename Class, typename T>
    bool property_impl<Class, T>::is_enum() const
    {
        return std::is_enum<T>::value;
    }

    //====================
    // Methods
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    enum_property_impl<Class, T> property_impl<Class, T>::as_enum() const
    {
        if (!this->is_enum())
        {
            throw detail::meta_exception("Property is not registered to an enumerated type.");
        }

        return static_cast<enum_property_impl<Class, T>&>(*this);
    }

    //====================
    // Functions
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, member_ptr<Class, T> member)
    {
        return property_impl<Class, T>(name, member);
    }

	/**********************************************************/
	template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, ref_getter_func_ptr<Class, T> getter)
	{
		return property_impl<Class, T>(name, getter, ref_setter_func_ptr<Class, T>(nullptr));
	}

	/**********************************************************/
	template <typename Class, typename T>
	property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter)
	{
		return property_impl<Class, T>(name, getter, val_setter_func_ptr<Class, T>(nullptr));
	}

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
    {
        return property_impl<Class, T>(name, getter, setter);
    }

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter)
    {
        return property_impl<Class, T>(name, getter, setter);
    }

    /**********************************************************/
    template <typename Class, typename T>
    property_impl<Class, T> property(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
    {
        return property_impl<Class, T>(name, getter, setter);
    }

} // end of namespace reflect
