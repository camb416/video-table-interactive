//
//  TwoStateButton.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/24/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>
#include "TwoStateButton.h"
#include "GalleryHelper.h"
using namespace gallerytools;

/* TwoStateButton::TwoStateButton(string _active, string _inactive, Vec2f _pos)
{
    gallerytools::Image active = Image(_active, _pos);
    gallerytools::Image inactive = Image(_inactive, _pos);
    pos = _pos;
    
    active.hide();
}   */

TwoStateButton::TwoStateButton(XmlTree xml)
{
    pos.x = xml.getAttributeValue<float>( "posX" );
    pos.y = xml.getAttributeValue<float>( "posY" );
    float angle = xml.getAttributeValue<float>( "angle" );
    device = xml.getAttributeValue<int>( "device" );
    sensor = xml.getAttributeValue<int>( "sensor" );
    
    for( XmlTree::Iter img = xml.begin(); img != xml.end(); ++img)
    {
        if (img->getAttributeValue<string>( "id" ) == "active")
        {
            active = Image(img->getValue(), pos);
        }
        else if (img->getAttributeValue<string>( "id" ) == "inactive")
        {
            inactive = Image(img->getValue(), pos);
        }
    }
    active.setRotation(angle);
    inactive.setRotation(angle);
}

void TwoStateButton::press()
{
    active.fadeIn(1.0f);
    inactive.fadeOut(10.0f);
}

void TwoStateButton::release()
{
    inactive.fadeIn(1.0f);
    active.fadeOut(10.0f);
}

int TwoStateButton::getSensor()
{
    return sensor;
}

int TwoStateButton::getDevice()
{
    return device;
}

void TwoStateButton::update()
{
    active.update();
    inactive.update();
}



void TwoStateButton::draw(bool _debug, Vec2f _scale)
{
    active.draw(CENTER,_scale,_debug);
    inactive.draw(CENTER,_scale,_debug);
}
