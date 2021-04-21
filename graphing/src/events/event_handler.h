#pragma once

#include <functional>

#include "event.h"

class event_handler {
public:
    event_handler(event& e) : m_event(e) {}

    template <typename T>
    void handle(std::function<void(T&)> func) {
        if (m_event == T::static_type()) {
            func(*(T*)&m_event);
        }
    }
private:
    event& m_event;
};