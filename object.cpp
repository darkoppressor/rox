#include "object.h"
#include "world.h"

using namespace std;

Object::Object(){
    alive=true;
}

bool Object::is_interactive(){
    if(alive){
        return true;
    }
    else{
        return false;
    }
}

void Object::movement(){
    if(is_interactive()){
        Vector_Components vc=velocity.get_components();

        box.x+=vc.a/UPDATE_RATE;
        box.y+=vc.b/UPDATE_RATE;

        handle_collisions();
    }
}

void Object::handle_collisions(){
    for(int x=0;x<tiles.size();x++){
        for(int y=0;y<tiles[x].size();y++){
            Tile* tile=&tiles[x][y];

            if(collision_check_rect(box,tile->get_box(x,y))){
                tile->whack(velocity.magnitude);
            }
        }
    }
}

void Object::render(){
    if(is_interactive() && collision_check_rect(box*game.camera_zoom,game.camera)){
        sprite.render(box.x*game.camera_zoom-game.camera.x,box.y*game.camera_zoom-game.camera.y);
    }
}
