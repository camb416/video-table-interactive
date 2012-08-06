//
//  RecipeModel.h
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#ifndef __CinderProject__RecipeModel__
#define __CinderProject__RecipeModel__

#include "cinder/Xml.h"
#include "cinder/app/AppBasic.h"
#include <iostream>
#include <string>
#include <vector>

using namespace ci;
using namespace cinder::app;
using namespace std;

struct cookStepModel{
    string img;
    string video;
    string btn;
};

class RecipeModel{
public:
    RecipeModel();
    ~RecipeModel();
    int load(string _plist);
    int pretendLoad();
    bool isLoaded();
    string getMenuImage();
    string getEndImage();
    cookStepModel getCookStep(int _whichStep = 0);
    int trace();

private:
    bool bLoaded;
    string title_str;
    XmlTree plist;
    vector<cookStepModel> cookSteps;
    string img_menu;
    string img_end;
    cookStepModel emptyCookStep;
};



#endif /* defined(__CinderProject__RecipeModel__) */
