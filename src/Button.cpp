
#include "Button.h"

Button::Button(uint8_t pin, void (*callback)(uint8_t, uint8_t), uint16_t debounce)
{
    _pin = pin;
    _callback = callback;
    _debounce = debounce;
    _time = 0;
    _state = 0xff;
}

void Button::setCallback(void (*callback)(uint8_t, uint8_t))
{
    _callback = callback;
}

void Button::begin(void)
{
    pinMode(_pin, INPUT);
    _time = millis();
    _state = ::digitalRead(_pin);
}

void Button::update(void)
{
    if (_state == 0xff)
    {
        return;
    }
    
    uint16_t t = millis();
    if (t != _time)
    {
        uint8_t reading = ::digitalRead(_pin);
        
        if (reading != _state)
        {
            _time = t;
        }
        
        if ((t - _time) >= _debounce && reading != _state)
        {
            _state = reading;
            if (_callback)
            {
                _callback(_pin, _state);
            }
        }
    }
}

uint8_t Button::digitalRead(void)
{
    return _state;
}

