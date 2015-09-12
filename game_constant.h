/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_constant_h
#define game_constant_h

#include <string>

extern double ZOOM_RATE;
extern double ZOOM_MIN;
extern double ZOOM_MAX;

class Game_Constant{
public:

    std::string name;

    Game_Constant();

    void set_value(std::string new_value);
};

#endif
