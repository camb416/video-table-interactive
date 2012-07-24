//
//  Image.h
//  ImageTest
//
//  Created by Cameron Browning on 7/19/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef ImageTest_Image_h
#define ImageTest_Image_h

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include <iostream>
#include <cmath>

using namespace ci;
using namespace std;

namespace gallerytools {
    class Image {
    public:
        Image();
        Image(string _file);
        Image(string _file, int _x, int _y);
        Image(string _file, Vec2f _pos);
        void moveTo (int _x, int _y, bool _tween = false);
       // void moveTo (int _x, int _y);
        void moveTo (Vec2f pos, bool _tween = false);
       // void moveTo (Vec2f pos);
        void setRate(float _rate);
        void fadeOut(float _fadeRate = 4.0f);
        void fadeIn(float _fadeRate = 4.0f);
        bool isFading();
        void hide();
        void show();
        void load(string file);      
        void setRotation(int _deg);
        void update();
        void draw();
        
        int  getRotation();             // accessors
        int  getX();
        int  getY();                      
        Vec2f getPosition();
        
    private:
        gl::Texture texture;
        int x, y, dx, dy, deg;
        bool tween, hidden;
        float alpha, dAlpha;
        float moveRate, fadeRate;
        void border();
    };
}


#endif
