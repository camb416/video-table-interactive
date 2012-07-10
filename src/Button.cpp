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
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Xml.h"

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
        else
            unpressed = img->getValue();
    }
}