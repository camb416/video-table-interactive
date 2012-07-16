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
#include "Button.h"

#include <vector>
//#include "cinder/Xml.h"
#include "PhidgetConnector.h"




class UserArea
{
public:
    UserArea();
    UserArea(char c, Rectf vR, vector<string> videos, float angle_in , Vec2f pos_in);
    UserArea(XmlTree area);
    UserArea(XmlTree area, PhidgetConnector *pc_);
    
    void update();
    void draw();
    void drawBackground();
    Vec2f pos;
    char getKey();
    void nextMovie();
    enum button_t {LEFT_BUTTON, MID_BUTTON, RIGHT_BUTTON};
    void registerButton(button_t b, int serial, int index);
    
private:
    char key;
    VideoPlayer player;
    Rectf vidRect;
    int state;
    bool flipped;
    vector<Button::Button> buttons;
    vector<bool> buttonStates;
    string background;
    float angle;
    int frameCount;
    PhidgetConnector *pc;
    gl::Texture mTexture;
};

#endif