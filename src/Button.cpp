//
//  Button.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/10/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>

#include "Button.h"

#include "cinder/gl/Texture.h"
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
        {
            pressed = img->getValue();
            activeTexture = gl::Texture( loadImage( loadResource( pressed ) ) );
        }
        else if (img->getAttributeValue<string>( "id" ) == "inactive")
        {
            unpressed = img->getValue();
            inactiveTexture = gl::Texture( loadImage( loadResource( unpressed ) ) );
        }
    }
    release();
//    isPressed = false;
//    wasPressed = false;
    alpha = 0.0f;
    dAlpha = 1.0f;
    alpha2 = 0.0f;
    dAlpha2 = 0.0f;
}

void Button::update()
{
    alpha += (dAlpha - alpha) / 4.0f;
    alpha2 += (dAlpha2 - alpha2) / 4.0f;
}

void Button::draw(bool _debug)
{
  //  ColorT myColor = ColorT(255,0,0);
    
    
    
    if (activeTexture && inactiveTexture)
    {
        gl::pushMatrices();
        gl::translate(-inactiveTexture.getWidth()/2, -inactiveTexture.getHeight()/2);
       
        if(alpha>0.01f){
            gl::color(ColorA(255,255,255,alpha));
            gl::draw( inactiveTexture, Vec2f( posX, posY ) );
        }
        if(alpha2>0.01f){
            gl::color(ColorA(255,255,255,alpha2));
            gl::draw( activeTexture, Vec2f( posX, posY ) );
        
        }
        gl::popMatrices();
    }
}

void Button::press()
{
 //   drawTexture = activeTexture;
    dAlpha = 0;
    dAlpha2 = 1.0f;
}

void Button::release()
{
 //   drawTexture = inactiveTexture;
    dAlpha = 1.0f;
    dAlpha2 = 0.0f;
}

int Button::getDevice()
{
    return device;
}

int Button::getSensor()
{
    return sensor;
}

