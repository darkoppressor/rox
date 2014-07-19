#ifndef object_h
#define object_h

#include "collision.h"
#include "vector.h"
#include "sprite.h"

class Object{
public:

    Collision_Rect box;

    Vector velocity;

    Sprite sprite;

    bool alive;

    Object();

    virtual bool is_interactive();

    virtual void movement();
    virtual void handle_collisions();

    void render();
};

#endif
