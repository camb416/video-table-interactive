//
//  Video.h
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#ifndef __CinderProject__Video__
#define __CinderProject__Video__

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include "GalleryHelper.h"
#include "cinder/qtime/QuickTime.h"

#include <iostream>
#include <cmath>

using namespace ci;
using namespace std;

namespace gallerytools {
    class Video {
    public:
        Video();
        Video(string _file);
        Video(string _file, int _x, int _y);
        Video(string _file, Vec2f _pos);
        Video(gl::Texture _texture, Vec2f _pos);
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
        int load(string file);
        void setRotation(int _deg);
        void update();
        
        void draw(char _align = CENTER,Vec2f _scale = Vec2f(1.0f,1.0f),bool _debug = false);
        // legacy support
        void draw(char _align,bool _debug = false);
        
        int  getRotation();             // accessors
        int  getX();
        int  getY();
        Vec2f getPosition();
        bool isDone();
        void play();
        void stop();
        
    private:
        string path_str;
        gl::Texture texture;
        int x, y, dx, dy, deg;
        bool tween, hidden;
        float alpha, dAlpha;
        float moveRate, fadeRate;
        void border();
        qtime::MovieGl video;
    };
}


#endif
