/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_constant.h"
#include "world.h"

using namespace std;

double ZOOM_RATE=0.0;
double ZOOM_MIN=0.0;
double ZOOM_MAX=0.0;

Game_Constant::Game_Constant(){
    name="";
}

void Game_Constant::set_value(string new_value){
    if(name=="zoom_rate"){
        ZOOM_RATE=string_stuff.string_to_double(new_value);
    }
    else if(name=="zoom_min"){
        ZOOM_MIN=string_stuff.string_to_double(new_value);
    }
    else if(name=="zoom_max"){
        ZOOM_MAX=string_stuff.string_to_double(new_value);
    }
}
