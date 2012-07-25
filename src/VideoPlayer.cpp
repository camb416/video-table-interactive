//
//  VideoPlayer.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/2/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream> 
#include "VideoPlayer.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"


VideoPlayer::VideoPlayer()
{
}

VideoPlayer::VideoPlayer( Rectf r, vector<string> names )
{    
    ind = 0;
    isFading = false;
    drawRect = r;
    
    // fill movies up
    for (int i = 0; i < names.size(); i++)
    {
        try {
            if (!names[i].empty())
            {
                movies.push_back(qtime::MovieGl( loadResource(names[i]) ) );
                movies[i].play();               // initial play/stop avoids lag when swapping videos
                movies[i].stop();
          //      movies[i].stepForward();
            }
            else
                console() << "movie name is empty." << endl;    }
        catch (...) { console() << "Unable to load movie titled " << names[i] << endl; }
    }
    
    mMovie = movies[ind];
    mMovie.play();
    mMovie.setLoop();
}

void VideoPlayer::nextMovie()
{
    ind++;
    if ( ind > movies.size() - 1)
        ind = 0;
    mMovie.stop();
    fadeFrom = Image( mMovie.getTexture(), Vec2f(0,0) );
    mMovie = movies[ind];
    fadeTo = Image( mMovie.getTexture(), Vec2f(0,0) );
    isFading = true;
    firstFade = false;
    
    fadeFrom.fadeOut(20.0f);
    
  /*  while (fadeFrom.isFading()) { 
        fadeFrom.update();
        fadeFrom.draw();
    }
    fadeTo.fadeIn(20.0f);
    while (fadeFrom.isFading()) {
        fadeTo.update();
        fadeTo.draw();
    }   */
    
    mMovie.play();
    mMovie.setLoop();
}

void VideoPlayer::update()
{
    if (mMovie)    
        mFrameTexture = mMovie.getTexture();
}

void VideoPlayer::draw()
{
    if (isFading && fadeFrom.isFading())
    {
        firstFade = true;
        fadeFrom.update();
        fadeFrom.draw();
    }
    else if (isFading && !fadeFrom.isFading() && firstFade)
    {
        fadeTo.fadeIn(20.0f);
        firstFade = false;
    }
    else if (isFading && fadeTo.isFading())
    {
        fadeFrom.update();
        fadeFrom.draw();
    }
             
	else if( mFrameTexture ){
        gl::pushMatrices();

        // gl::translate(mFrameTexture.getWidth()/-2.0f,mFrameTexture.getHeight()/-2.0f);
        
        gl::translate(-320,-240);
        
        gl::draw( mFrameTexture, drawRect  );
        gl::popMatrices();
        console() << "texture found" << endl;
    }
    else
        console() << "no texture" << endl;
}


