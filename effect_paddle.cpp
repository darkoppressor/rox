/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "effect_paddle.h"
#include "world.h"

using namespace std;

Effect_Paddle::Effect_Paddle(double x,double y){
    sprite.set_name("paddle");

    box.x=x;
    box.y=y;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    box_start=box;
    box_start.y=0;

    exists=true;

    scale=1.0;
    angle=0.0;

    headed_to_mid=true;
}

void Effect_Paddle::movement(){
    if(exists){
        scale+=3.5/UPDATE_RATE;
        angle+=360.0/UPDATE_RATE;

        Collision_Rect box_target;
        box_target.w=8.0;
        box_target.h=8.0;
        box_target.x=game.camera.center_x()-box_target.w/2.0;
        box_target.y=game.camera.center_y()-box_target.h/2.0;
        if(!headed_to_mid){
            box_target=box_start;
        }

        Vector velocity(298.667,get_angle_to_rect(box,box_target,game.camera));

        Vector_Components vc=velocity.get_components();

        box.x+=vc.a/UPDATE_RATE;
        box.y+=vc.b/UPDATE_RATE;

        if(headed_to_mid && collision_check_rect(box,box_target)){
            headed_to_mid=false;
        }

        if(scale>=4.0){
            exists=false;
        }
    }
}

void Effect_Paddle::render(){
    if(exists && collision_check_rect(box*game.camera_zoom,game.camera)){
        sprite.render(box.x*game.camera_zoom-game.camera.x,box.y*game.camera_zoom-game.camera.y,1.0,scale,scale,angle);
    }
}
