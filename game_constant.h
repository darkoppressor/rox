#ifndef game_constant_h
#define game_constant_h

#include <string>

extern double ZOOM_RATE;
extern double ZOOM_MIN;
extern double ZOOM_MAX;

class Game_Constant{
public:

    std::string name;

    Game_Constant();

    void set_value(std::string new_value);
};

#endif
