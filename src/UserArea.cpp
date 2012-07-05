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

UserArea::UserArea(char c, Rectf vR, bool f, float angle_in, Vec2f pos_in)
{
    pos = pos_in;
    angle = angle_in;
    key = c;
    vidRect = vR;
    player = VideoPlayer( vR, f );  
    flipped = f;
 
    /* generate random number between 0 and 627 (roughly 2*PI*100) */
    frameCount = rand() % 628;
    
    cout << "the random frame is: " << frameCount << endl;
    
}

void UserArea::update()
{
    frameCount++;
    player.update();
}

void UserArea::draw()
{
    gl::pushMatrices();
    
    gl::translate(pos.x,pos.y);
    
    // 
    // gl::rotate(angle);
    // 
    // yeah but that's no fun... let's add some wiggle!
    // here's where the framecount comes in to do some animation.
    // using sine because it makes a nice pulsing pattern on the angle.
    // this is also a lot of fun to use in a scale property over time to make a pulsing patterns
    // that look like breathing
    gl::rotate(angle + sin(((float)frameCount)/100.0f)*7.5f);
    
    
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