//
//  TableController.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/27/12.
//
//
#include "CinderProjectApp.h"
#include "TableController.h"
#include "cinder/app/AppBasic.h"


void  TableController::setup(AppModel * _model, vector<RecipeView> * _views){
    model = _model;
    views = _views;
    debugState = DEVELOPMENT;
}
int TableController::getDebugState(){
    return debugState;
}
void TableController::handleKeyPress(char _key){
    console() << "check this out, yo: " << _key << endl;
    
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
    ProjectApp *myApp = (ProjectApp*)app::App::get();

    switch(_key){
        case '`':
        case '~':
            
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
            if(debugState!=0){
                myApp->showCursor();
            } else {
                myApp->hideCursor();
            }
            updateViewStates();
            break;
    }
    
}
void TableController::updateViewStates(){
    for(int i=0;i<views->size();i++){
        views->at(i).setDebug(debugState);
    }
}
void TableController::handleKeyRelease(char _key){
    console() << "check this out, yo: " << _key << endl;
    
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
