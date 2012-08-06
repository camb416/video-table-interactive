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

using namespace ci;
using namespace ci::app;
using namespace std;

class ProjectApp : public AppBasic {
public:
	void setup();
    
	void keyDown( KeyEvent event );
    void prepareSettings( Settings *settings );
	void update();
	void draw();
    
    AppModel model;
    
    vector<UserArea> mAreas;
    PhidgetConnector pConnector;    // the Phidget Connector object.

private:
    void parseXML();
    string background_str;
    gl::Texture background_tex;
    float width, height;
    bool useTouch;
    int debugState;
    Vec2f defaultWindowSize;
    Vec2f windowScale;
    
};

void ProjectApp::setup()
{
    debugState = DEVELOPMENT;
    
    model.setup("APP.plist","RECIPES.plist");
    
    parseXML();
    
    
    background_tex = gl::Texture( loadImage( loadResource( background_str ) ) );
    
    
    
    if(useTouch){
        pConnector.useEvents(false);
        pConnector.connect(148986);
    }
    
    // get these from the XML
    setWindowSize(defaultWindowSize.x, defaultWindowSize.y);
//    width = 1920.0;
 //   height = 1200.0;
}

void ProjectApp::parseXML()
{
    mAreas.clear();
    try {
        XmlTree doc(loadResource( "USER_AREAS.xml" ) );
        XmlTree areas = doc.getChild("project");
        background_str = areas.getAttributeValue<string>("background");
        background_tex = gl::Texture( loadImage( loadResource( background_str ) ) );
        
        //
        // katie: please fix this so it gets this string from the "usetouch" attribute of the <project> tag.
        //
        string useTouch_str = "false";//areas.getAttributeValue<string>("usetouch");
        //
        //
        float scrW = areas.getAttributeValue<float>("screenwidth");
        float scrH = areas.getAttributeValue<float>("screenheight");

        defaultWindowSize = Vec2f(scrW,scrH);
        
        if(useTouch_str=="false" || useTouch_str=="no" || useTouch_str == "none" || useTouch_str == "0"){
            console() << "looks like we don't want to use touch" << endl;
            useTouch = false;
        } else {
            useTouch = true;
        }
        
        PhidgetConnector * pc;
        if(useTouch){
            pc = &pConnector;
        } else {
            pc = NULL;
        }
        for( XmlTree::Iter area = areas.begin(); area!= areas.end(); ++area )
        {
            XmlTree a = *area;
            mAreas.push_back( UserArea(a, pc) ) ;
        }
    }
    catch ( ... ) {
        console() << "Unable to load XML document. Check for syntax errors." << endl;
    }
}

void ProjectApp::prepareSettings( Settings *settings )
{
	// settings->setWindowSize( 1920,1200 );
	settings->setFrameRate( 60.0f );
    // katie: this doesn't work... probably needs to be in setup (also, have it work with the XML settings in <project>
    setFullScreen(true);
}

void ProjectApp::keyDown( KeyEvent event )
{
    switch(event.getChar()){
            case 'f':
            case 'F':
                setFullScreen( ! isFullScreen() );
            break;
            case ' ':
            debugState++;
            if(debugState>2){
                debugState = 0;
            }
            break;
            case 's':
            case 'S':
            parseXML();
            break;
    }

    
    //iterate, if key pressed matches player key, change video of that player
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
        if (event.getChar() == p->getKey())
            p->nextMovie();
}

void ProjectApp::update()
{
    
    pConnector.updateKits();
    
    Area curWindowSizeA = getWindowBounds();
    Vec2f curWindowSize = Vec2f(curWindowSizeA.getWidth(),curWindowSizeA.getHeight());
    windowScale = curWindowSize/defaultWindowSize;
    
    // Update UserAreas
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p){
         p->update();
    }
}

void ProjectApp::draw()
{
    bool debugDrawFlag = debugState != 0;
    gl::draw(background_tex,getWindowBounds());
	//gl::clear( Color( 0, 0, 0) );
    gl::enableAlphaBlending();
    
    //for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
       // p->drawBackground(debugDrawFlag);
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p){
        p->draw(debugDrawFlag, windowScale);
    }
}

CINDER_APP_BASIC( ProjectApp, RendererGl(0) );
