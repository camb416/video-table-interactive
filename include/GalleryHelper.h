//
//  constants.h
//  CinderProject
//
//  Created by Cameron Browning on 8/1/12.
//
//

#ifndef CinderProject_constants_h
#define CinderProject_constants_h

#include "cinder/Rect.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"

using namespace ci;

enum {TOP_LEFT,TOP_MIDDLE, TOP_RIGHT, MIDDLE_LEFT,CENTER,MIDDLE_RIGHT,BOTTOM_LEFT, BOTTOM_MIDDLE, BOTTOM_RIGHT};
enum {PRODUCTION, DEBUG, DEVELOPMENT};

class GalleryHelper{
public:
   static int alignElement(char _align, cinder::Area _bounds); // legacy
   static int alignElement(char _align, gl::Texture * _tex);
    
};


#endif
