/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "cloud.h"
#include "world.h"

using namespace std;

Cloud::Cloud(){
    sprite.set_name("cloud");

    box.x=0.0;
    box.y=0.0;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    velocity.magnitude=0.0;
    velocity.direction=0.0;
}

Cloud::Cloud(double x,double y,double direction){
    sprite.set_name("cloud");

    box.x=x;
    box.y=y;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    velocity.magnitude=341.333;
    velocity.direction=direction;
}

void Cloud::handle_collisions(){
    Object::handle_collisions();

    for(int i=0;i<balls.size();i++){
        Ball* ball=&balls[i];

        if(ball->is_interactive() && collision_check_rect(box,ball->box)){
            ball->velocity=velocity.opposite();

            if(game.effect_allowed()){
                effects_ding.push_back(Effect_Ding(box.x,box.y,"puff"));
            }

            sound_system.play_sound("cloud_hit_ball",box.x,box.y);
        }
    }

    for(int i=0;i<paddles.size();i++){
        Paddle* paddle=&paddles[i];

        if(paddle->is_interactive() && collision_check_rect(box,paddle->box)){
            paddle->stun();

            alive=false;

            if(game.effect_allowed()){
                effects_ding.push_back(Effect_Ding(box.x,box.y,"puff_large"));
            }

            if(network.get_our_player_number()==i){
                game.screen_shake.add_shake(0.99,300);
                engine_interface.make_rumble(CONTROLLER_ID_ALL,1.0f,300);
            }

            sound_system.play_sound("cloud_hit_paddle",box.x,box.y);

            return;
        }
    }

    if(box.x+box.w<0.0){
        alive=false;

        return;
    }
    else if(box.x>game.world_x){
        alive=false;

        return;
    }
}
