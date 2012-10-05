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
#include "ButtonModel.h"
#include <iostream>
#include <string>
#include <vector>

using namespace ci;
using namespace cinder::app;
using namespace std;

struct CookStepModel{
    vector<string> img;
    vector<string> video;
    string name;
};

class RecipeModel{
    
public:
    RecipeModel();
    ~RecipeModel();
    int load(string _plist);
    int testCase();
    int save();
    CookStepModel getCookStep(int _whichStep = 0);
    int switchLanguage();
    int trace();
    int getNumSteps();
    int getNumLanguages();
    
    // for parity with PlistReader
    string name;
    vector<CookStepModel> steps;
    ButtonModel back_btn;
    ButtonModel select_btn;
    ButtonModel fwd_btn;
    
    int curLanguage;
   

private:
    CookStepModel emptyCookStep;

    
    
    
};



#endif /* defined(__CinderProject__RecipeModel__) */
