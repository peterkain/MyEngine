#pragma once

#include <functional>

namespace engine {

template<class ...Args>
class Subscriber
{
    template<class ...Args>
    friend class Event;

    struct SubscriberMakeShared : public Subscriber<Args...>
    {
        SubscriberMakeShared(std::function<void(Args...)> f) :
            Subscriber<Args...>(f)
        {}
    };
public:
    static std::shared_ptr<Subscriber<Args...>> create(std::function<void(Args...)> f)
    {
        return std::make_shared<SubscriberMakeShared>(f);
    }
private:
    Subscriber(std::function<void(Args...)> f) :
        _func{ std::move(f) }
    {
    }

private:
    void notify(Args... args)
    {
        _func(args...);
    }

private:
    std::function<void(Args...)> _func;
};

}
