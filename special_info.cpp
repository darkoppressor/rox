/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "special_info.h"
#include "world.h"

using namespace std;

string Special_Info::get_special_info_text(string special_info){
    string text="";

    if(special_info.length()>0){
        if(special_info=="configure_command"){
            if(engine_interface.configure_command!=-1 && engine_interface.configure_command<engine_interface.game_commands.size()){
                text+="Inputs currently bound to\n\""+engine_interface.game_commands[engine_interface.configure_command].title+"\":"+"\n";

                const char* ckey=SDL_GetScancodeName(engine_interface.game_commands[engine_interface.configure_command].key);
                const char* cbutton=SDL_GameControllerGetStringForButton(engine_interface.game_commands[engine_interface.configure_command].button);
                const char* caxis=SDL_GameControllerGetStringForAxis(engine_interface.game_commands[engine_interface.configure_command].axis);

                bool allow_keys_and_buttons=true;
                bool allow_axes=true;
                if(caxis!=0 && engine_interface.game_commands[engine_interface.configure_command].axis!=SDL_CONTROLLER_AXIS_INVALID){
                    allow_keys_and_buttons=false;
                }
                else{
                    allow_axes=false;
                }

                if(allow_keys_and_buttons){
                    text+="Keyboard Key: ";
                    if(ckey!=0 && engine_interface.game_commands[engine_interface.configure_command].key!=SDL_SCANCODE_UNKNOWN){
                        text+=string_stuff.first_letter_capital(ckey);
                    }
                    else{
                        text+="<NOT SET>";
                    }
                    text+="\n";

                    text+="Controller Button: ";
                    if(cbutton!=0 && engine_interface.game_commands[engine_interface.configure_command].button!=SDL_CONTROLLER_BUTTON_INVALID){
                        text+=string_stuff.first_letter_capital(cbutton);
                    }
                    else{
                        text+="<NOT SET>";
                    }
                    text+="\n";
                }

                if(allow_axes){
                    text+="Controller Axis: ";
                    if(caxis!=0 && engine_interface.game_commands[engine_interface.configure_command].axis!=SDL_CONTROLLER_AXIS_INVALID){
                        text+=string_stuff.first_letter_capital(caxis);
                    }
                    else{
                        text+="<NOT SET>";
                    }
                    text+="\n";
                }
            }
        }
        else{
            message_log.add_error("Invalid special info text: '"+special_info+"'");
        }
    }

    return text;
}

string Special_Info::get_special_info_sprite(string special_info){
    string str_sprite_name="";

    if(special_info.length()>0){
        if(special_info=="example"){
            str_sprite_name="";
        }
        else{
            message_log.add_error("Invalid special info sprite: '"+special_info+"'");
        }
    }

    return str_sprite_name;
}
