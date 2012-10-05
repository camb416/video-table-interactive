//
//  CursorTarget.h
//  CinderProject
//
//  Created by Cameron Browning on 8/29/12.
//
//

#ifndef __CinderProject__CursorTarget__
#define __CinderProject__CursorTarget__

#include "cinder/app/AppBasic.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "GalleryHelper.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace ci;
using namespace ci::app;
using namespace cinder;
using namespace std;

#include <iostream>
namespace gallerytools{
class CursorTarget{
public:
    CursorTarget();
    void draw();
    void update(Vec2i pos);
    void update(string _str);
    void push();
private:
    AppBasic * app;
    stringstream suffix;
    ci::gl::Texture    text_texture;
    vector<string>poslist;
};
}
#endif /* defined(__CinderProject__CursorTarget__) */
