//
//  CookStep.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
//

#include "CookStep.h"

int CookStep::setImage(string _path){
    int returnVal = img.load(_path);
    return returnVal;
}

int CookStep::setVideo(string _path){
    int returnVal = -1;//video.load(_path);
    
    return returnVal;
}

int CookStep::setBtn(string _path){
    int returnVal = btn_overlay.load(_path);
    return returnVal;
}