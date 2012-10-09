//
//  PhidgetGraph.h
//  VideoTable
//
//  Created by Cameron Browning on 10/9/12.
//
//

#ifndef __VideoTable__PhidgetGraph__
#define __VideoTable__PhidgetGraph__


#include "cinder/app/AppBasic.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/Camera.h"
#include "cinder/Text.h"
#include "cinder/Rect.h"
#include "PhidgetConnector.h"
#include "AppModel.h"
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class PhidgetGraph{
    
public:
	void setup(PhidgetConnector * _pc, vector<TouchSensorModel> * _sensors);
	void mouseDown( MouseEvent event );	
	void update();
	void draw(Rectf _drawrect);
    void resize(Rectf _rect);
    vector<float> dValues;
    vector<float> values;
    vector<Rectf> rectangles;
    Vec2i * sensorAddrs;
    int numSensors;
    int margin;
    int gutter;
    vector<TouchSensorModel> * sensors;
    
    PhidgetConnector * pConnector;    // the Phidget Connector object.
    
};
#endif /* defined(__VideoTable__PhidgetGraph__) */
