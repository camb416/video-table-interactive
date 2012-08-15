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
#include "RecipeModel.h"
#include "cinder/qtime/QuickTime.h"
#include <iostream>
#include <vector>


// okay here's a recipe class
class RecipeView{
public:
    int state;
    RecipeView(RecipeModel _model);
    void draw(Vec2f pos);
    void update();
    void moveForward();
    
private:
    RecipeModel recipeModel;
    int curStep;
    int stepState;
    int prevStep;
    int prevStepState;
 //   int reload();
   // gallerytools::Image img;
   // gallerytools::Image menu_img;
    vector<CookStep> steps;
    gl::Texture text_texture;
   // gallerytools::Video video;
    vector<gallerytools::Image> images;
    vector<gallerytools::Video> videos;
    
};



#endif /* defined(__CinderProject__Recipe__) */
