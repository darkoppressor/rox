/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "ball.h"
#include "world.h"

using namespace std;

Ball::Ball(){
    sprite.set_name("ball");

    box.x=0.0;
    box.y=0.0;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    velocity.direction=0.0;
    velocity.magnitude=0.0;

    counter_rubble=0;
}

Ball::Ball(double x,double y){
    sprite.set_name("ball");

    box.x=x;
    box.y=y;
    box.w=sprite.get_width();
    box.h=sprite.get_height();

    int quadrant=game.rng.random_range(0,3);
    if(quadrant==0){
        velocity.direction=game.rng.random_range(0,45);
    }
    else if(quadrant==1){
        velocity.direction=game.rng.random_range(135,180);
    }
    else if(quadrant==2){
        velocity.direction=game.rng.random_range(180,235);
    }
    else if(quadrant==3){
        velocity.direction=game.rng.random_range(315,360);
    }

    velocity.magnitude=170.667;
}

void Ball::movement(){
    Object::movement();

    if(is_interactive()){
        if(--counter_rubble<=0){
            counter_rubble=0.15*UPDATE_RATE;

            if(game.effect_allowed()){
                effects_ding.push_back(Effect_Ding(box.x,box.y,"rubble"));
            }
        }
    }
}

void Ball::handle_collisions(){
    Object::handle_collisions();

    for(int i=0;i<paddles.size();i++){
        Paddle* paddle=&paddles[i];

        if(paddle->is_interactive()){
            if(collision_check_rect(box,paddle->box)){
                bool collide_horizontal=false;

                Collision_Rect box_horizontal=box;
                box_horizontal.y+=box_horizontal.h/4.0;
                box_horizontal.h/=2.0;

                Collision_Rect box_vertical=box;
                box_vertical.x+=box_vertical.w/4.0;
                box_vertical.w/=2.0;

                Collision_Rect box_horizontal_top=box;
                box_horizontal_top.y+=1.0;
                box_horizontal_top.h/=4.0;
                box_horizontal_top.h-=1.0;

                Collision_Rect box_horizontal_bottom=box;
                box_horizontal_bottom.y+=box_horizontal_bottom.h/4.0*3.0;
                box_horizontal_bottom.h/=4.0;
                box_horizontal_bottom.h-=1.0;

                if(collision_check_rect(box_horizontal,paddle->box)){
                    collide_horizontal=true;

                    if(box.x<paddle->box.x){
                        box.x=paddle->box.x-box.w;
                    }
                    else if(box.x+box.w>paddle->box.x+paddle->box.w){
                        box.x=paddle->box.x+paddle->box.w;
                    }
                }
                else if(collision_check_rect(box_vertical,paddle->box)){
                    if(box.y<paddle->box.y){
                        box.y=paddle->box.y-box.h;
                    }
                    else if(box.y+box.h>paddle->box.y+paddle->box.h){
                        box.y=paddle->box.y+paddle->box.h;
                    }
                }
                else if(collision_check_rect(box_horizontal_top,paddle->box)){
                    collide_horizontal=true;

                    if(box.x<paddle->box.x){
                        box.x=paddle->box.x-box.w;
                    }
                    else if(box.x+box.w>paddle->box.x+paddle->box.w){
                        box.x=paddle->box.x+paddle->box.w;
                    }
                }
                else if(collision_check_rect(box_horizontal_bottom,paddle->box)){
                    collide_horizontal=true;

                    if(box.x<paddle->box.x){
                        box.x=paddle->box.x-box.w;
                    }
                    else if(box.x+box.w>paddle->box.x+paddle->box.w){
                        box.x=paddle->box.x+paddle->box.w;
                    }
                }

                rebound(collide_horizontal);
                velocity+=paddle->velocity*0.1;
                velocity.magnitude*=1.05;
                if(velocity.magnitude>512.0){
                    velocity.magnitude=512.0;
                }

                effects_ding.push_back(Effect_Ding(paddle->box.x+paddle->box.w-8.0,box.y-4.0,"rubble_large"));

                sound_system.play_sound("rebound_paddle",box.x,box.y);
            }
        }
    }

    if(box.x+box.w<0.0){
        alive=false;

        paddles[1].score++;

        sound_system.play_sound("score",box.x,box.y);

        return;
    }
    else if(box.x>game.world_x){
        alive=false;

        paddles[0].score++;

        sound_system.play_sound("score",box.x,box.y);

        return;
    }

    if(box.y<0.0){
        box.y=0.0;

        rebound(false);

        effects_ding.push_back(Effect_Ding(box.x-8.0,-8.0,"rubble_large"));

        sound_system.play_sound("rebound_wall",box.x,box.y);
    }
    else if(box.y+box.h>game.world_y){
        box.y=game.world_y-box.h;

        rebound(false);

        effects_ding.push_back(Effect_Ding(box.x-8.0,game.world_y-8.0,"rubble_large"));

        sound_system.play_sound("rebound_wall",box.x,box.y);
    }
}

void Ball::rebound(bool horizontal){
    int quadrant=get_angle_quadrant(velocity.direction);
    if(quadrant==0){
        velocity=velocity.opposite();
    }
    else{
        if(!horizontal){
            velocity.direction*=-1.0;
        }
        else{
            Vector_Components vc=velocity.get_components_absolute();
            vc.a*=-1.0;
            velocity.set_polar_form(vc);
        }
    }
}
