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

struct CookStepModel{
    string img;
    string video;
    string name;
};

class RecipeModel{
public:
    RecipeModel();
    ~RecipeModel();
    int load(string _plist);
    int testCase();
  //  bool isLoaded();
    int save();
  //  string getMenuImage();
  //  string getEndImage();
    CookStepModel getCookStep(int _whichStep = 0);
    int trace();
    int getNumSteps();
    
    // for parity with PlistReader
    string name;
    vector<CookStepModel> steps;
    

private:
 //   bool bLoaded;
   // string title_str;
  //  XmlTree plist;
    
    // deprecate me
    vector<CookStepModel> cookSteps;
  
    //  string img_menu;
  //  string img_end;
    CookStepModel emptyCookStep;
};



#endif /* defined(__CinderProject__RecipeModel__) */
