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
    // load the xml here into plist
    // populate img_menu, img_end, cookSteps
    // if anything fails, write what failed to console, then return -1, if success return 0
    // if success, bLoaded = true;
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
bool RecipeModel::isLoaded() {
    return bLoaded;
}