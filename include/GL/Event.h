#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "GL/Subscriber.h"
#include "Types.h"


namespace engine {
using event_t = u8;

enum class EventType {
	WindowResize = 0,
    KeyUpdate,
    MouseMove,
    MouseScroll
};

template<class ...Args>
class Event
{
public:
    Event(event_t type)
    {
        if (eventlist().find(type) != eventlist().end())
        {
            Event* o = eventlist()[type];
            this->_subscribers = o->_subscribers;
            this->_evnt = o->_evnt;
        }
        else
        {
            _evnt = type;
            eventlist()[_evnt] = this;
        }
    }

    ~Event()
    {
        eventlist().erase(_evnt);
    }


    inline void add_subscriber(std::function<void(Args...)> f)
    { 
        _subscribers.emplace_back(Subscriber<Args...>::create(f));
    }

    void publish(Args... args)
    {
        for (std::size_t i{}; i != _subscribers.size(); i++)
        {
            _subscribers[i]->notify(args...);
        }
    }

private:
	static inline std::unordered_map<event_t, Event*>& eventlist()
	{
		static auto eventlist = new std::unordered_map<event_t, Event*>;
		return *eventlist;
	}

private:
    std::vector<std::shared_ptr<Subscriber<Args...>>> _subscribers;
	event_t _evnt;
};

}
