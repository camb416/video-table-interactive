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

int RecipeModel::testCase(){

    
    
    
    name = "Chicken and Waffles";
    
    CookStepModel ck;
    ck.img = "ckimg0.png";
    ck.video = "sample.mov";
    steps.push_back(ck);
    ck.img = "ckimg1.png";

    ck.video = "sample.mov";
    steps.push_back(ck);
    ck.img = "ckimg2.png";

    ck.video = "sample.mov";
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
    console() << csm.img << " : " << csm.video << " : " <<  endl;
    }
    return 0;
}

