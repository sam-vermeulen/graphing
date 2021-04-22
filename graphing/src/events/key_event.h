#pragma once

#include <cinttypes>

#include "event.h"

class key_pressed_event : public event {
public:
    key_pressed_event(const uint16_t keycode, const uint16_t repeat) : m_keycode(keycode), m_repeat(repeat) {}

    EVENT_TYPE(key_pressed)

    uint16_t get_repeat() {
        return m_repeat;
    }

    uint16_t get_key_code() const {
        return m_keycode;
    }

private:
    uint16_t m_keycode;
    uint16_t m_repeat;
};

class key_released_event : public event {
public:
    key_released_event(const uint16_t keycode) : m_keycode(keycode) {}

    EVENT_TYPE(key_released)

    uint16_t get_key_code() const {
        return m_keycode;
    }

private:
    uint16_t m_keycode;
};

class key_typed_event : public event {
public:
    key_typed_event(const uint16_t keycode) : m_keycode(keycode) {}

    EVENT_TYPE(key_typed)

    uint16_t get_key_code() const {
        return m_keycode;
    }

private:
    uint16_t m_keycode;
};