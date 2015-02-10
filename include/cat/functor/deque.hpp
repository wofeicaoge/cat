#pragma once

#include <deque>

#include <cat/functor/functor.hpp>


namespace cat
{
    // deque is a functor:
    //

    template <> struct is_functor<std::deque> : std::true_type { };

    // deque instance:
    //

    template <typename Fun, typename A, typename Alloc>
    struct FunctorInstance<std::deque, Fun, A, Alloc> : Functor<std::deque>::Class<Fun, A, Alloc>
    {
        using B = decltype(std::declval<Fun>()(std::declval<A>()));

        std::deque<B, rebind_t<Alloc, B>>
        fmap(Fun f, std::deque<A, Alloc> const &xs) final
        {
            std::deque<B, rebind_t<Alloc, B> > out;

            for(auto & x : xs)
                out.push_back(f(x));

            return out;
        }
    };

} // namespace cat
