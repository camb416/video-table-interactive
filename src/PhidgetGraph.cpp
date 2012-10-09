//
//  PhidgetGraph.cpp
//  VideoTable
//
//  Created by Cameron Browning on 10/9/12.
//
//

#include "PhidgetGraph.h"








void PhidgetGraph::setup(PhidgetConnector * _pc, vector<TouchSensorModel> * _sensors)
{
    margin = 15;
    gutter = 20;
    
    
    
    
    pConnector = _pc;
    sensors = _sensors;
    
    numSensors = sensors->size();
    sensorAddrs = new Vec2i[numSensors];
    for(int i=0;i<sensors->size();i++){
        TouchSensorModel tsm = sensors->at(i);
        sensorAddrs[i] = Vec2i(tsm.board,tsm.sensor);
    }
    
    for(int i=0;i<numSensors;i++){
            int Rw = (getWindowWidth()-2*margin-gutter*(numSensors-1))/(numSensors);
            int Rx = margin+Rw*i+gutter*(i);
            int Ry = getWindowHeight()-margin;
            int Rh = 0;
            rectangles.push_back(Rectf( Vec2f( Rx,Ry ), Vec2f( Rx+Rw,Ry+Rh ) ));   
    }
    for(int i=0;i<numSensors;i++){
        dValues.push_back(10);
        values.push_back(100);
    }
}

void PhidgetGraph::mouseDown( MouseEvent event ){
    //   pConnector.reset();
    pConnector->print();
}

void PhidgetGraph::update(){
    // manually request the block to update the info from the hardware
    // pConnector->updateKits();
    
    for(int i=0;i<numSensors;i++){
        
        // return a true/false for the sensor (uses 500 as a cutoff
        // this seems weird
        bool thisBool = pConnector->getBool(sensorAddrs[i].x,sensorAddrs[i].y); ///1000.0f*(getWindowHeight()-margin*2);
        float thisFloat;
        if(thisBool){
            //thisInt = (getWindowHeight()-margin*2);
            thisFloat = 1.0f;
//            console() << "big" << endl;
        } else {
            thisFloat = 0.1f;
        }
        dValues.at(i) = thisFloat;
    }
    
    for(int i=0;i<dValues.size();i++){
        values.at(i) += (dValues.at(i)-values.at(i))/16.0f;
        rectangles.at(i).y1 = rectangles.at(i).y2-values.at(i);
    }
}

void PhidgetGraph::draw(Rectf _drawrect){
   // resize(_drawrect);
    float rectWidth = (_drawrect.getWidth()-margin*2.0f-((numSensors-1)*gutter))/numSensors;
    
    gl::color(0,0,0,0.75f);
    ci::gl::drawSolidRoundedRect(_drawrect,20.0f);
    for(int i=0;i<numSensors;i++){
       
        // Rectf thisRect = Rectf(margin+(rectWidth*i),margin,margin+(rectWidth*i)+rectWidth,_drawrect.getHeight()-values.at(i)*_drawrect.getHeight());
       
        Rectf thisRect = Rectf(
                               i*(rectWidth+gutter)+margin+_drawrect.x1,
                               _drawrect.y2-values.at(i)*(_drawrect.getHeight()-margin*2.0f),
                               i*(rectWidth+gutter)+margin+rectWidth+_drawrect.x1,
                               _drawrect.y2-margin
                               );
        
         Rectf shadowRect = Rectf(thisRect.x1-10.0f,thisRect.y1-10.0f,thisRect.x2+10.0f,thisRect.y2+10.0f);
        ci::gl::color(0,0,0,0.25f);
        ci::gl::drawSolidRoundedRect(shadowRect, 15.0f);
        shadowRect = Rectf(thisRect.x1-5.0f,thisRect.y1-5.0f,thisRect.x2+5.0f,thisRect.y2+5.0f);
        ci::gl::color(255,255,255,0.25f);
       ci::gl::drawSolidRoundedRect(shadowRect, 10.0f);
        ci::gl::color(255,255,255);
        ci::gl::drawSolidRoundedRect(thisRect, 5.0f);
    }
}

void PhidgetGraph::resize(Rectf _rect){
    rectangles.clear();
    for(int i=0;i<numSensors;i++){
        int Rw = (_rect.getWidth()-2*margin-gutter*(numSensors-1))/(numSensors);
        int Rx = margin+Rw*i+gutter*(i);
        int Ry = _rect.getHeight()-margin;
        int Rh = 0;
        rectangles.push_back(Rectf( Vec2f( Rx,Ry ), Vec2f( Rx+Rw,Ry+Rh ) ));
    }
    
}



