//
//  Recipe.h
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
//

#ifndef __CinderProject__RecipeView__
#define __CinderProject__RecipeView__

#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include "Resources.h"
#include "Image.h"
#include "Video.h"
#include "CookStep.h"
#include "AppModel.h"
#include "cinder/qtime/QuickTime.h"
#include <iostream>
#include <vector>


// okay here's a recipe class
class RecipeView{
public:
    int state;
    RecipeView(RecipeModel _model);
    RecipeView(UserAreaModel _area, RecipeModel _recipe);
    void draw();
    void update();
    
    void forwardPress();
    void backwardPress();
    void selectPress();
    
    void forwardRelease();
    void backwardRelease();
    void selectRelease();
    
    void setDebug(int _debugState);
    
    int getKeyFunction(char _aChar);
    
private:
    int debugState;
    Vec2f pos;
    float rotation;
    RecipeModel recipeModel;
    UserAreaModel areaModel;
    int curStep;
    int stepState;
    int prevStep;
    int prevStepState;
    int align;
   // int reload();
   // gallerytools::Image img;
   // gallerytools::Image menu_img;
    vector<CookStep> steps;
    gl::Texture text_texture;
   // gallerytools::Video video;
    vector<gallerytools::Image> images;
    vector<gallerytools::Video> videos;
    
    gallerytools::Image back_btn;
    gallerytools::Image fwd_btn;
    gallerytools::Image select_btn;
    
};



#endif /* defined(__CinderProject__Recipe__) */
