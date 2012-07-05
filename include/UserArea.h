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
    UserArea(char c, Rectf vR, bool f, float angle_in );
        void update();
        void draw();
        
        char getKey();
        void nextMovie();
    
        char key;
        VideoPlayer player;
        Rectf vidRect;
        int state;
        bool flipped;

    float angle;

};

#endif