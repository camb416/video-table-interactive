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
#include "GalleryHelper.h"
using namespace gallerytools;

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
}

UserArea::UserArea(XmlTree area, PhidgetConnector *pc_)
{
    pos = Vec2f(area.getAttributeValue<float>( "centerX" ), area.getAttributeValue<float>( "centerY" ));
    angle = area.getAttributeValue<float>( "angle" );
    key = area.getAttributeValue<char>( "key" );
    
    
    // this should be loading from the XML.
    background = "area_background.png";
    
    // there is some serious abstracting to be done here
    string activeArea_str = "active_area.png";
    
    
    
    bg_img.load(background);
    activeArea_img.load(activeArea_str);
    
    // really, still? hmmm
    // mTexture = gl::Texture( loadImage( loadResource( background ) ) );
    
    
    vector<string> videos;
    for( XmlTree::Iter child = area.begin(); child != area.end(); ++child)
    {
        if ( child->getTag() == "video" )
            videos.push_back(child->getValue());
        else if ( child->getTag() == "button" )
        {
            XmlTree b = *child;
            //buttons.push_back(Button::Button(b/*, &UserArea::nextMovie*/));
            buttons.push_back(TwoStateButton(b));
            buttonStates.push_back(false);
           
           // void (UserArea::*func)() = &UserArea::nextMovie;
          /*  void (*func)() = &printTest;
            func(); */
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
        
        buttons[i].update();
        // is it pressed?
        if (pc!=NULL && pc->getBool(buttons.at(i).getDevice(), buttons.at(i).getSensor()))
        {
            buttons[i].press();
            console()<<"button press"<<endl;
            buttonStates[i] = true;
        }
        // was it just pressed?
        else if (pc!=NULL && buttonStates[i])
        {
            buttonStates[i] = false;
            nextMovie();
            buttons[i].release();
        }
    }
    
}

void UserArea::draw(bool _debug)
{
    gl::pushMatrices();
    
    gl::translate(pos.x,pos.y);
    gl::rotate(angle);

  //  gl::rotate(angle + sin(((float)frameCount)/150.0f)*7.5f);
    gl::color(Color(255,255,255));
    bg_img.draw(CENTER,_debug);
    activeArea_img.draw(CENTER,_debug);
    player.draw(CENTER,_debug);

    for (int i = 0; i < buttons.size(); i++){
        buttons[i].draw(_debug);
    }
    

    
    gl::popMatrices();
    
    
}

void UserArea::drawBackground(bool _debug)
{
    cout << "soon to be deprecated function: do not use drawBackground()" << endl;
     gl::color(Color(255,255,255));
    gl::pushMatrices();
    
    gl::translate(pos.x,pos.y);
    gl::rotate(angle);
    gl::translate(-mTexture.getWidth()/2, -mTexture.getHeight()/2);
    if (mTexture)
        gl::draw(mTexture, Rectf(0, 0, mTexture.getWidth(), mTexture.getHeight()));
    
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