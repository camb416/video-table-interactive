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
#include <vector>
#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "Image.h"
#include "cinder/Buffer.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gallerytools;

class VideoPlayer {
public:
    VideoPlayer();
    VideoPlayer( Rectf r, vector<string> movies );
    void update(); 
    void draw(char _align, bool _debug);

    void nextMovie();
    void play();
    void pause();
    void unload();
    
    
private:
    int                     ind;
	gl::Texture             mFrameTexture;
	qtime::MovieGl     *     mMovie;
    vector<qtime::MovieGl *>  movies;
    Rectf                   drawRect;
    Image                   fadeTo, fadeFrom;
    bool                    isFading;
    bool                    firstFade;
    float                   alpha, dAlpha;
    Buffer                  mBuffer;
    vector<Buffer>          buffers;
};

 #endif 