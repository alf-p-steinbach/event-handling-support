#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/all.hpp>

namespace event_handling_support {
    $use_cppx( No_copy, Type_ );

    template< class Event_source, class Observer_interface  >
    inline void add_observer(
        const Type_<Event_source*>          p_source, 
        const Type_<Observer_interface*>    p_observer
        )
    {
        p_source->add_observer( p_observer );
    }

    template< class Event_source, class Observer_interface  >
    inline void remove_observer(
        const Type_<Event_source*>          p_source, 
        const Type_<Observer_interface*>    p_observer
        )
    {
        p_source->remove_observer( p_observer );
    }

    template< class Observer_interface_, class Event_source_ >
    class Observation_ final
        : public No_copy
    {
    public:
        using Observer_interface    = Observer_interface_;
        using Event_source          = Event_source_;

    private:
        Observer_interface*     m_p_observer;
        Event_source*           m_p_source;

    public:
        ~Observation_()
        {
            if( m_p_source ) {
                remove_observer( m_p_source, m_p_observer );
            }
        }

        Observation_(
            const Type_<Observer_interface*>    p_observer,
            const Type_<Event_source*>          p_source
            ):
            m_p_observer( p_observer ),
            m_p_source( p_source )
        {
            add_observer( m_p_source, m_p_observer );
        }

        Observation_( Observation_&& other ):
            m_p_observer( exchange( other.m_p_observer, nullptr ) ),
            m_p_source( exchange( other.m_p_source, nullptr ) )
        {}

        auto observer() const       -> Observer_interface*  { return m_p_observer; }
        auto event_source() const   -> Event_source*        { return m_p_source; }
    };

}  // namespace event_handling_support
