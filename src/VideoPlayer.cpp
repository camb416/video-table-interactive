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
               // buffers.push_back( Buffer( loadResource( names[i] ) ) );
                movies.push_back(new qtime::MovieGl( loadResource(names[i]) ) );
                
                //movies.push_back(new qtime::MovieGl( loadResource(names[i]) ) );
                //movies.at(i)->play();               // initial play/stop avoids lag when swapping videos
                movies.at(i)->setLoop();
                movies.at(i)->play();
                movies.at(i)->stop();
                movies.at(i)->seekToStart();
            }
            else {
                console() << "movie name is empty." << endl;
            }
        } catch (...) {
            console() << "Unable to load movie titled " << names[i] << endl;
        }
    }
    
   // mMovie = movies[ind];
  //  mMovie.getMovieHandle().PreRollMovie();
    
    
    for(int i=0;i<movies.size();i++){
        // movies.at(i)->setLoop();
         // movies.at(i)->play();
    }
    movies.at(ind)->play();
   
}

void VideoPlayer::nextMovie()
{
    // this increments the movie, but possibly before its ready,
    // resulting in some missing texture messages in draw. Fix this one day
    
    console() << "incrementing movie" << endl;
   movies.at(ind)->stop();
    movies.at(ind)->seekToStart();
    ind++;
    if ( ind > movies.size() - 1){
        ind = 0;
    }
    
    movies.at(ind)->play();
   // movies.at(ind)->setLoop();
}

//play, pause, unload
void VideoPlayer::play()
{
    movies.at(ind)->play();
}

void VideoPlayer::pause()
{
    movies.at(ind)->stop();
}

void VideoPlayer::update()
{
  //  if (&movies.at(ind))
   //     mFrameTexture = movies.at(ind)->getTexture();
  //  console() << "is current movie playing? " << movies.at(ind)->isPlaying() << endl;
}

void VideoPlayer::draw()
{
//	 if( mFrameTexture ){
        gl::pushMatrices();
        
        gl::translate(-320,-240);
         //         gl::draw( mFrameTexture, drawRect  );

       //  for(int i=0;i<movies.size();i++){
             gl::Texture tex = movies.at(ind)->getTexture();
             if(tex){
          //  gl:: pushMatrices();
           //  gl::translate(i*100,0,0);
           //  if(i==ind){
            //     gl::color(255,0,0);
           //  } else {
                 gl::color(255,255,255);
           //  }
        gl::draw( movies.at(ind)->getTexture() );
          //  gl:: popMatrices();
             } else {
                 console() << "missing a texture" << endl;
             }
       //  }
         gl::popMatrices();
       // console() << "texture found" << endl;
  //  }
  //  else
       // console() << "no texture" << endl;
 }


