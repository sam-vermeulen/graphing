#pragma once

#include "window.h"
#include "events/window_event.h"

int main(int argc, char** argv);

class application {
public:
    application();

    void on_event(event& e);

    virtual void on_update() = 0;

    window& get_window() { return *m_window; }

    static application& get() { return *s_instance; }

private:
    void run();
    void on_window_close(window_close_event& e);
    void on_window_resize(window_resize_event& e);

    std::unique_ptr<window> m_window;
    bool m_running = true;
    
    static application* s_instance;
    
    friend int ::main(int argc, char** argv);
};

application* create_application();