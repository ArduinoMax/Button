#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <stdint.h>

enum
{
    /*!
     The button is pressed.
     */
    BUTTON_PRESSED = HIGH,
    
    /*!
     The button is released.
     */
    BUTTON_RELEASED = LOW
};

/// Debounced button interface.
class Button
{
private:
    void (*_callback)(uint8_t pin, uint8_t event);
    uint8_t _pin;
    uint16_t _debounce;
    uint16_t _time;
    uint8_t _state;
    
public:
    /*!
     Initialize an debounced button.
     
     @param pin      The pin the button is attached to.
     @param callback The event callback function.
     @param debounce Debounce timeout.
     */
    Button(uint8_t pin, void (*callback)(uint8_t, uint8_t) = nullptr, uint16_t debounce = 10);
    
    /*!
     Set the event callback function.
     
     @param callback The event callback function.
     */
    void setCallback(void (*callback)(uint8_t, uint8_t));
    
    /*!
     Prepare the button debouncer.
     */
    void begin(void);
    
    /*!
     Check the button status.
     */
    void update(void);
    
    /*!
     Get the button's actual status.
     
     @return Debounced button status.
     */
    uint8_t digitalRead(void);
};

#endif
