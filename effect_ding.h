/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

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
