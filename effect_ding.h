#ifndef effect_ding_h
#define effect_ding_h

#include "collision.h"
#include "sprite.h"

class Effect_Ding{
public:

    Collision_Rect box;

    Sprite sprite;

    bool exists;

    Effect_Ding(double x,double y,std::string sprite_name);

    void animate();
    void render();
};

#endif
