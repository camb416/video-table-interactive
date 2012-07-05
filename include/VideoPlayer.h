//
//  VideoPlayer.h
//  CinderProject
//
//  Created by Cameron Browning on 7/2/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

 #ifndef CinderProject_VideoPlayer_h
 #define CinderProject_VideoPlayer_h


#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideoPlayer {
public:
    VideoPlayer();
    VideoPlayer( Rectf r, bool f);
    void update(); 
    void draw();
    
    void loadMovieFile( const string &moviePath );
    //void loadMovieFile( const fs::path &path );
    void fileDrop( FileDropEvent event );
    void nextMovie();
    
    
    static const int           size = 3;
    //fs::path                   movies[size];
    string                  movieNames[size];
    string                  moviePath;
    int                     ind;
	gl::Texture             mFrameTexture, mInfoTexture;
	qtime::MovieGl          mMovie;
    Rectf                   drawRect;
    bool                    flipped;
    
    
    
};

 #endif 