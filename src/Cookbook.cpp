//
//  Settings.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/6/12.
//
//

#include <iostream>

#include "Cookbook.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int Cookbook::setup(){
    //XmlTree doc;
try {
    XmlTree doc(loadResource( "RECIPES.plist" ) );
    
    console() << doc << endl;
    
}
catch ( ... ) {
    console() << "Unable to load XML document. Check for syntax errors." << endl;
}
    return 0;
}