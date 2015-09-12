/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "update.h"
#include "world.h"
#include "render.h"

using namespace std;

void Update::tick(){
    if(game.in_progress && !game.paused){
    }
}

void Update::ai(){
    if(game.in_progress && !game.paused){
        for(int i=0;i<paddles.size();i++){
            if(network.get_player_count()<i+1){
                paddles[i].ai(i);
            }
        }
    }
}

void Update::input(){
    engine_interface.prepare_for_input();

    game.prepare_for_input();

    bool event_ignore_command_set=false;

    while(engine_interface.poll_event(&event)){
        bool event_consumed=false;

        if(event.type==SDL_QUIT){
            engine_interface.quit();

            event_consumed=true;
        }

        if(!event_consumed && engine_interface.touch_controls){
            event_consumed=engine_interface.handle_input_events_touch();
        }

        if(!event_consumed){
            event_consumed=engine_interface.handle_input_events_command_set();
        }

        //If we are still binding a command input.
        if(engine_interface.configure_command!=-1){
            event_ignore_command_set=true;
        }
        else{
            event_ignore_command_set=false;
        }

        if(!event_consumed){
            event_consumed=engine_interface.handle_input_events(event_ignore_command_set);
        }

        if(!engine_interface.console.on && !engine_interface.chat.on && !event_ignore_command_set){
            if(!event_consumed && !engine_interface.mutable_info_selected()){
                event_consumed=game.handle_input_events_gui();
            }

            if(!event_consumed && !engine_interface.is_any_window_open()){
                event_consumed=game.handle_input_events();
            }
        }
    }

    engine_interface.handle_input_states();

    if(!engine_interface.console.on && !engine_interface.chat.on && !event_ignore_command_set){
        if(!engine_interface.mutable_info_selected()){
            game.handle_input_states_gui();
        }

        if(!engine_interface.is_any_window_open()){
            game.handle_input_states();
        }
    }

    game.handle_game_commands_multiplayer();
    game.handle_command_states_multiplayer();
}

void Update::movement(){
    if(game.in_progress && !game.paused){
        for(int i=0;i<paddles.size();i++){
            paddles[i].movement();
        }

        for(int i=0;i<balls.size();i++){
            balls[i].movement();
        }

        for(int i=0;i<clouds.size();i++){
            clouds[i].movement();
        }

        for(int i=0;i<effects_paddle.size();i++){
            effects_paddle[i].movement();
        }
    }
}

void Update::events(){
    game.manage_music();

    if(game.in_progress && !game.paused){
        if(network.status=="server"){
            uint32_t player_count=network.get_player_count();

            if(player_count>=2 && game.last_player_count<2){
                game.restart();
            }

            game.last_player_count=player_count;

            if(game.counter_end_game==0){
                for(int i=0;i<paddles.size();i++){
                    if(paddles[i].score>=10){
                        balls.clear();

                        game.counter_end_game=10*(int)UPDATE_RATE;

                        network.send_sound("end",RakNet::UNASSIGNED_RAKNET_GUID,true);
                        sound_system.play_sound("end");

                        break;
                    }
                }
            }
        }

        game.manage_objects();

        for(int i=0;i<balls.size();i++){
            Ball* ball=&balls[i];
            if(ball->is_interactive() && ball->velocity.magnitude>=170.667*1.4){
                double shake=0.001*(ball->velocity.magnitude/256.0);

                if(shake>0.002){
                    shake=0.002;
                }

                game.screen_shake.add_shake(shake,1+(int)ceil(1000.0/UPDATE_RATE));
                engine_interface.make_rumble(CONTROLLER_ID_ALL,1.0f,1+(int)ceil(1000.0/UPDATE_RATE));

                break;
            }
        }
    }
}

void Update::animate(){
    music.fadein_tracks();
    music.fadeout_tracks();

    engine_interface.animate();

    if(game.in_progress && !game.paused){
        for(int x=0;x<tiles.size();x++){
            for(int y=0;y<tiles[x].size();y++){
                tiles[x][y].animate();
            }
        }

        for(int i=0;i<effects_ding.size();i++){
            effects_ding[i].animate();
        }
    }
}

void Update::camera(int frame_rate,double ms_per_frame,int logic_frame_rate){
    engine_interface.update_window_caption(frame_rate,ms_per_frame,logic_frame_rate);

    if(game.in_progress){
        game.set_camera();
    }
}

void Update::render(int frame_rate,double ms_per_frame,int logic_frame_rate){
    SDL_SetRenderDrawColor(main_window.renderer,0,0,0,255);
    SDL_RenderClear(main_window.renderer);

    if(game.in_progress){
        Bitmap_Font* font=engine_interface.get_font("standard");

        /**rtt_manager.example.make_render_target();
        ///Render something here.
        rtt_manager.example.reset_render_target();*/

        game.render_background();

        for(int x=0;x<tiles.size();x++){
            for(int y=0;y<tiles[x].size();y++){
                tiles[x][y].render(x,y);
            }
        }

        for(int i=0;i<paddles.size();i++){
            paddles[i].render();
        }

        for(int i=0;i<balls.size();i++){
            balls[i].render();
        }

        for(int i=0;i<clouds.size();i++){
            clouds[i].render();
        }

        for(int i=0;i<effects_paddle.size();i++){
            effects_paddle[i].render();
        }

        for(int i=0;i<effects_ding.size();i++){
            effects_ding[i].render();
        }

        if(game.counter_end_game>0){
            double msg_height=(main_window.SCREEN_HEIGHT-font->spacing_y)/2.0-font->spacing_y;

            int winner=0;
            for(int i=0;i<paddles.size();i++){
                if(paddles[i].score>=10){
                    winner=i;

                    break;
                }
            }

            render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,0.5,"ui_black");

            string msg="Player "+string_stuff.num_to_string(winner+1)+" wins!";
            font->show((main_window.SCREEN_WIDTH-msg.length()*font->spacing_x)/2.0,msg_height,msg,"ui_white");

            msg="New game in "+string_stuff.num_to_string((int)ceil((double)game.counter_end_game/UPDATE_RATE))+" seconds";
            font->show((main_window.SCREEN_WIDTH-msg.length()*font->spacing_x)/2.0,msg_height+font->spacing_y*2.0,msg,"ui_white");
        }

        string msg=string_stuff.num_to_string(paddles[0].score)+"                 "+string_stuff.num_to_string(paddles[1].score);
        font->show((main_window.SCREEN_WIDTH-msg.length()*font->spacing_x)/2.0,(main_window.SCREEN_HEIGHT-font->spacing_y)/2.0,msg,"ui_white");

        game.render_scoreboard();
    }
    else{
        engine_interface.render_title_background();
    }

    engine_interface.render(frame_rate,ms_per_frame,logic_frame_rate);

    SDL_RenderPresent(main_window.renderer);
}
