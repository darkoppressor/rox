#ifndef paddle_h
#define paddle_h

#include "object.h"

class Paddle: public Object{
public:

    uint32_t score;

    int stunned;

    int counter_cooldown;

    Paddle();
    Paddle(double x,double y);

    void restart();

    bool is_stunned();
    bool is_interactive();

    bool is_cooled();

    void stun();

    void use_ability(int index);

    void ai(int index);

    void movement();
    void handle_collisions();
};

#endif
