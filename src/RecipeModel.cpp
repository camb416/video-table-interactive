//
//  RecipeModel.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#include "RecipeModel.h"

RecipeModel::RecipeModel(){
    // empty constructor
    curLanguage = 0;

}
RecipeModel::~RecipeModel(){
    //destructor
}
int RecipeModel::load(string _plist){
    // load the xml here into plist
    // populate name, cookSteps
    // if anything fails, write what failed to console, then return -1, if success return 0
    // if success, bLoaded = true;
    
    // this is silly, why hardcode the user area titles?
    
    
    
    return -1;
}

int RecipeModel::getNumLanguages(){
    if(steps.size()>0){
        int numLanguages = steps.at(0).img.size();
        return numLanguages;
    } else {
        return -1;
    }
}

int RecipeModel::switchLanguage(){
    // switch the language here
    int prevLanguage = curLanguage;
    curLanguage++;
    if(curLanguage>=getNumLanguages()){
        curLanguage = 0;
    }
    if(curLanguage!=prevLanguage){
        return 1;   // requires view update
    } else {
        return 0;   // requires no view update
    }
}

int RecipeModel::testCase(){

    
    
    
    name = "Chicken and Waffles";
    
    CookStepModel ck;
    ck.img.push_back("ckimg0.png");
    ck.video.push_back("sample.mov");
    steps.push_back(ck);
    ck.img.push_back( "ckimg1.png");

    ck.video.push_back( "sample.mov");
    steps.push_back(ck);
    ck.img.push_back("ckimg2.png");

    ck.video.push_back("sample.mov");
    steps.push_back(ck);
    

    return 0;
}
CookStepModel RecipeModel::getCookStep(int _whichStep){
    
    if(_whichStep>-1 && _whichStep<steps.size()){
        return steps.at(_whichStep);
    } else {
        console() << "a cookstep out of range: " << name << " : " << _whichStep << " / " << steps.size() << "." << endl;
        return emptyCookStep;
    }
}

int RecipeModel::getNumSteps(){
    return steps.size();
}

int RecipeModel::trace(){
    console() << name << " =====V===== " << endl;
    for(int i=0;i<steps.size();i++){
        CookStepModel csm = steps.at(i);
    console() << csm.img.at(0) << " : " << csm.video.at(0) << " : " <<  endl;
    }
    return 0;
}

