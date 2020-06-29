#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/all.hpp>

#include <unordered_set>    // std::unordered_set

namespace event_handling_support {
    $use_cppx(
        With_derived_, No_copy, Type_,
        Require_, is_same_type_
        );
    $use_std( unordered_set );

    template<
        class Derived_param, class Observer_interface_param,
        class = Require_<is_same_type_<
            Derived_param,
            With_derived_<typename Derived_param::Derived>
            >>
        >
    class Observable_:
        public No_copy
    {
    public:
        using Derived               = typename Derived_param::Derived;
        using Observer_interface    = Observer_interface_param;

    private:
        unordered_set<Observer_interface*>  m_observers;

    protected:
        template< class Func >
        void for_each_observer( const Func& f )
        {
            for( const auto p_observer: m_observers ) {
                f( p_observer );
            }
        }

    public:
        void add_observer( const Type_<Observer_interface*> p_observer )
        {
            m_observers.insert( p_observer );
        }

        void remove_observer( const Type_<Observer_interface*> p_observer )
        {
            m_observers.erase( p_observer );
        }
    };

}  // namespace event_handling_support
