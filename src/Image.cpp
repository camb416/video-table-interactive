//
//  Image.cpp
//  ImageTest
//
//  Created by Cameron Browning on 7/19/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include "Image.h"


using namespace ci::app;
using namespace ci;
using namespace std;

using namespace gallerytools;


/*Image::Image(string _file)
 {
 load(_file);
 x = y = dx = dy = 0.0f;
 alpha = dAlpha = 1.0f;
 hidden = false;
 deg = 0;
 moveRate = 30.0f;
 }   */

Image::Image(){

    x = y = dx = dy = deg = 0;
    alpha = dAlpha = 1.0f;
    hidden = false;
    moveRate = 30.0f;
    fadeRate = 30.0f;
    xscale = yscale = 1.0f;
}

Image::Image(string _file, int _x, int _y)
{
    
     xscale = yscale = 1.0f;
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

Image::Image(string _file, Vec2f _pos)
{
     xscale = yscale = 1.0f;
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

Image::Image(gl::Texture _texture, Vec2f _pos)
{
     xscale = yscale = 1.0f;
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

int Image::load(string _file)
{
    path_str = _file;
    try {
        texture = gl::Texture( loadImage( path_str) );
    
    } catch(...) {
        console()<<"Unable to load image: "<< path_str << "." << endl;
        return -1;
    }
    return 0;
}

/**
 *  moveTo can take an x, y coord pair or a Vec2f.
 *  The boolean dictates whether the image tweens to
 *  its new location or moves immediately. If no boolean
 *  is given, it is assumed to be false.
 */
void Image::moveTo(int _x, int _y, bool _tween)
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
 void Image::moveTo(int _x, int _y)
 {
 tween = false;
 x = _x;
 y = _y;
 }   */

void Image::boingScaleIn(){
    timeline().apply(&alpha,1.0f,0.1f,EaseNone());
    timeline().apply(&xscale, 1.0f, 0.1f,EaseOutElastic(1.0f,1.0f));
    timeline().apply(&yscale,1.0f,0.1f,EaseOutElastic(1.0f,2.0f));
}

void Image::boingScaleOut(){
    timeline().apply(&alpha,0.0f,1.0f,EaseNone());
    timeline().apply(&xscale, 0.5f, 1.0f,EaseOutElastic(1.0f,1.0f));
    timeline().apply(&yscale,0.5f,1.0f,EaseOutElastic(1.0f,2.0f));
}

void Image::setHalfHidden(){
    alpha = 0.0f;
    xscale = 0.5f;
    yscale = 0.5f;
}

void Image::moveTo (Vec2f pos, bool _tween)
{
    moveTo( pos.x, pos.y, _tween );
}
/*
 void Image::moveTo (Vec2f pos)
 {
 moveTo( pos.x, pos.y );
 }   */

void Image::hide()
{
    alpha = dAlpha = 0.0f;
    hidden = true;
}

void Image::show()
{
    alpha = dAlpha = 1.0f;
    hidden = false;
}

void Image::fadeOut(float _fadeRate)
{
    fadeRate = _fadeRate;
    dAlpha = 0.0f;
}

void Image::fadeIn(float _fadeRate)
{
    fadeRate = _fadeRate;
    dAlpha = 1.0f;
}

bool Image::isFading()
{
    return abs(dAlpha - alpha) > .01;
}

void Image::setRotation(int _deg)
{
    deg = _deg;
}

void Image::update()
{
    console() << "deprecated the update on the image class... use timeline() instead." << endl;
 //   if (tween) {
 //       x += (dx - x) / moveRate;
 //       y += (dy - y) / moveRate;
 //   }
    
  //  alpha += (dAlpha - alpha) / fadeRate;
}

void Image::draw(char _align,bool _debug){
    // deprecated
    // put a cout here?
    draw(_align,Vec2f(xscale,yscale),_debug);
}

void Image::draw(char _align,Vec2f _scale, bool _debug)
{
    gl::pushMatrices();
    if (texture) {
        
        gl::translate(x, y);
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

void Image::border()
{
    Rectf r = Rectf( x - texture.getWidth()/2,
                    y - texture.getHeight()/2,
                    x + texture.getWidth()/2,
                    y + texture.getHeight()/2 );
    gl::color(Color(255, 0, 0));
    gl::drawSolidRect(r);
}

int Image::getRotation()
{
    return deg;
}

int Image::getX()
{
    return x;
}

int Image::getY()
{
    return y;
}

Vec2f Image::getPosition()
{
    return Vec2f(x, y);
}
