//
//  Video.cpp
//  VideoTest
//
//  Created by Cameron Browning on 7/19/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include "Video.h"


using namespace ci::app;
using namespace ci;
using namespace std;

using namespace gallerytools;


/*Video::Video(string _file)
 {
 load(_file);
 x = y = dx = dy = 0.0f;
 alpha = dAlpha = 1.0f;
 hidden = false;
 deg = 0;
 moveRate = 30.0f;
 }   */

Video::Video(){
    x = y = dx = dy = deg = 0;
    alpha = dAlpha = 1.0f;
    hidden = false;
    moveRate = 30.0f;
    fadeRate = 30.0f;
}

Video::Video(string _file, int _x, int _y)
{
    load(_file);
    x = _x;
    y = _y;
    dx = x;
    dy = y;
    
    alpha = dAlpha = 1.0f;
    hidden = false;
    deg = 0;
    moveRate = 30.0f;
    fadeRate = 30.0f;
}

Video::Video(string _file, Vec2f _pos)
{
    load(_file);
    x = _pos.x;
    y = _pos.y;
    dx = x;
    dy = y;
    
    alpha = dAlpha = 1.0f;
    hidden = false;
    deg = 0;
    moveRate = 30.0f;
    fadeRate = 50.0f;
}

Video::Video(gl::Texture _texture, Vec2f _pos)
{
    texture = _texture;
    x = _pos.x;
    y = _pos.y;
    dx = x;
    dy = y;
    
    alpha = dAlpha = 1.0f;
    hidden = false;
    deg = 0;
    moveRate = 30.0f;
    fadeRate = 50.0f;
}

int Video::load(string _file)
{
    path_str = _file;
    try {
        
        video = qtime::MovieGl( loadResource( path_str  ) );
        
    } catch(...) {
        console()<<"Unable to load Video: "<< path_str << "." << endl;
        return -1;
    }
    return 0;
}
bool Video::isDone(){
    return video.isDone();
}
void Video::play(){
    video.play();
}
void Video::stop(){
    video.stop();
}

/**
 *  moveTo can take an x, y coord pair or a Vec2f.
 *  The boolean dictates whether the Video tweens to
 *  its new location or moves immediately. If no boolean
 *  is given, it is assumed to be false.
 */
void Video::moveTo(int _x, int _y, bool _tween)
{
    tween = _tween;
    if (!tween) {
        x = _x;
        y = _y;
    }
    else {
        dx = _x;
        dy = _y;
    }
}

/*
 void Video::moveTo(int _x, int _y)
 {
 tween = false;
 x = _x;
 y = _y;
 }   */

void Video::moveTo (Vec2f pos, bool _tween)
{
    moveTo( pos.x, pos.y, _tween );
}
/*
 void Video::moveTo (Vec2f pos)
 {
 moveTo( pos.x, pos.y );
 }   */

void Video::hide()
{
    alpha = dAlpha = 0.0f;
    // hidden = true;
}

void Video::show()
{
    hidden = false;
}

void Video::fadeOut(float _fadeRate)
{
    fadeRate = _fadeRate;
    dAlpha = 0.0f;
}

void Video::fadeIn(float _fadeRate)
{
    hidden = false;
    fadeRate = _fadeRate;
    dAlpha = 1.0f;
}

bool Video::isFading()
{
    return abs(dAlpha - alpha) > .01;
}

void Video::setRotation(int _deg)
{
    deg = _deg;
}

void Video::update()
{
    if(video){
        
    texture = video.getTexture();
    }
        if (tween) {
        x += (dx - x) / moveRate;
        y += (dy - y) / moveRate;
    }
    
    alpha += (dAlpha - alpha) / fadeRate;
}

void Video::draw(char _align,bool _debug){
    // deprecated
    // put a cout here?
    draw(_align,Vec2f(1.0f,1.0f),_debug);
}

void Video::draw(char _align,Vec2f _scale, bool _debug)
{
    gl::pushMatrices();
    if (texture && !hidden) {
        
        gl::translate(x*_scale.x, y*_scale.y);
        gl::rotate(deg);
        /*
         gl::translate(-texture.getWidth()/2,
         -texture.getHeight()/2 );
         */
        gl::color(ColorA(255, 255, 255, alpha));
        gl::pushMatrices();
        
        Rectf texRect = Rectf(0.0f,0.0f,_scale.x*texture.getWidth(),_scale.y*texture.getHeight());
        
        GalleryHelper::alignElement(_align,Area(texRect));
        //  gl::draw( texture, Vec2f( 0, 0 ) );
        
        
        gl::draw(texture, texRect );
        if(_debug){
            gl::color(1.0f,1.0f,1.0f);
            //Rectf aRect =texture.getBounds();
            //    Rectf aRect = Rectf(0.0f,0.0f,text)
            gl::drawStrokedRect(texRect);
            gl::drawLine(texRect.getLowerLeft(),texRect.getUpperRight());
            gl::drawLine(texRect.getLowerRight(),texRect.getUpperLeft());
        }
        gl::popMatrices();
        if(_debug){
            gl::color(255,255,255);
            gl::drawStrokedCircle(Vec2f(0,0),20);
            gl::color(0,0,0);
            gl::drawSolidCircle(Vec2f(0,0),10);
            gl::color(1.0f,0.5f,0.25f);
            gl::drawSolidCircle(Vec2f(0,0),5);
            
        }
        //     gl::draw( texture, Vec2f( x - texture.getWidth()/2,
        //                               y - texture.getHeight()/2 ) );
    }
    gl::popMatrices();
    gl::color(1.0f,1.0f,1.0f);
}

void Video::border()
{
    Rectf r = Rectf( x - texture.getWidth()/2,
                    y - texture.getHeight()/2,
                    x + texture.getWidth()/2,
                    y + texture.getHeight()/2 );
    gl::color(Color(255, 0, 0));
    gl::drawSolidRect(r);
}

int Video::getRotation()
{
    return deg;
}

int Video::getX()
{
    return x;
}

int Video::getY()
{
    return y;
}

Vec2f Video::getPosition()
{
    return Vec2f(x, y);
}
