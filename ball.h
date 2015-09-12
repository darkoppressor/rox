/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef ball_h
#define ball_h

#include "object.h"

class Ball: public Object{
public:

    int counter_rubble;

    Ball();
    Ball(double x,double y);

    void movement();
    void handle_collisions();

    void rebound(bool horizontal);
};

#endif
