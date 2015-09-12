/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "effect_ding.h"
#include "world.h"

using namespace std;

Effect_Ding::Effect_Ding(double x,double y,string sprite_name){
    sprite.set_name(sprite_name);

    box.x=x;
    box.y=y;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    exists=true;
}

void Effect_Ding::animate(){
    sprite.animate();

    if(!sprite.animating){
        exists=false;
    }
}

void Effect_Ding::render(){
    if(exists && collision_check_rect(box*game.camera_zoom,game.camera)){
        sprite.render(box.x*game.camera_zoom-game.camera.x,box.y*game.camera_zoom-game.camera.y);
    }
}
