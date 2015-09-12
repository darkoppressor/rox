/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "paddle.h"
#include "world.h"

using namespace std;

Paddle::Paddle(){
    sprite.set_name("paddle");

    box.x=0.0;
    box.y=0.0;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    score=0;
    stunned=0;
    counter_cooldown=0;
}

Paddle::Paddle(double x,double y){
    sprite.set_name("paddle");

    box.x=x;
    box.y=y;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    score=0;

    stunned=0;

    counter_cooldown=0;
}

void Paddle::restart(){
    box.y=(game.world_y-box.h)/2.0;

    score=0;
    stunned=0;
    counter_cooldown=0;
}

bool Paddle::is_stunned(){
    if(stunned==0){
        return false;
    }
    else{
        return true;
    }
}

bool Paddle::is_interactive(){
    if(!is_stunned()){
        return Object::is_interactive();
    }
    else{
        return false;
    }
}

bool Paddle::is_cooled(){
    if(counter_cooldown==0){
        return true;
    }
    else{
        return false;
    }
}

void Paddle::stun(){
    if(!is_stunned()){
        stunned=(int)ceil(1.5*UPDATE_RATE);

        if(game.effect_allowed()){
            effects_paddle.push_back(Effect_Paddle(box.x,box.y));
        }
    }
}

void Paddle::use_ability(int index){
    if(is_cooled()){
        counter_cooldown=(int)ceil(5.0*UPDATE_RATE);

        double direction=0.0;
        double x=box.x+box.w;
        if(index==1){
            direction=180.0;
            x=box.x-16.0;
        }

        clouds.push_back(Cloud(x,box.y+(box.h-8.0)/2.0,direction));

        sound_system.play_sound("cloud_spawn",box.x,box.y);
    }
}

void Paddle::ai(int index){
    if(is_interactive()){
        string move_state="";

        Ball* ball=0;

        if(balls.size()>=1){
            ball=&balls[0];
        }

        if(ball!=0){
            if(ball->box.y<box.y){
                move_state="up";
            }
            else if(ball->box.y+ball->box.h>box.y+box.h){
                move_state="down";
            }

            if(ball->box.center_y()>=box.y && ball->box.center_y()<=box.y+box.h){
                if(is_cooled() && game.rng.random_range(0,99)<1){
                    use_ability(index);
                }
            }
        }
        else{
            if(is_cooled() && game.rng.random_range(0,999)<1){
                use_ability(index);
            }
        }

        if(move_state=="up"){
            velocity.direction=90.0;
            velocity.magnitude=144.0;
        }
        else if(move_state=="down"){
            velocity.direction=270.0;
            velocity.magnitude=144.0;
        }
        else{
            velocity.direction=0.0;
            velocity.magnitude=0.0;
        }
    }
}

void Paddle::movement(){
    if(is_stunned()){
        stunned--;

        if(!is_stunned()){
            sound_system.play_sound("paddle_unstun",box.x,box.y);
        }
    }

    if(!is_cooled()){
        counter_cooldown--;

        if(is_cooled()){
            if(is_stunned()){
                counter_cooldown++;
            }
            else{
                if(game.effect_allowed()){
                    effects_ding.push_back(Effect_Ding(box.x-(16.0-box.w)/2.0,box.y,"ding"));
                }

                sound_system.play_sound("ding",box.x,box.y);
            }
        }
    }

    if(!is_stunned()){
        Object::movement();
    }
}

void Paddle::handle_collisions(){
    Object::handle_collisions();

    if(box.x<0.0){
        box.x=0.0;
    }
    else if(box.x+box.w>game.world_x){
        box.x=game.world_x-box.w;
    }

    if(box.y<0.0){
        box.y=0.0;
    }
    else if(box.y+box.h>game.world_y){
        box.y=game.world_y-box.h;
    }
}
