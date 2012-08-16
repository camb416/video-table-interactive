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
    
    
    console() << "this recipemodel has this many steps: " << recipeModel.getNumSteps() << "." << endl;
    for(int i=0;i<recipeModel.getNumSteps();i++){
        console() << "wtf: " << i << endl;
        gallerytools::Image anImage;
        anImage.load(recipeModel.getCookStep(i).img);
        anImage.hide();
        images.push_back(anImage);
        gallerytools::Video aVideo;
        aVideo.load(recipeModel.getCookStep(i).video);
        aVideo.hide();
        videos.push_back(aVideo);
    }
    
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
    //img.update();
    // for(int i=0;i<videos.size();i++){
      //  if(i!=curStep){
       //     console() << "stopping video " << i << endl;
     //       videos.at(i).stop();
       // }
   // }
    for(int i=0;i<videos.size();i++){
        if(i!=curStep){
                      // videos.at(i).stop();
        }
    }
    if(stepState==1){
       videos.at(curStep).update();
        if(videos.at(curStep).isDone()) moveForward();
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

      //  videos.at(curStep).stop();
     //   videos.at(curStep).hide();
       if(prevStep>-1) videos.at(prevStep).stop();
        prevStep = curStep;
        
      //  videos.at(curStep).show();
     //   videos.at(curStep).play();
        
    }
    if(prevStepState!=stepState){
        // moved from start image to video
        //
        
        if(stepState==1){
           // video.fadeIn();
            
            videos.at(curStep).show();
            images.at(curStep).hide();
            // img.fadeOut();
            videos.at(curStep).play();
        } else {
            console() << "// does this ever even happen?" << endl;
            //img.fadeIn();
            //video.fadeOut();
            images.at(curStep).show();
            videos.at(curStep).hide();
            videos.at(curStep).stop();
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
        //for(int i=0;i<images.size();i++){
        //    if(i==curStep && stepState==0){
        //        gl::color(1.0f,0.0f,0.0f);
        //    } else {
                gl::color(1.0f,1.0f,1.0f);
        //    }
            images.at(curStep).draw(TOP_LEFT,true);
         //   gl::translate(25.0f,25.0f,0.0f);
     //   }
    } else {
        // for(int i=0;i<videos.size();i++){
        //    if(i==curStep && stepState!=0){
        //        gl::color(1.0f,0.0f,0.0f);
        //    } else {
                gl::color(1.0f,1.0f,1.0f);
        //    }
            videos.at(curStep).draw(TOP_LEFT,true);
        //      gl::translate(25.0f,25.0f,0.0f);
      //  }
      
    }
    // gl::translate(20,20,0);
   // menu_img.draw(CENTER,true);
    gl::draw(text_texture);
    gl::popMatrices();
}