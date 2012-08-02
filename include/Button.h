//
//  Button.h
//  CinderProject
//
//  Created by Cameron Browning on 7/10/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef CinderProject_Button_h
#define CinderProject_Button_h

//#include "UserArea.h"
#include <iostream>
#include <vector>
#include "cinder/gl/Texture.h"
#include "cinder/Xml.h"


using namespace ci;
using namespace std;


class Button {
public:
    Button();
    Button(XmlTree xml);
    //Button(XmlTree xml, void (*f)());
    void draw(bool _debug = false);
    void press();
    void release();
    void update();
    bool stateChange();
    int getDevice();
    int getSensor();
    
private:
    float posX;
    float posY;
    float angle;
    int device;
    int sensor;
    string unpressed;
    string pressed;
    bool isPressed;
    bool wasPressed;
    gl::Texture inactiveTexture;
    gl::Texture activeTexture;
    gl::Texture drawTexture;
    float alpha;
    float dAlpha;
    float alpha2;
    float dAlpha2;
    
    void (*func)();
};

#endif
