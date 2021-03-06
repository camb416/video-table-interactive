//
//  TableController.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/27/12.
//
//
#include "VideoTableApp.h"
#include "TableController.h"
#include "cinder/app/AppBasic.h"


void  TableController::setup(AppModel * _model, vector<RecipeView> * _views){
    model = _model;
    views = _views;
    debugState = PRODUCTION;
    updateViewStates();
}
int TableController::getDebugState(){
    return debugState;
}
void TableController::handleKeyPress(char _key){
    
    console() << "check this out, down: " << _key << endl;
    VideoTable *myApp;
    switch(_key){
        case '`':
        case '~':
            myApp = (VideoTable*)app::App::get();
            if(isFullScreen()){
                myApp->showCursor();
            } else {
                myApp->hideCursor();
            }
            setFullScreen( ! isFullScreen() );
            
            break;
        case ' ':
            debugState++;
            if(debugState>2){
                debugState = 0;
            }
            updateViewStates();
            break;
    }
    
    
    for(int i=0;i<views->size();i++){
        //  console() << "does recipeview 1 have key: " << _key << "? answer: " << views->at(i).getKeyFunction(_key) << endl;
        RecipeView * rv = &views->at(i);
        int keyFunc = rv->getKeyFunction(_key);
        switch(keyFunc){
            case 0:
                rv->backwardPress();
                break;
            case 1:
                rv->selectPress();
                break;
            case 2:
                rv->forwardPress();
                break;
                
            default:
                // do nothing
                break;
        }
    }
    
    
}
void TableController::updateViewStates(){
    for(int i=0;i<views->size();i++){
        console() << debugState << endl;
        views->at(i).setDebug(debugState);
    }
}
void TableController::handleKeyRelease(char _key){
    console() << "check this out, release: " << _key << endl;
    
    for(int i=0;i<views->size();i++){
        //   console() << "does recipeview 1 have key: " << _key << "? answer: " << views->at(i).getKeyFunction(_key) << endl;
        RecipeView * rv = &views->at(i);
        int keyFunc = rv->getKeyFunction(_key);
        switch(keyFunc){
            case 0:
                rv->backwardRelease();
                break;
            case 1:
                rv->selectRelease();
                break;
            case 2:
                rv->forwardRelease();
                break;
            default:
                // do nothing
                break;
        }
    }
    
    
    
}
