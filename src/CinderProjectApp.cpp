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

    // seed a random number
    srand ( time(NULL) );

    Rectf r = Rectf(0, 0, 640, 480);    
    // while passing Rectfs makes it easier to draw in GL,
    // it's nice to abstract the positioning of the user area
    // considering that we will never scale an entire user area.
    // although, we may scale individual parts of it, we want positionability,
    // but not scalability in rendering these things.

    
    Vec2f pos0 = Vec2f(320.0f,240.0f);
    Vec2f pos1 = Vec2f(960.0f,240.0f);
    Vec2f pos2 = Vec2f(320.0f,720.0f);
    Vec2f pos3 = Vec2f(960.0f,720.0f);

    // eventually, we'll take care of this rectangle stuff in the videoplayer class
    // and just have it generate the rect from the size of the video file
    // it loads. Also, the flipped flag can go away. I like the keystroke in the constructor though.
    // it would be really cool to load this data from an XML file. That way we could add/remove user areas
    // and/or change keypresses or reposition them using XML and not recompiling...
    mAreas.push_back(UserArea('a' , r, false, 180, pos0));
    mAreas.push_back(UserArea('s' , r, false, 180, pos1));
    mAreas.push_back(UserArea('z' , r, false, 0, pos2));
    mAreas.push_back(UserArea('x' , r, false, 0, pos3));                 
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
