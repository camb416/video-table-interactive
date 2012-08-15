//
//  PlistReader.h
//  PLister
//
//  Created by Cameron Browning on 8/7/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#ifndef PLister_PlistReader_h
#define PLister_PlistReader_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Xml.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

struct StepModel{
    string name;
    string start_img;
    string video;
};

struct RecipeModel{
    string name;
    string menu_img;
    string end_img;
    vector <StepModel> steps;
};



class PlistReader {
public:
    PlistReader();
    void parseRecipes();
    void trace(XmlTree t);
    vector<RecipeModel> recipeModels;
   
private:
    XmlTree root;
};


#endif
