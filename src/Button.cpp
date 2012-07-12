//
//  Button.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/10/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>

#include "Button.h"

#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Xml.h"
#include "cinder/app/AppBasic.h"

using namespace ci::app;
using namespace ci;
using namespace std;


Button::Button()
{
}

Button::Button(XmlTree xml)
{
    posX = xml.getAttributeValue<float>( "posX" );
    posY = xml.getAttributeValue<float>( "posY" );
    angle = xml.getAttributeValue<float>( "angle" );
    device = xml.getAttributeValue<int>( "device" );
    sensor = xml.getAttributeValue<int>( "sensor" );

    for( XmlTree::Iter img = xml.begin(); img != xml.end(); ++img)
    {
        if (img->getAttributeValue<string>( "id" ) == "active")
            pressed = img->getValue();
        else if (img->getAttributeValue<string>( "id" ) == "inactive")
            unpressed = img->getValue();
    }
    release();
    isPressed = false;
    wasPressed = false;
}

void Button::draw()
{
    if (mTexture)
    {
        gl::pushMatrices();
        gl::translate(-mTexture.getWidth()/2, -mTexture.getHeight()/2);
        gl::draw( mTexture, Vec2f( posX, posY ) );
        gl::popMatrices();
    }
}

void Button::press()
{
    mTexture = gl::Texture( loadImage( loadResource( pressed ) ) );
}

bool Button::stateChange()
{
    return wasPressed && !isPressed;
}

void Button::release()
{
    mTexture = gl::Texture( loadImage( loadResource( unpressed ) ) );
}

int Button::getDevice()
{
    return device;
}

int Button::getSensor()
{
    return sensor;
}

