//
//  Recipe.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/3/12.
//
//
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include "Resources.h"
#include "RecipeView.h"
#include <stdio.h>
#include <stdlib.h>

RecipeView::RecipeView(RecipeModel _model){
    recipeModel = _model;
    // menu_img.load(_model.getMenuImage());
    
    curStep = 0;
    stepState = 0;
    prevStepState = -1;
    prevStep = -1;
    img.load(recipeModel.getCookStep().img);
    img.hide();
    
    string normalFont( "Arial" );
    
	TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( normalFont, 24 ) );
	layout.setColor( Color( 1, 1, 1 ) );
	layout.addLine( "testing here");
	Surface8u rendered = layout.render( true, false );
	text_texture = gl::Texture( rendered );

    
}

void RecipeView::moveForward(){
    //stepState++;
    if(++stepState>1){
        stepState = 0;
        if(++curStep>=recipeModel.getNumSteps()){
            curStep = 0;
        }
    }
  //  img.load(recipeModel.getCookStep(curStep).img);
}

void RecipeView::update(){
    img.update();
    if(stepState==1){
        if(video.isDone()) moveForward();
    }
    
    char buffer [50];
    sprintf (buffer, "curStep: %i \n stepState: %i", curStep, stepState);
    TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( "Arial", 24 ) );
	layout.setColor( Color( 1, 1, 1 ) );
	layout.addLine( buffer);
	Surface8u rendered = layout.render( true, false );
    text_texture = gl::Texture( rendered );
    if(prevStep!=curStep){
        // moved from video to new start image
        // load both the image and the video for the new step
        img.load(recipeModel.getCookStep(curStep).img);
        console() << "Loaded a vid..." << endl;
        video = qtime::MovieGl( loadResource(recipeModel.getCookStep(curStep).video));
        prevStep = curStep;
    }
    if(prevStepState!=stepState){
        // moved from start image to video
        //
        
        if(stepState==1){
            video.fadeIn();
            img.fadeOut();
            console() << "playing a vid..." << endl;
   video.play();
        } else {
            img.fadeIn();
            video.fadeOut();
        }
     //   if(prevStepState==-1)  video.stop();
        prevStepState = stepState;
    }
    
}

void RecipeView::draw(Vec2f pos){
    gl::pushMatrices();
   
    gl::enableAlphaBlending();
     
    (stepState == 0) ? gl::color(1.0f,1.0f,1.0f,0.5f) : gl::color(0.0f,1.0f,1.0f,0.5f);
    
    gl::translate(pos);
    if(stepState==0){
    img.draw(CENTER,true);
    } else {
       // console() << "drawing a vid" << endl;
        gl::Texture tex = video.getTexture();
        try{
            if(tex) gl::draw(tex);
        } catch(...){ console() << "buggy" << endl; }
    }
    // gl::translate(20,20,0);
   // menu_img.draw(CENTER,true);
    gl::draw(text_texture);
    gl::popMatrices();
}