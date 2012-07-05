#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"

//#include "VideoPlayer.h"
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
};

void ProjectApp::setup()
{
    Rectf r = Rectf(0, 0, 640, 480);
    Rectf r2 = Rectf(640, 0, 1280, 480);
    Rectf r3 = Rectf(0, 480, 640, 960);
    Rectf r4 = Rectf(640, 480, 1280, 960);
    
    mAreas.push_back(UserArea('a' , r, true, 0 ));
    mAreas.push_back(UserArea('s' , r, true, 45 ));
    mAreas.push_back(UserArea('z' , r, false, 90 ));
    mAreas.push_back(UserArea('x' , r, false , 135));                 
}

void ProjectApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 960 );
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
    // iterate, update areas
    for (vector<UserArea>::iterator p = mAreas.begin(); p != mAreas.end(); ++p)
         p->update();
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
