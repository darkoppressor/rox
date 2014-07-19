#include "game.h"
#include "world.h"

using namespace std;

void Game::clear_world(){
    paddles.clear();
    balls.clear();
    clouds.clear();
    tiles.clear();
    effects_paddle.clear();
    effects_ding.clear();
}

void Game::generate_world(){
    clear_world();

    world_x=256.0;
    world_y=144.0;

    uint32_t world_tile_x=(uint32_t)ceil(world_x/16.0);
    uint32_t world_tile_y=(uint32_t)ceil(world_y/16.0);

    for(int x=0;x<world_tile_x;x++){
        tiles.push_back(vector<Tile>());
        for(int y=0;y<world_tile_y;y++){
            tiles[x].push_back(Tile());
        }
    }

    paddles.push_back(Paddle(0.0,(world_y-32.0)/2.0));

    paddles.push_back(Paddle(world_x-8.0,(world_y-32.0)/2.0));

    counter_new_ball=4*(int)UPDATE_RATE;

    network.send_sound("start",RakNet::UNASSIGNED_RAKNET_GUID,true);
    sound_system.play_sound("start");
}

void Game::restart(){
    if(in_progress){
        balls.clear();
        clouds.clear();
        effects_paddle.clear();
        effects_ding.clear();

        paddles[0].restart();
        paddles[1].restart();

        counter_new_ball=4*(int)UPDATE_RATE;

        network.send_sound("start",RakNet::UNASSIGNED_RAKNET_GUID,true);
        sound_system.play_sound("start");
    }
}
