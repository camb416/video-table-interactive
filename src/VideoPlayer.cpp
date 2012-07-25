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
    
    drawRect = r;
    
    // fill movies up
    for (int i = 0; i < names.size(); i++)
    {
        try {
            if (!names[i].empty())
                movies.push_back(qtime::MovieGl( loadResource(names[i]) ) );
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
    mMovie = movies[ind];
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
	if( mFrameTexture ){
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


