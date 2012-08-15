//
//  Settings.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#include <iostream>

#include "AppModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int AppModel::setup(string _appFilePath, string _contentFilePath){
    // 1: load app file
    // 2: populate settings model
    // 3: load content file
    // 4: populate recipes models
    
   // XmlTree plist;
    XmlTree root;
    
 //   console() << "I THINK I WILL LOAD THIS: " << _contentFilePath << endl;

    XmlTree plist(loadResource( _contentFilePath ) );
    
   // console() << plist << endl;
    

   // console() << "this is the tag name... " << plist.getTag() << "IS THIS A DOC ELEMENT OR WAHAT???? " << plist.isDocument() << endl;
    try {
    //    console() << "again... " << plist;
        root = plist.getChild("plist");
    } catch(XmlTree::Exception e){
        console() << "the content file doesn't look like a plist file." << endl;
    }
    try {
    parseRecipes(root);
    } catch(XmlTree::Exception e){
        console() << "a problem occurred parsing the recipes plist file.";
        return -1;
    }
    
    return 0;
}


int AppModel::pretendSetup(){
    RecipeModel rm;
    rm.testCase();
    for(int i=0;i<4;i++){
        recipes.push_back(rm);
    }
    bLoaded = true;
    return 0;
}
int AppModel::trace(){
    if(bLoaded){
        console() << "APPMODEL: " << endl;
    for(int i=0;i<recipes.size();i++){
        recipes.at(i).trace();
    }
        return 0;
    } else {
        return -1;
    }
}
void AppModel::parseRecipes(XmlTree _root){
    XmlTree t = _root.getChild("dict/dict");
    
    for( XmlTree::Iter child = t.begin(); child != t.end(); ++child ){
      //  console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;
        if(child->getTag().compare("key")==0){
            // use this value as the name for a new Recipe object
            RecipeModel rm;
            rm.name = child->getValue();
            recipes.push_back(rm);
        } else {
        //    console() << "check it out, this is probably a dict:::: " << child->getTag() << "." << endl;
            XmlTree t2 = *child;
            string whichKey;
            for( XmlTree::Iter grandchild = t2.begin(); grandchild != t2.end(); ++grandchild ){
          //      console() << "\t Tag: " << grandchild->getTag() << "  Value: " << grandchild->getValue() << endl;
                
                if(grandchild->getTag().compare("key")==0){
                    // its a key yo
                    whichKey = grandchild->getValue();
            //        console() << "\t\t right after, whichkey is: " << whichKey << endl;
                    
                } else if(grandchild->getTag().compare("dict")==0){
                    // surely these are Steps??
                    
                    if(whichKey.compare("Steps")==0){
                //        console() << " I FOUND A DICT AND LO AND BEHOLD its a Steps child... "<< grandchild->getValue() << endl;
                        
                        // it must be time to dig through these bloomin STEPS.
                        // loop through em.
                        
                        XmlTree t3 = *grandchild;
                        CookStepModel sm;
                        for( XmlTree::Iter greatChild = t3.begin(); greatChild != t3.end(); ++greatChild ){
                            XmlTree t4 = *greatChild;
                            
                            string stepKey;
                            
                            
                            
                            if(greatChild->getTag().compare("dict")==0){
                                
                                for( XmlTree::Iter baby = t4.begin(); baby != t4.end(); ++baby ){
                                    if(baby->getTag().compare("key")==0){
                                        stepKey = baby->getValue();
                                    } else {
                                        // then its likely a value
                                //        console() << "\t\t\t\t\t\t\t\t " << stepKey << "  Value: " << baby->getValue() << endl;
                                        if(stepKey.compare("img")==0){
                                            sm.img = baby->getValue();
                                        } else if(stepKey.compare("video")==0){
                                            sm.video = baby->getValue();
                                        } else {
                                            console() << "I got a property of a cookstep that was unexpected: " << stepKey << ", " << baby->getValue();
                                        }
                                        
                                    }
                                }
                            } else if(greatChild->getTag().compare("key")==0){
                                if(recipes.size()>0 && sm.name.compare("")!=0){
                            //          console() << "putting the stepmodel in the vector..." << endl;
                                    recipes.at(recipes.size()-1).steps.push_back(sm);
                                }
                          //      console() << " this should be the name of the step... "<< greatChild->getValue() << endl;
                                sm.name = sm.video = sm.img = "";
                                sm.name = greatChild->getValue();
                            }
                            
                        }
                        if(sm.name.compare("")!=0){
                   //         console() << "putting the stepmodel in the vector..." << endl;
                            recipes.at(recipes.size()-1).steps.push_back(sm);
                        }
                        
                        
                        
                        
                    }
                    
                } else {
                    // its some kinda value, son
           //         console() << "\t\t\t whichkey is: " << whichKey << endl;
                   // do nothing?
                    
                }
                
            }
        }
        
    }
}