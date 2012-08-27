//
//  Settings.h
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#ifndef __CinderProject__AppModel__
#define __CinderProject__AppModel__

#include "cinder/Utilities.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Xml.h"
#include "ButtonModel.h"
#include "RecipeModel.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cinder;



struct UserAreaModel{
    string name;
    string recipe;
    float x;
    float y;
    float r;
    ButtonModel back_btn;
    ButtonModel select_btn;
    ButtonModel fwd_btn;
};
struct TouchSensorModel{
    int board;
    int sensor;
    char keymap;
};

class AppModel{
public:
    
    int setup(string _appFilePath, string _contentFilePath);
    int pretendSetup();

    int trace();
    void parseRecipes(XmlTree _root);
    void parseSettings(XmlTree _root);
    
    RecipeModel getRecipeModel(string _recipeTitle);
    
    vector<RecipeModel> recipes;
    vector<UserAreaModel> areas;
    vector<TouchSensorModel> sensors;
    
    string backgroundPath;
    string buttonPath;
    bool isFullScreen;
    
private:
    

    bool bLoaded;
    
};
#endif /* defined(__CinderProject__Settings__) */
