//
//  TwoStateButton.h
//  CinderProject
//
//  Created by Cameron Browning on 7/24/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef CinderProject_TwoStateButton_h
#define CinderProject_TwoStateButton_h

#include "Image.h"
#include "cinder/Xml.h"

//using namespace gallerytools;

namespace gallerytools {
    class TwoStateButton {
    public:
        
      //  TwoStateButton(string _active, string _inactive, Vec2f _pos);
        TwoStateButton(XmlTree xml);
        void press();
        void release();
        void update();
        void draw(bool _debug = false);
        int getSensor();
        int getDevice();
        
    private:
        Vec2f pos;
        Image active;
        Image inactive;    
        int device;
        int sensor;
    };
}
#endif
