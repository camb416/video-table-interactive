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
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
//#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

VideoPlayer::VideoPlayer()
{
}

VideoPlayer::VideoPlayer( Rectf r, vector<string> names )
{
    console() << "size: " << names.size() << endl;
    
    ind = 0;
    
    movieNames = names;
    
    moviePath = movieNames.at(ind);
    if ( ! moviePath.empty() )
        loadMovieFile(moviePath);
   
    drawRect = r;	
}

void VideoPlayer::nextMovie()
{
    ind++;
    if ( ind > movieNames.size() - 1)
        ind = 0;
    console() << ind << endl;
    loadMovieFile( movieNames.at(ind));
}

void VideoPlayer::loadMovieFile( const string &moviePath )
{
    try {
        mMovie = qtime::MovieGl( loadResource(moviePath) );
        mMovie.setLoop();
        mMovie.play();
    }
    catch ( ... ) {
        console() << "Unable to load the movie. " << moviePath << std::endl;
		mMovie.reset();
    }
}

void VideoPlayer::update()
{
    
    if( mMovie )
    {
		mFrameTexture = mMovie.getTexture();
        //if (mFrameTexture && flipped)
        //    mFrameTexture.setFlipped(true);
    }
}

void VideoPlayer::draw()
{
	if( mFrameTexture ){
        gl::pushMatrices();
        
        // this is very pesky.
        // ideally we should just draw the video whatever size the file is, and center it on our Vec2f position. That leaves the
        // most room for error in dropping assets in.
        // I think we should do this later on, once we have some vids of the correct size.
        //
        // gl::translate(mFrameTexture.getWidth()/-2.0f,mFrameTexture.getHeight()/-2.0f);
        //
        // until then, let's force it to 640x480 for testing. This whole Rect business is annoying anyways.
        
        gl::translate(-320,-240);
        
        gl::draw( mFrameTexture, drawRect  );
        gl::popMatrices();
    }
}


