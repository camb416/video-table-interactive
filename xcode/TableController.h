//
//  TableController.h
//  CinderProject
//
//  Created by Cameron Browning on 8/27/12.
//
//

#ifndef __CinderProject__TableController__
#define __CinderProject__TableController__

#include "AppModel.h"
#include "RecipeView.h"
#include <iostream>

class TableController{
public:
   void  setup(AppModel * _model, vector<RecipeView>  * _views);
    void handleKeyPress(char _key);
    void handleKeyRelease(char _key);
private:
    AppModel * model;
    vector<RecipeView> * views;
    
};

#endif /* defined(__CinderProject__TableController__) */
