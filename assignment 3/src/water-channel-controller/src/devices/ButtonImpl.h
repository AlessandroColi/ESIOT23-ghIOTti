#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"

class ButtonImpl : public Button 
{
    public:
        ButtonImpl(int pin);
        bool isPressed() = 0;
        bool isClicked() = 0;

        void sync();
    
    private:
        int pin;
        bool pressed;
        bool clicked;
};

#endif