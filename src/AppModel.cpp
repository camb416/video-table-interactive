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
    
    curLanguage = 0;
    
    basePath = getHomeDirectory().string()+"/Desktop/videotable/";
    assetsPath = "assets/";
    settingsPath ="settings/";
    
    useSensors = true;
    useFrontPlate = false;
    backgroundPath = "problem loading background path from settings";
     foregroundPath = "problem loading background path from settings";
    buttonPath = "problem loading button path from settings";
    isFullScreen = false;
    
    XmlTree appTree(loadFile(basePath+settingsPath+_appFilePath));
    
    
        XmlTree root;
    try {
        root = appTree.getChild("plist");
    } catch(XmlTree::Exception e){
        console() << "the settings file doesn't look like a plist file." << endl;
        return -1;
    }
    try {
        parseSettings(root);
    } catch(XmlTree::Exception e){
        console() << "a problem occurred parsing the settings plist file.";
        return -1;
    }

    
    
    XmlTree contentTree(loadFile( basePath+settingsPath+_contentFilePath ) );

    
    try {
        root = contentTree.getChild("plist");
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

void AppModel::parseSettings(XmlTree _root){
    XmlTree t = _root.getChild("dict");
    // is key background?
    // load background
    
    // is key user areas?
    // loop children
    // create userareamodel
    // set x, y, r
    // is it a button?
    
    UserAreaModel uam;
    TouchSensorModel tsm;
    ButtonModel bm;
    
    string topLevelKey = "";
    for( XmlTree::Iter child = t.begin(); child != t.end(); ++child ){
        string tagType = child->getTag();
        console() << "tag: " << tagType << endl;
        if(tagType.compare("key")==0){
            topLevelKey = child->getValue();
             console() << "topkey: " << topLevelKey << endl;
        } else {
            if(tagType.compare("string")==0 || tagType.compare("false")==0 || tagType.compare("true")==0){
                if(topLevelKey.compare("background")==0){
                    backgroundPath = basePath+assetsPath+child->getValue();
                } else if(topLevelKey.compare("foreground")==0){
                    foregroundPath = basePath+assetsPath+child->getValue();
                } else if(topLevelKey.compare("button")==0){
                    console() << "Button Value::: " << tagType << "!!!!!" << endl;
                    buttonPath = basePath+assetsPath+child->getValue();
                } else if(topLevelKey.compare("fullscreen")==0){
                    console() << "FULLSCREEN VALUE:::: " << tagType << "!!!!!!!!!" << endl;
                    if(tagType.compare("true")==0) isFullScreen = true;
                } else if(topLevelKey.compare("frontplate")==0){
                    console() << "FRONTPLATE VALUE:::: " << tagType << "!!!!!!!!!" << endl;
                    if(tagType.compare("true")==0) useFrontPlate = true;
                } else if(topLevelKey.compare("sensors")==0){
                    console() << "SENSORS VALUE:::: " << tagType << "!!!!!!!!!" << endl;
                    if(tagType.compare("false")==0) useSensors = false;
                } 
            } else if(tagType.compare("dict")==0){
                // this is either the user areas, or the sensor boards
                // depending on the toplevelkey
                XmlTree t2 = *child;
                string midLevelKey = "";
                for( XmlTree::Iter grandchild = t2.begin(); grandchild != t2.end(); ++grandchild ){
                    console() << grandchild->getTag() << " ::: " << grandchild->getValue() << endl;
                    string gcTagType = grandchild->getTag();
                    if(gcTagType.compare("key")==0){
                        midLevelKey = grandchild->getValue();
                    } else {
                        console() << "GRANCHILDLEVEL: " << grandchild->getValue() << " : " << midLevelKey << ", " << topLevelKey << endl;
                        
                        if(topLevelKey.compare("User Areas")==0){
                            uam = UserAreaModel();
                        } else if(topLevelKey.compare("Sensor Boards")==0){
                            tsm = TouchSensorModel();
                        } else if(topLevelKey.compare("languages")==0){
                            // we're looping the languages...
                            console() << "here's a language: " << grandchild->getValue() << endl;
                            languages.push_back(grandchild->getValue());
                            
                        }
                        
                        
                        // this should always be a dict (either a list of nums and strings for user areas, or nums for sensor boards)
                        XmlTree t3 = *grandchild;
                        string bottomLevelKey = "";
                        for( XmlTree::Iter baby = t3.begin(); baby != t3.end(); ++baby ){
                            string babyTag = baby->getTag();
                            
                            if(babyTag.compare("key")==0){
                                bottomLevelKey = baby->getValue();
                            } else if(babyTag.compare("dict")!=0){
                                console() << "BABY LEVEL: " << baby->getValue() << " : " << bottomLevelKey << " : " << midLevelKey << ", " << topLevelKey << endl;
                                
                                if(topLevelKey.compare("User Areas")==0){
                                    if(bottomLevelKey.compare("x")==0){
                                        uam.x = atof(baby->getValue().c_str());
                                    } else if(bottomLevelKey.compare("y")==0){
                                        uam.y = atof(baby->getValue().c_str());
                                    } else if(bottomLevelKey.compare("r")==0){
                                        uam.r = atof(baby->getValue().c_str());
                                    }else if(bottomLevelKey.compare("recipe")==0){
                                        uam.recipe = baby->getValue();
                                    } else if(bottomLevelKey.compare("button")>0){
                                        bm = ButtonModel();
                                    }
                                } else if(topLevelKey.compare("Sensor Boards")==0) {
                                    tsm.sensor = atoi(baby->getValue().c_str());
                                    tsm.keymap = bottomLevelKey[0];
                                    tsm.board = atoi(midLevelKey.c_str());
                                    tsm.val = 0;
                                    tsm.prev = 0;
                                    sensors.push_back(tsm);
                                }
                                
                            } else {
                                if(topLevelKey.compare("User Areas")==0){
                                    uam.name = midLevelKey;
                                }
                                
                                
                                XmlTree t4 = *baby;
                                string easyModeKey = "";
                                for( XmlTree::Iter zygote = t4.begin(); zygote != t4.end(); ++zygote ){
                                    string zygoteTag = zygote->getTag();
                                    
                                    if(zygoteTag.compare("key")==0){
                                        easyModeKey = zygote->getValue();
                                    } else {
                                        string zValue = zygote->getValue();
                                        console() << "ZYGOTE LEVEL: " << zValue << ": " << easyModeKey << " : " << bottomLevelKey << " : " << midLevelKey << ", " << topLevelKey << endl;
                                        if(easyModeKey.compare("x")==0){
                                            bm.x = atoi(zValue.c_str());
                                        } else if(easyModeKey.compare("y")==0){
                                            bm.y = atoi(zValue.c_str());
                                        } else if(easyModeKey.compare("keymap")==0){
                                            console() << "here's a keymap::: " << zValue << endl;
                                            bm.keymap = zValue[0];
                                            console() << "again::: " << bm.keymap << endl;
                                        }
                                    }
                                }
                                bm.path = buttonPath;
                                if(bottomLevelKey.compare("back-button")==0){
                                    uam.back_btn = bm;
                                } else if(bottomLevelKey.compare("select-button")==0){
                                    uam.select_btn = bm;
                                } else if(bottomLevelKey.compare("forward-button")==0){
                                    uam.fwd_btn = bm;
                                } else {
                                    console() << "couldn't find this button in the ua model... " << easyModeKey << endl;
                                }
                            }
                    
                        
                        
                        }
                        if(topLevelKey.compare("User Areas")==0){
                            areas.push_back(uam);
                        }
                    }
                }
            }
        }
    }
}

RecipeModel AppModel::getRecipeModel(string _recipeTitle){
    
    for(int i=0;i<recipes.size();i++){
        console() << "comparing: " << recipes.at(i).name << " to: " << _recipeTitle << ", result: " << recipes.at(i).name.compare(_recipeTitle) << endl;
        if(recipes.at(i).name.compare(_recipeTitle)==0){
            return recipes.at(i);
        }
    }
    console() << "couldn't find the requested recipe model: " << _recipeTitle << endl;
    return RecipeModel();
}


void AppModel::parseRecipes(XmlTree _root){
    XmlTree t = _root.getChild("dict/dict");
    
    for( XmlTree::Iter child = t.begin(); child != t.end(); ++child ){
        if(child->getTag().compare("key")==0){
            // use this value as the name for a new Recipe object
            RecipeModel rm;
            rm.name = child->getValue();
            recipes.push_back(rm);
        } else {
            XmlTree t2 = *child;
            string whichKey;
            for( XmlTree::Iter grandchild = t2.begin(); grandchild != t2.end(); ++grandchild ){                
                if(grandchild->getTag().compare("key")==0){
                    whichKey = grandchild->getValue();
                } else if(grandchild->getTag().compare("dict")==0){                    
                    if(whichKey.compare("Steps")==0){
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
                                        if(stepKey.compare("img")==0){
                                            for(int i=0;i<languages.size();i++){
                                                sm.img.push_back(basePath+assetsPath+languages.at(i)+"/"+baby->getValue());
                                            }
                                        //    console() << "the image is: " << sm.img << ", while the language is: " << whichLanguage << endl;
                                        } else if(stepKey.compare("video")==0){
                                            for(int i=0;i<languages.size();i++){
                                            sm.video.push_back(basePath+assetsPath+languages.at(i)+"/"+baby->getValue());
                                            }
                                        } else {
                                            console() << "I got a property of a cookstep that was unexpected: " << stepKey << ", " << baby->getValue();
                                        }
                                        
                                    }
                                }
                            } else if(greatChild->getTag().compare("key")==0){
                                if(recipes.size()>0 && sm.name.compare("")!=0){
                                    recipes.at(recipes.size()-1).steps.push_back(sm);
                                }
                                sm.name = "";
                                sm.video.clear();
                                sm.img.clear();
                                sm.name = greatChild->getValue();
                            }
                            
                        }
                        if(sm.name.compare("")!=0){
                            recipes.at(recipes.size()-1).steps.push_back(sm);
                        }
                    }
                    
                } else {
                   // do nothing?
                }
                
            }
        }
        
    }
}