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
/*    ind = 0;
    
    movieNames = names;
   
    moviePath = movieNames.at(ind);
    if ( ! moviePath.empty() )
        loadMovieFile(moviePath);
   
    drawRect = r;       */
    
    ind = 0;
    for (int i = 0; i < names.size(); i++)
    {
        try {
            if (!names[i].empty())
            {
                loadedMovies.push_back(qtime::MovieGl( loadResource(names[i]) ) );
                console() << "movie " << i   << " loaded" << endl;
            }
            else
                console() << "movie name is empty." << endl;    }
        catch (...) { console() << "Unable to load movie titled " << names[i] << endl; }
    }
    
  //  mMovie = loadedMovies[ind];
    loadedMovies[ind].setLoop();
    loadedMovies[ind].play();
    loadedMovies[ind].stepForward();
}

void VideoPlayer::nextMovie()
{
    ind++;
    if ( ind > loadedMovies.size() - 1)
        ind = 0;
    //loadMovieFile( movieNames.at(ind));
    
    loadedMovies[ind].setLoop();
    loadedMovies[ind].play();
    loadedMovies[ind].stepForward();
}

/*void VideoPlayer::loadMovieFile( const string &moviePath )
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
}   */

void VideoPlayer::update()
{
    
 //   if( mMovie )
//		mFrameTexture = mMovie.getTexture();
    if (loadedMovies[ind])
        mFrameTexture = loadedMovies[ind].getTexture();
    
  //  console() << loadedMovies[ind].isPlaying() << endl;
}

void VideoPlayer::draw()
{
	if( mFrameTexture ){
        gl::pushMatrices();

        // gl::translate(mFrameTexture.getWidth()/-2.0f,mFrameTexture.getHeight()/-2.0f);
        
        gl::translate(-320,-240);
        
        gl::draw( mFrameTexture, drawRect  );
        gl::popMatrices();
    }
    else
        console() << "no texture" << endl;
}


