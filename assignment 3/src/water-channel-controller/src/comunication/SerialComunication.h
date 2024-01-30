#ifndef __SERIAL_COMUNICATION__
#define __SERIAL_COMUNICATION__

#include "model/SmartRiver.h"
#include "config.h"

class SerialComunication
{
    public:
        SerialComunication(SmartRiver* smartRiver);
        void init();
        void update();
        bool isMessageAvailable();
        String getMessage();

    private:
        static SmartRiver* smartRiver;
};

#endif