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

using namespace ci;
using namespace ci::app;
using namespace std;

class ProjectApp : public AppBasic {
public:
	void setup();
    
	void keyDown( KeyEvent event );
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
    float width, height;
    bool useTouch;

    Vec2f defaultWindowSize;
    Vec2f windowScale;
    
    vector<RecipeView> recipeViews;
    TableController controller;
};

void ProjectApp::setup()
{
    //debugState = DEVELOPMENT;
   
    
    controller.setup(&model,&recipeViews);
    
    model.setup("SETTINGS.plist","RECIPES.plist");
    
    // implement fullscreen test here...
    setFullScreen(model.isFullScreen);
    if(model.isFullScreen) hideCursor();
    
    // doubt these still work
    // model.pretendSetup();
    // model.trace();
    
    
     
    int numRecipes = model.recipes.size();
  
  //  myRecipeView = new RecipeView(model.recipes.at(0));
    
    for(int i=0;i<model.areas.size();i++){
        string thisRecipe_str = model.areas.at(i).recipe;
        UserAreaModel theUserAreaModel = model.areas.at(i);
        RecipeModel theRecipeModel = model.getRecipeModel(thisRecipe_str);
        recipeViews.push_back(RecipeView(theUserAreaModel, theRecipeModel));
    }
   /*
    for(int i=0;i<model.recipes.size();i++){
        recipeViews.push_back(RecipeView(model.recipes.at(i)));
    }
    */
    console() << "there are " << numRecipes << " recipes.";
    
    /*
    model.setup("APP.plist","RECIPES.plist");
    
    parseXML();
    
    
    
    
    
    
    if(useTouch){
        pConnector.useEvents(false);
        pConnector.connect(148986);
    }
    
    // get these from the XML
    setWindowSize(defaultWindowSize.x, defaultWindowSize.y);
//    width = 1920.0;
 //   height = 1200.0;
     */
    background_tex = gl::Texture( loadImage( loadResource( model.backgroundPath ) ) );
}

void ProjectApp::parseXML()
{
    console() << "ProjectApp::parseXML has been deprecated" << endl;
}

void ProjectApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1920,1200 );
    
    // maybe lowering might smooth things out?
	settings->setFrameRate( 60.0f );
}
void ProjectApp::keyUp(KeyEvent event){
     controller.handleKeyRelease(event.getChar());
}
void ProjectApp::keyDown( KeyEvent event )
{
    /*
    for(int i=0;i<recipeViews.size();i++){
       recipeViews.at(i).moveForward();
    }
     */
    controller.handleKeyPress(event.getChar());
    
    

    }

void ProjectApp::update()
{
    for(int i=0;i<recipeViews.size();i++){
        recipeViews.at(i).update();
    }
  
//    pConnector.updateKits();

}

void ProjectApp::draw()
{
    gl::clear( Color( 0, 0, 0) );
    gl::enableAlphaBlending();
    gl::color(1.0f,1.0f,1.0f);
    gl::draw(background_tex,getWindowBounds());
    for(int i=0;i<recipeViews.size();i++){
        recipeViews.at(i).draw();
    }
}

CINDER_APP_BASIC( ProjectApp, RendererGl(0) );
