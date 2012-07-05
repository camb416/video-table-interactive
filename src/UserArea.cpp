//
//  UserArea.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/2/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>
#include "UserArea.h"

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


UserArea::UserArea()
{
}

UserArea::UserArea(char c, Rectf vR, bool f, float angle_in)
{
    angle = angle_in;
    key = c;
    vidRect = vR;
    player = VideoPlayer( vR, f );  
    flipped = f;
}

void UserArea::update()
{
    player.update();
}

void UserArea::draw()
{
    gl::pushMatrices();
    
   // if (flipped)
   // {
       //gl::translate(vidRect.getUpperLeft());
       // console()<<key<<" "<<vidRect.getX1() << "," << vidRect.getY1();
       // gl::translate(Vec2f(vidRect.getWidth(), vidRect.getHeight()));
        gl::translate(vidRect.getX1(), vidRect.getY1());
        gl::rotate(angle );
        
        
   // }
    
    player.draw();
    
    gl::popMatrices();
}

char UserArea::getKey()
{
    return key;
}

void UserArea::nextMovie()
{
    player.nextMovie();
}