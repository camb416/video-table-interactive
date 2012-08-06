//
//  Settings.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#include <iostream>

#include "AppModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int AppModel::setup(string _appFilePath, string _contentFilePath){
    // 1: load app file
    // 2: populate settings model
    // 3: load content file
    // 4: populate recipes models
    /*
try {
    XmlTree doc(loadResource( "RECIPES.plist" ) );
    
    console() << doc << endl;
    
}
catch ( ... ) {
    console() << "Unable to load XML document. Check for syntax errors." << endl;
}
     */
    
    return -1;
}
int AppModel::pretendSetup(){
    RecipeModel rm;
    rm.pretendLoad();
    for(int i=0;i<4;i++){
        recipes.push_back(rm);
    }
    bLoaded = true;
    return 0;
}
int AppModel::trace(){
    if(bLoaded){
        console() << "APPMODEL: " << endl;
    for(int i=0;i<recipes.size();i++){
        recipes.at(i).trace();
    }
        return 0;
    } else {
        return -1;
    }
}