//
//  CinderProjectApp.h
//  CinderProject
//
//  Created by Cameron Browning on 8/27/12.
//
//

#ifndef CinderProject_CinderProjectApp_h
#define CinderProject_CinderProjectApp_h

#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Xml.h"
#include <queue>
#include "PhidgetConnector.h"
#include "GalleryHelper.h"
#include "AppModel.h"
#include "UserArea.h"
#include "RecipeView.h"
#include "TableController.h"
#include "CursorTarget.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideoTable : public AppBasic {
public:
	void setup();
    
	void keyDown( KeyEvent event );
    void mouseDown ( MouseEvent evt);
    void keyUp(KeyEvent event);
    void prepareSettings( Settings *settings );
	void update();
	void draw();
    
    AppModel model;
    
    vector<UserArea> mAreas;
    PhidgetConnector pConnector;    // the Phidget Connector object.
    
private:
    void parseXML();
    

    
    gl::Texture background_tex;
    gl::Texture foreground_tex;
    float width, height;
    bool useTouch;
    
    Vec2f defaultWindowSize;
    Vec2f windowScale;
    
    vector<RecipeView> recipeViews;
    TableController controller;
    
    gallerytools::CursorTarget * cTarget;
};

#endif
