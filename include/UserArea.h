//
//  UserArea.h
//  CinderProject
//
//  Created by Cameron Browning on 7/2/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef CinderProject_UserArea_h
#define CinderProject_UserArea_h


#include "VideoPlayer.h"

#include <vector>
#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;



class UserArea
{
    public:
        UserArea();
        UserArea(char c, Rectf vR, vector<string> videos, float angle_in , Vec2f pos_in);
        void update();
        void draw();
        Vec2f pos;
        char getKey();
        void nextMovie();
private:
        char key;
        VideoPlayer player;
        Rectf vidRect;
        int state;
        bool flipped;

    float angle;
    int frameCount;

};

#endif