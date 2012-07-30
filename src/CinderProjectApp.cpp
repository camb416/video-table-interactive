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
    
    vector<UserArea> mAreas;
    PhidgetConnector pConnector;    // the Phidget Connector object.

private:
    void parseXML();
    string background;
    gl::Texture mTexture;
    float width, height;
    bool useTouch;
    
};

void ProjectApp::setup()
{
    parseXML();
    mTexture = gl::Texture( loadImage( loadResource( background ) ) );
    
    if(useTouch){
        pConnector.useEvents(false);
        pConnector.connect(148986);
    }
    
    width = 1760.0;
    height = 960.0;
}

void ProjectApp::parseXML()
{    
    try {
        XmlTree doc(loadResource( "USER_AREAS.xml" ) );
        XmlTree areas = doc.getChild("project");
        background = areas.getAttributeValue<string>("background");
        mTexture = gl::Texture( loadImage( loadResource( background ) ) );
        
        //
        // katie please fix this so it gets this string from the "usetouch" attribute of the <project> tag.
        //
        string useTouch_str = "false";//areas.getAttributeValue<string>("usetouch");
        //
        //
        
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
	settings->setWindowSize( 1760.0, 960.0 );
	settings->setFrameRate( 60.0f );
}

void ProjectApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'f' ) {
		setFullScreen( ! isFullScreen() );
	}
    
    //iterate, if key pressed matches player key, change video of that player
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
        if (event.getChar() == p->getKey())
            p->nextMovie();
}

void ProjectApp::update()
{
    
    pConnector.updateKits();
    
    // Update UserAreas
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
         p->update();
}

void ProjectApp::draw()
{
	gl::clear( Color( 0, 0, 0) );
    gl::enableAlphaBlending();
    
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
        p->drawBackground();
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
        p->draw();  
}

CINDER_APP_BASIC( ProjectApp, RendererGl(0) );
