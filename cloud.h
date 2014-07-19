#ifndef cloud_h
#define cloud_h

#include "object.h"

class Cloud: public Object{
public:

    Cloud();
    Cloud(double x,double y,double direction);

    void handle_collisions();
};

#endif
