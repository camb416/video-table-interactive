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
    void parseXML();
    
    vector<UserArea> mAreas;
    PhidgetConnector pConnector;    // the Phidget Connector object.

    bool oldVal;        // keeps track of touch sensor's changes
    bool newVal;

};

void ProjectApp::setup()
{
    parseXML();
    // seed a random number
    srand ( time(NULL) );
    
    pConnector.useEvents(false);
    pConnector.connect(148986);

    oldVal = false;
    
    
    // while passing Rectfs makes it easier to draw in GL,
    // it's nice to abstract the positioning of the user area
    // considering that we will never scale an entire user area.
    // although, we may scale individual parts of it, we want positionability,
    // but not scalability in rendering these things.


    // eventually, we'll take care of this rectangle stuff in the videoplayer class
    // and just have it generate the rect from the size of the video file
    // it loads. Also, the flipped flag can go away. I like the keystroke in the constructor though.
    // it would be really cool to load this data from an XML file. That way we could add/remove user areas
    // and/or change keypresses or reposition them using XML and not recompiling...
}

void ProjectApp::parseXML()
{
 /*   char key;
    Rectf r = Rectf(0, 0, 640, 480);  
    float x, y, angle;
    Vec2f pos;
    vector<string> videos;  */
    
    XmlTree doc(loadResource( "USER_AREAS.xml" ) );
    for( XmlTree::Iter area = doc.begin(); area!= doc.end(); ++area )
    {
       /* key = area->getAttributeValue<char>( "key" );
        x = area->getAttributeValue<float>( "centerX" );
        y = area->getAttributeValue<float>( "centerY" );
        angle = area->getAttributeValue<float>( "angle" );
        pos = Vec2f(x, y);
        
        for( XmlTree::Iter vid = area->begin(); vid != area->end(); ++vid)
            videos.push_back(vid->getValue());  
        
        mAreas.push_back(UserArea( key, r, videos, angle, pos ));
        videos.clear(); */
        XmlTree a = *area;
        mAreas.push_back( UserArea(a) ) ;
    }

}

void ProjectApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1760, 960 );
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
    
    // iterate, update areas
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
         p->update();
    
    //pConnector.print();
    //console() << pConnector.getVal(148986, 7);
    
    newVal = pConnector.getBool(148986, 7);
    
    if (newVal && !oldVal)
    {
        console() << "push" << endl;
        for(int i = 0; i<mAreas.size(); i++)
            mAreas.at(i).nextMovie();
    }
    
    oldVal = newVal;
}

void ProjectApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	gl::enableAlphaBlending();
    
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
    {
        p->draw();
    }
}

CINDER_APP_BASIC( ProjectApp, RendererGl(0) );
