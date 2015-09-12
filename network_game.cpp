/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "network.h"
#include "world.h"

using namespace std;

void Network::write_game_objects(RakNet::BitStream* bitstream){
    bitstream->WriteCompressed((int)paddles.size());
    for(int i=0;i<paddles.size();i++){
        bitstream->Write(paddles[i].box.x);
        bitstream->Write(paddles[i].box.y);

        bitstream->Write(paddles[i].velocity.magnitude);
        bitstream->Write(paddles[i].velocity.direction);

        bitstream->WriteCompressed(paddles[i].alive);

        bitstream->WriteCompressed(paddles[i].score);

        bitstream->WriteCompressed(paddles[i].stunned);

        bitstream->WriteCompressed(paddles[i].counter_cooldown);
    }

    bitstream->WriteCompressed((int)balls.size());
    for(int i=0;i<balls.size();i++){
        bitstream->Write(balls[i].box.x);
        bitstream->Write(balls[i].box.y);

        bitstream->Write(balls[i].velocity.magnitude);
        bitstream->Write(balls[i].velocity.direction);

        bitstream->WriteCompressed(balls[i].alive);

        bitstream->WriteCompressed(balls[i].counter_rubble);
    }

    bitstream->WriteCompressed((int)clouds.size());
    for(int i=0;i<clouds.size();i++){
        bitstream->Write(clouds[i].box.x);
        bitstream->Write(clouds[i].box.y);

        bitstream->Write(clouds[i].velocity.magnitude);
        bitstream->Write(clouds[i].velocity.direction);

        bitstream->WriteCompressed(clouds[i].alive);
    }
}

void Network::read_game_objects(RakNet::BitStream* bitstream){
    int paddles_size=0;
    bitstream->ReadCompressed(paddles_size);
    for(int i=0;i<paddles_size;i++){
        paddles.push_back(Paddle());

        bitstream->Read(paddles[i].box.x);
        bitstream->Read(paddles[i].box.y);

        bitstream->Read(paddles[i].velocity.magnitude);
        bitstream->Read(paddles[i].velocity.direction);

        bitstream->ReadCompressed(paddles[i].alive);

        bitstream->ReadCompressed(paddles[i].score);

        bitstream->ReadCompressed(paddles[i].stunned);

        bitstream->ReadCompressed(paddles[i].counter_cooldown);
    }

    int balls_size=0;
    bitstream->ReadCompressed(balls_size);
    for(int i=0;i<balls_size;i++){
        balls.push_back(Ball());

        bitstream->Read(balls[i].box.x);
        bitstream->Read(balls[i].box.y);

        bitstream->Read(balls[i].velocity.magnitude);
        bitstream->Read(balls[i].velocity.direction);

        bitstream->ReadCompressed(balls[i].alive);

        bitstream->ReadCompressed(balls[i].counter_rubble);
    }

    int clouds_size=0;
    bitstream->ReadCompressed(clouds_size);
    for(int i=0;i<clouds_size;i++){
        clouds.push_back(Cloud());

        bitstream->Read(clouds[i].box.x);
        bitstream->Read(clouds[i].box.y);

        bitstream->Read(clouds[i].velocity.magnitude);
        bitstream->Read(clouds[i].velocity.direction);

        bitstream->ReadCompressed(clouds[i].alive);
    }
}

void Network::write_initial_game_data(RakNet::BitStream* bitstream){
    bitstream->Write(game.world_x);
    bitstream->Write(game.world_y);

    write_game_objects(bitstream);
}

void Network::read_initial_game_data(RakNet::BitStream* bitstream){
    bitstream->Read(game.world_x);
    bitstream->Read(game.world_y);

    uint32_t world_tile_x=(uint32_t)ceil(game.world_x/16.0);
    uint32_t world_tile_y=(uint32_t)ceil(game.world_y/16.0);

    for(int x=0;x<world_tile_x;x++){
        tiles.push_back(vector<Tile>());
        for(int y=0;y<world_tile_y;y++){
            tiles[x].push_back(Tile());
        }
    }

    read_game_objects(bitstream);
}

void Network::write_update(RakNet::BitStream* bitstream){
    bitstream->WriteCompressed(game.counter_end_game);

    write_game_objects(bitstream);
}

void Network::read_update(RakNet::BitStream* bitstream){
    paddles.clear();
    balls.clear();
    clouds.clear();

    bitstream->ReadCompressed(game.counter_end_game);

    read_game_objects(bitstream);
}
