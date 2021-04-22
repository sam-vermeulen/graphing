#include "application.h"

#include <memory>

#include "events/event_handler.h"
#include "events/window_event.h"

application* application::s_instance = nullptr;

application::application() {
    s_instance = this;
    m_window = std::make_unique<window>("hello", 500, 500);

    m_window->set_event_callback([this](event& e) -> void {
        return this->on_event(e);
    });
}

void application::on_event(event& e) {
    event_handler handler(e);
    handler.handle<window_close_event>([this](window_close_event& e) -> void {
        return this->on_window_close(e);
    });
    handler.handle<window_resize_event>([this](window_resize_event& e) -> void {
        return this->on_window_resize(e);
    });
}

void application::run() {
    while(m_running) {
        m_window->on_update();
    }
}

void application::on_window_close(window_close_event& e) {
    m_running = false;
}

void application::on_window_resize(window_resize_event& e) {

}
