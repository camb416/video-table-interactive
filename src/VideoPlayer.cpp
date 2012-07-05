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

VideoPlayer::VideoPlayer( Rectf r, bool f )
{
    //console() << App::getResourcePath( "m1.mp4" ) << endl;
    
    ind = 0;
    
    movieNames[0] = "m1.mp4";
    movieNames[1] = "m2.m4v";
    movieNames[2] = "m3.mp4";
    moviePath = movieNames[ind];
    if ( ! moviePath.empty() )
        loadMovieFile(moviePath);
   
    drawRect = r;
    flipped = f;
}

void VideoPlayer::nextMovie()
{
    ind++;
    if ( ind > size - 1)
        ind = 0;
    loadMovieFile( movieNames[ind]);
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
	if( mFrameTexture )
		gl::draw( mFrameTexture, drawRect  );
}


