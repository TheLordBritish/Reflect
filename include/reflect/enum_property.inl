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

namespace reflect
{
    //========================================
    // enum_property_hash
    //========================================
    //====================
    // Operators
    //====================
    /**********************************************************/
    template <typename T>
    template <typename>
    std::size_t enum_property_hash<T>::operator()(T const& value) const
    {
        using type = typename std::underlying_type<T>::type;
        const type val = static_cast<type>(value);

        std::hash<type> hash;
        return hash(val);
    }

    //========================================
    // enum_property_impl
    //========================================
    //====================
    // Ctors and dtor
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    enum_property_impl<Class, T>::enum_property_impl(const std::string& name, member_ptr<Class, T> member)
        : property_impl(name, member)
    {
        // Empty.
    }    

    /**********************************************************/
    template <typename Class, typename T>
    enum_property_impl<Class, T>::enum_property_impl(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
        : property_impl(name, getter, setter)
    {
        // Empty.
    }

    /**********************************************************/
    template <typename Class, typename T>
    enum_property_impl<Class, T>::enum_property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter)
        : property_impl(name, getter, setter)
    {
        // Empty.
    }

    /**********************************************************/
    template <typename Class, typename T>
    enum_property_impl<Class, T>::enum_property_impl(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
        : property_impl(name, getter, setter)
    {
        // Empty.
    }

    //====================
    // Private methods
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<!std::is_enum<U>::value, empty_map<U, U>>::type enum_property_impl<Class, T>::to_string_map() const
    {
        throw detail::meta_exception("Called to_string_map on a non-enumerated type.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<std::is_enum<U>::value, to_string_map_type<U>&>::type enum_property_impl<Class, T>::to_string_map() const
    {
        static to_string_map_type<U> map;
        return map;
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<!std::is_enum<U>::value, empty_map<U, U>>::type enum_property_impl<Class, T>::from_string_map() const
    {
        throw detail::meta_exception("Called from_string_map on a non-enumerated type.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<std::is_enum<U>::value, from_string_map_type<U>&>::type enum_property_impl<Class, T>::from_string_map() const
    {
        static from_string_map_type<U> map;
        return map;
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<!std::is_enum<U>::value, enum_property_impl<Class, T>&>::type enum_property_impl<Class, T>::set_value(const std::string& name, T value)
    {
        throw detail::meta_exception("Called value on a non-enumerated type.");
    }

    //====================
    // Methods
    //====================
    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<std::is_enum<U>::value, enum_property_impl<Class, T>&>::type enum_property_impl<Class, T>::set_value(const std::string& name, T value)
    {
        auto& to_map = this->to_string_map();
        auto& from_map = this->from_string_map();

        to_map[value] = name;
        from_map[name] = value;

        return *this;
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<std::is_enum<U>::value, std::string&>::type enum_property_impl<Class, T>::to_string(const T value) const
    {
        return this->to_string_map().at(value);
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<!std::is_enum<U>::value, std::string&>::type enum_property_impl<Class, T>::to_string(const T value) const
    {
        throw detail::meta_exception("Called to_string on non-enumerated property.");
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<std::is_enum<U>::value, U>::type enum_property_impl<Class, T>::from_string(const std::string& name) const
    {
        return this->from_string_map().at(name);
    }

    /**********************************************************/
    template <typename Class, typename T>
    template <typename U>
    typename std::enable_if<!std::is_enum<U>::value, U>::type enum_property_impl<Class, T>::from_string(const std::string& name) const
    {
        throw detail::meta_exception("Called from_string on non-enumerated property.");
    }

    //====================
    // Functions
    //====================
    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, member_ptr<Class, T> member)
    {
        return enum_property_impl<Class, T>(name, member);
    }

    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, ref_getter_func_ptr<Class, T> getter)
    {
        return enum_property_impl<Class, T>(name, getter, ref_setter_func_ptr<Class, T>(nullptr));
    }

    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter)
    {
        return enum_property_impl<Class, T>(name, getter, val_setter_func_ptr<Class, T>(nullptr));
    }

    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, ref_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
    {
        return enum_property_impl<Class, T>(name, getter, setter);
    }

    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter, val_setter_func_ptr<Class, T> setter)
    {
        return enum_property_impl<Class, T>(name, getter, setter);
    }

    /**********************************************************/
    template <typename Class, typename T, typename>
    enum_property_impl<Class, T> enum_property(const std::string& name, val_getter_func_ptr<Class, T> getter, ref_setter_func_ptr<Class, T> setter)
    {
        return enum_property_impl<Class, T>(name, getter, setter);
    }

} // namespace reflect