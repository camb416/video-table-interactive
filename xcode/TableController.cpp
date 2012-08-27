//
//  TableController.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/27/12.
//
//

#include "TableController.h"


void  TableController::setup(AppModel * _model, vector<RecipeView> * _views){
    model = _model;
    views = _views;
}
void TableController::handleKeyPress(char _key){
    console() << "check this out, yo: " << _key << endl;
    
    for(int i=0;i<views->size();i++){
        console() << "does recipeview 1 have key: " << _key << "? answer: " << views->at(i).getKeyFunction(_key) << endl;
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
void TableController::handleKeyRelease(char _key){
    console() << "check this out, yo: " << _key << endl;
    
    for(int i=0;i<views->size();i++){
        console() << "does recipeview 1 have key: " << _key << "? answer: " << views->at(i).getKeyFunction(_key) << endl;
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
