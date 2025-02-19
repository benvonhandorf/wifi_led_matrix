
#ifndef COMMON_COMMANDINTERFACE_H_
#define COMMON_COMMANDINTERFACE_H_

class CommandInterface {
    public:
        virtual void inc() = 0;
        virtual void dec() = 0;
        virtual void randomize() = 0;
        virtual void energy(uint8_t energy_level) = 0;
        virtual void color_data(uint8_t *color_data) = 0;
};

#endif