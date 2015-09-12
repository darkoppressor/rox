/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef world_h
#define world_h

#include "collision.h"
#include "vector.h"
#include "coords.h"
#include "pixels.h"
#include "math.h"

#include "game_window.h"
#include "image.h"
#include "rtt_manager.h"
#include "music.h"
#include "sound.h"
#include "engine_interface.h"
#include "update.h"
#include "message_log.h"
#include "string_stuff.h"
#include "file_io.h"
#include "game.h"
#include "game_constant.h"
#include "network.h"

#include "paddle.h"
#include "ball.h"
#include "cloud.h"
#include "tile.h"
#include "effect_paddle.h"
#include "effect_ding.h"

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>

const int CONTROLLER_ID_ALL=-1;
const int CONTROLLER_ID_TOUCH=-2;

extern bool world_loaded;

extern bool save_location_loaded;

extern std::string CURRENT_WORKING_DIRECTORY;
extern std::string CHECKSUM;

extern double UPDATE_RATE;
extern double SKIP_TICKS;

extern double UPDATE_RATE_RENDER;
extern double SKIP_TICKS_RENDER;

extern Message_Log message_log;

extern String_Stuff string_stuff;

extern Game_Window main_window;

extern SDL_Event event;

extern Engine_Interface engine_interface;

extern Update update;

extern File_IO file_io;

extern Network network;

extern Image image;

extern Rtt_Manager rtt_manager;

extern Music music;

extern Sound sound_system;

extern Game game;

extern std::vector<Paddle> paddles;
extern std::vector<Ball> balls;
extern std::vector<Cloud> clouds;
extern std::vector< std::vector<Tile> > tiles;
extern std::vector<Effect_Paddle> effects_paddle;
extern std::vector<Effect_Ding> effects_ding;

bool load_world();

void unload_world();

#endif
