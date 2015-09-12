/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef effect_paddle_h
#define effect_paddle_h

#include "collision.h"
#include "sprite.h"

class Effect_Paddle{
public:

    Collision_Rect box;
    Collision_Rect box_start;

    Sprite sprite;

    bool exists;

    double scale;
    double angle;

    bool headed_to_mid;

    Effect_Paddle(double x,double y);

    void movement();

    void render();
};

#endif
