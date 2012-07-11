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
}

void ProjectApp::parseXML()
{    
    XmlTree doc(loadResource( "USER_AREAS.xml" ) );
    for( XmlTree::Iter area = doc.begin(); area!= doc.end(); ++area )
    {
        XmlTree a = *area;
        mAreas.push_back( UserArea(a/*, pConnector*/) ) ;
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
