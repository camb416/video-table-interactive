//
//  Recipe.h
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
//

#ifndef __CinderProject__Recipe__
#define __CinderProject__Recipe__

#include "Image.h"
#include "CookStep.h"
#include <iostream>
#include <vector>

// okay here's a recipe class
class Recipe{
public:
    int state;
    
private:
    gallerytools::Image end_img;
    gallerytools::Image menu_img;
    vector<CookStep> steps;
    
};



#endif /* defined(__CinderProject__Recipe__) */
