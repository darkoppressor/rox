/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef cloud_h
#define cloud_h

#include "object.h"

class Cloud: public Object{
public:

    Cloud();
    Cloud(double x,double y,double direction);

    void handle_collisions();
};

#endif
