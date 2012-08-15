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
//int RecipeModel::save(){
//    bLoaded = true;
//    return 0;
//}
int RecipeModel::testCase(){

    
    
    
    name = "Chicken and Waffles";
    
    CookStepModel ck;
    ck.img = "ckimg0.png";
    ck.video = "sample.mov";
    cookSteps.push_back(ck);
    ck.img = "ckimg1.png";

    ck.video = "sample.mov";
    cookSteps.push_back(ck);
    ck.img = "ckimg2.png";

    ck.video = "sample.mov";
    cookSteps.push_back(ck);
    

    return 0;
}
/*
string RecipeModel::getMenuImage(){
    if(!bLoaded){
        console() << "requesting a menu image from an unloaded recipe: " << title_str << "." << endl;
        return "ERROR";
    } else {
        return img_menu;
    }
}
string RecipeModel::getEndImage(){
    if(!bLoaded){
        console() << "requesting an end image from an unloaded recipe: " << title_str << "." << endl;
        return "ERROR";
    } else {
        return img_end;
    }
}
 */
CookStepModel RecipeModel::getCookStep(int _whichStep){
    
    if(_whichStep>-1 && _whichStep<cookSteps.size()){
        return cookSteps.at(_whichStep);
    } else {
        console() << "a cookstep out of range: " << name << " : " << _whichStep << " / " << cookSteps.size() << "." << endl;
        return emptyCookStep;
    }
}

int RecipeModel::getNumSteps(){
    return cookSteps.size();
}

int RecipeModel::trace(){
    console() << name << " =====V===== " << endl;
  //  console() << "menu image: " << img_menu << ", end image: " << img_end << endl;
    for(int i=0;i<cookSteps.size();i++){
        CookStepModel csm = cookSteps.at(i);
    console() << csm.img << " : " << csm.video << " : " <<  endl;
    }
    return 0;
}

