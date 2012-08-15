
#include "PlistReader.h"

void PlistReader::trace(XmlTree t){
    for( XmlTree::Iter child = t.begin(); child != t.end(); ++child ){
        console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;
        if(child->getTag().compare("dict")==0){
            trace(*child);
        }
        
    }
}

PlistReader::PlistReader()
{
    XmlTree plist =  XmlTree(loadResource( "RECIPES.plist" ) );
    console() << "this is the tag name... " << plist.getTag() << "IS THIS A DOC ELEMENT OR WAHAT???? " << plist.isDocument() << endl;
    try {
        root = plist.getChild("plist");
    } catch(XmlTree::Exception e){
        console() << "darn" << endl;
    }
    //trace(root);
    parseRecipes();
}



void PlistReader::parseRecipes(){
    XmlTree t = root.getChild("dict/dict");
    for( XmlTree::Iter child = t.begin(); child != t.end(); ++child ){
        console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;
        if(child->getTag().compare("key")==0){
            // use this value as the name for a new Recipe object
            RecipeModel rm;
            rm.name = child->getValue();
            recipeModels.push_back(rm);
        } else {
            console() << "check it out, this is probably a dict:::: " << child->getTag() << "." << endl;
            XmlTree t2 = *child;
            string whichKey;
            for( XmlTree::Iter grandchild = t2.begin(); grandchild != t2.end(); ++grandchild ){
                console() << "\t Tag: " << grandchild->getTag() << "  Value: " << grandchild->getValue() << endl;
                
                if(grandchild->getTag().compare("key")==0){
                    // its a key yo
                    whichKey = grandchild->getValue();
                    console() << "\t\t right after, whichkey is: " << whichKey << endl;
                    
                } else if(grandchild->getTag().compare("dict")==0){
                    // surely these are Steps??
                    
                    if(whichKey.compare("Steps")==0){
                        console() << " I FOUND A DICT AND LO AND BEHOLD its a Steps child... "<< grandchild->getValue() << endl;
                        
                        // it must be time to dig through these bloomin STEPS.
                        // loop through em.
                        
                        XmlTree t3 = *grandchild;
                        StepModel sm;
                        for( XmlTree::Iter greatChild = t3.begin(); greatChild != t3.end(); ++greatChild ){
                            XmlTree t4 = *greatChild;
                            
                            string stepKey;
                            
                            
                            
                            if(greatChild->getTag().compare("dict")==0){
                                
                                for( XmlTree::Iter baby = t4.begin(); baby != t4.end(); ++baby ){
                                    if(baby->getTag().compare("key")==0){
                                        stepKey = baby->getValue();
                                    } else {
                                        // then its likely a value
                                        console() << "\t\t\t\t\t\t\t\t " << stepKey << "  Value: " << baby->getValue() << endl;
                                        if(stepKey.compare("start-image")==0){
                                            sm.start_img = baby->getValue();
                                        } else if(stepKey.compare("name")==0){
                                            sm.name = baby->getValue();
                                        } else if(stepKey.compare("video")==0){
                                            sm.video = baby->getValue();
                                        } else {
                                            console() << "I got a property of a cookstep that was unexpected: " << stepKey << ", " << baby->getValue();
                                        }
                                        
                                    }
                                }
                            } else if(greatChild->getTag().compare("key")==0){
                                if(recipeModels.size()>0 && sm.name.compare("")!=0){
                                    recipeModels.at(recipeModels.size()-1).steps.push_back(sm);
                                }
                                console() << " this should be the name of the step... "<< greatChild->getValue() << endl;
                                sm.name = sm.video = sm.start_img = "";
                                sm.name = greatChild->getValue();
                            }
                            
                        }
                        if(sm.name.compare("")!=0){
                        console() << "putting the stepmodel in the vector..." << endl;
                        recipeModels.at(recipeModels.size()-1).steps.push_back(sm);
                        }
                        
                        
                        
                        
                    }
                    
                } else {
                    // its some kinda value, son
                    console() << "\t\t\t whichkey is: " << whichKey << endl;
                    if(whichKey.compare("menu-image")==0){
                        recipeModels.at(recipeModels.size()-1).menu_img = grandchild->getValue();
                    } else if( whichKey.compare("end-image")==0){
                        recipeModels.at(recipeModels.size()-1).end_img = grandchild->getValue();
                    } else{
                        // do nothing man
                        console() << "doing nothing" << endl;
                    }
                    
                }
                
            }
        }
        
    }
}
