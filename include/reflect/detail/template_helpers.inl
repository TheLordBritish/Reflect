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
    namespace detail 
    {
        //====================
        // Functions
        //====================
        /**********************************************************/
        template <typename F, typename... Args>
        void for_each(F&& f, Args&&... args)
        {
            using expand = bool[];
            (void)expand {( f(std::forward<Args>(args)), true )...};
        }

        /**********************************************************/
        template <typename F, typename Tuple, size_t... I>
        decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
        {
            return f(std::get<I>(std::forward<Tuple>(t))...);
        }

        /**********************************************************/
        template <typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t)
        {
            constexpr size_t size = std::tuple_size<std::decay_t<Tuple>>::value;
            return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<size>());
        }

        /**********************************************************/
        template <typename F, typename T>
        void for_tuple(F&& f, T&& tuple)
        {
            apply([&f](auto&&... elems) { 
                for_each(f, std::forward<decltype(elems)>(elems)...); 
            }, std::forward<T>(tuple));
        }

        /**********************************************************/
        template <typename F>
        void for_tuple(F&& f, const std::tuple<>& tuple)
        {
            // Empty.
        }

        /**********************************************************/
        template <bool Test, typename F, typename... Args, typename>
        void call_if(F&& f, Args&&... args)
        {
            f(std::forward<Args>(args)...);
        }

        /**********************************************************/
        template <bool Test, typename F, typename... Args, typename, typename>
        void call_if(F&& f, Args&&... args)
        {
            // Empty.
        }

    } // namespace detail

} // namespace reflect