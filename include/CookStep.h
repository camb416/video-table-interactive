//
//  CookStep.h
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
// This class should contain:
// - an image that shows before the video plays
// - a video that shows a cooking step
// - a button overlay image that shows the action to take ie. COOK!

#ifndef __CinderProject__CookStep__
#define __CinderProject__CookStep__


#include "Image.h"
#include "cinder/qtime/QuickTime.h"
#include <iostream>

class CookStep{
public:
    
    int setImage(string _path);
    int setVideo(string _path);
    int setBtn(string _path);
    
private:
    gallerytools::Image img;
    qtime::MovieGl video;
    gallerytools::Image btn_overlay;
};

#endif /* defined(__CinderProject__PrepStep__) */
