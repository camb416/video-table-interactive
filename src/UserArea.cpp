//
//  UserArea.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/2/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>
#include "UserArea.h"
#include "Button.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
//#include "PhidgetConnector.h"


using namespace ci;
using namespace ci::app;
using namespace std;


UserArea::UserArea()
{
}

UserArea::UserArea(char c, Rectf vR, vector<string> videos, float angle_in, Vec2f pos_in)
{
    pos = pos_in;
    angle = angle_in;
    key = c;
    vidRect = vR;
    player = VideoPlayer( vR, videos );  
 
    /* generate random number between 0 and 627 (roughly 2*PI*100) */
    frameCount = rand() % 628;
    
    cout << "the random frame is: " << frameCount << endl;
    
}

UserArea::UserArea(XmlTree area, PhidgetConnector *pc_)
{
    pos = Vec2f(area.getAttributeValue<float>( "centerX" ), area.getAttributeValue<float>( "centerY" ));
    angle = area.getAttributeValue<float>( "angle" );
    key = area.getAttributeValue<char>( "key" );
    
    vector<string> videos;
    for( XmlTree::Iter child = area.begin(); child != area.end(); ++child)
    {
        if ( child->getTag() == "video" )
            videos.push_back(child->getValue());
        else if ( child->getTag() == "button" )
        {
            XmlTree b = *child;
            buttons.push_back(Button::Button(b));
            buttonStates.push_back(false);
        }
    }
    player = VideoPlayer ( Rectf(0, 0, 640, 480), videos);
    frameCount = rand() % 628;
    
    pc = pc_;
}

void UserArea::update()
{
    frameCount++;
    player.update();
    
    // Check for button presses
    for (int i = 0; i < buttons.size(); i++)
    {
        // is it pressed?
        if (pc->getBool(buttons.at(i).getDevice(), buttons.at(i).getSensor()))
        {
            buttons.at(i).press();
            console()<<"button press"<<endl;
            buttonStates[i] = true;
        }
        // was it just pressed?
        else if (buttonStates[i])
        {
            buttonStates[i] = false;
            nextMovie();
            buttons.at(i).release();
        }
   /*     else
            buttons.at(i).release();    */
    }
    
}

void UserArea::draw()
{
    gl::pushMatrices();
    
    gl::translate(pos.x,pos.y);
    
     gl::rotate(angle);

    // yeah but that's no fun... let's add some wiggle!
    // here's where the framecount comes in to do some animation.
    // using sine because it makes a nice pulsing pattern on the angle.
    // this is also a lot of fun to use in a scale property over time to make a pulsing patterns
    // that look like breathing
    //gl::rotate(angle + sin(((float)frameCount)/100.0f)*7.5f);

    player.draw();
    
    for (int i = 0; i < buttons.size(); i++)
        buttons.at(i).draw();
    
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