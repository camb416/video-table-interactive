//
//  Button.h
//  CinderProject
//
//  Created by Cameron Browning on 7/10/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef CinderProject_Button_h
#define CinderProject_Button_h

#include <iostream>
#include <vector>
//#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
//#include "cinder/Text.h"
//#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Xml.h"


using namespace ci;
using namespace std;


class Button {
public:
    Button();
    Button(XmlTree xml);
    void draw();
    void press();
    void release();
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
    gl::Texture mTexture;
};

#endif
