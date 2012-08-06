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
#include "RecipeModel.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cinder;

class AppModel{
public:
    
    int setup(string _appFilePath, string _contentFilePath);
    int pretendSetup();
    vector<RecipeModel> recipes;
    int trace();
private:
    bool bLoaded;
    
};
#endif /* defined(__CinderProject__Settings__) */
