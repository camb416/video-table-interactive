//
//  RecipeModel.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#include "RecipeModel.h"

RecipeModel::RecipeModel(){
    // constructor
    bLoaded = false;
}
RecipeModel::~RecipeModel(){
    //destructor
}
int RecipeModel::load(string _plist){
    // load the xml here into plist
    // populate img_menu, img_end, cookSteps
    // if anything fails, write what failed to console, then return -1, if success return 0
    // if success, bLoaded = true;
    return -1;
}
int RecipeModel::pretendLoad(){

    title_str = "Chicken and Waffles";
    img_menu = "img_menu.png";
    img_end = "img_end.png";
    
    cookStepModel ck;
    ck.img = "ckimg0.png";
    ck.btn = "ckbtn0.png";
    ck.video = "ck0.m4v";
    cookSteps.push_back(ck);
    ck.img = "ckimg1.png";
    ck.btn = "ckbtn1.png";
    ck.video = "ck1.m4v";
    cookSteps.push_back(ck);
    ck.img = "ckimg2.png";
    ck.btn = "ckbtn2.png";
    ck.video = "ck2.m4v";
    cookSteps.push_back(ck);
    
    
    bLoaded = true;
    return 0;
}

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
cookStepModel RecipeModel::getCookStep(int _whichStep){
    if(!bLoaded){
        console() << "requesting a cookstep from an unloaded recipe: " << title_str << "." << endl;
        return emptyCookStep;
    }
    if(_whichStep>-1 && _whichStep<cookSteps.size()){
        return cookSteps.at(_whichStep);
    } else {
        console() << "a cookstep out of range: " << title_str << " : " << _whichStep << " / " << cookSteps.size() << "." << endl;
        return emptyCookStep;
    }
}
int RecipeModel::trace(){
    console() << title_str << " =====V===== " << endl;
    console() << "menu image: " << img_menu << ", end image: " << img_end << endl;
    for(int i=0;i<cookSteps.size();i++){
        cookStepModel csm = cookSteps.at(i);
        console() << csm.img << " : " << csm.video << " : " << csm.btn << endl;
    }
    return 0;
}

bool RecipeModel::isLoaded() {
    return bLoaded;
}