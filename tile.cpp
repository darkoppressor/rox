/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "tile.h"
#include "world.h"

using namespace std;

Tile::Tile(){
    if(game.rng.random_range(0,99)<40){
        sprite.set_name("grass_flat");
    }
    else{
        sprite.set_name("grass_blades");
    }

    counter_animation_boost=0;
    animation_boost=0;
}

Collision_Rect Tile::get_box(uint32_t x,uint32_t y){
    Collision_Rect box;

    box.w=sprite.get_width();
    box.h=sprite.get_height();

    box.x=(double)x*box.w;
    box.y=(double)y*box.h;

    return box;
}

void Tile::whack(double magnitude){
    if(magnitude>0.0){
        counter_animation_boost=(int)ceil(0.25*UPDATE_RATE);
        animation_boost=(int)ceil(17066.7/magnitude);
    }
}

void Tile::animate(bool menu){
    if(!menu){
        if(counter_animation_boost>0){
            counter_animation_boost--;
        }

        if(counter_animation_boost==0){
            sprite.animate();
        }
        else{
            sprite.animate(animation_boost);
        }
    }
    else{
        sprite.animate(500);
    }
}

void Tile::render(uint32_t x,uint32_t y,bool menu){
    Collision_Rect box=get_box(x,y);

    if(!menu){
        if(collision_check_rect(box*game.camera_zoom,game.camera)){
            sprite.render(box.x*game.camera_zoom-game.camera.x,box.y*game.camera_zoom-game.camera.y);
        }
    }
    else{
        sprite.render(box.x,box.y);
    }
}
