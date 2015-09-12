/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef tile_h
#define tile_h

#include "sprite.h"
#include "collision.h"

class Tile{
public:

    Sprite sprite;

    int counter_animation_boost;
    int animation_boost;

    Tile();

    Collision_Rect get_box(uint32_t x,uint32_t y);

    void whack(double magnitude);

    void animate(bool menu=false);
    void render(uint32_t x,uint32_t y,bool menu=false);
};

#endif
