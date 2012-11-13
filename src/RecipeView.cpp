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

    console() << "error, this is deprecated" << endl;
    
}

int RecipeView::getKeyFunction(char _aChar){
    if(areaModel.back_btn.keymap==_aChar) return 0;
    if(areaModel.select_btn.keymap == _aChar) return 1;
    if(areaModel.fwd_btn.keymap == _aChar) return 2;
    
    return -1;
}
void RecipeView::setDebug(int _debugState){
    debugState = _debugState;
}

RecipeView::RecipeView(UserAreaModel _area, RecipeModel _recipe){
   timeOut = 60.0f;
    lastTouched = getElapsedSeconds();
    
    recipeModel = _recipe;
    areaModel = _area;
    // menu_img.load(_model.getMenuImage());
    debugState = 2;
    
    curStep = 0;
    stepState = 0;
    prevStepState = -1;
    prevStep = -1;
    
    pos = Vec2f(_area.x,_area.y);
    rotation = _area.r;
    
    align=TOP_LEFT;
    
    if(_area.name.compare("bottom-left")==0) align=BOTTOM_LEFT;
    if(_area.name.compare("bottom-right")==0) align=BOTTOM_RIGHT;
    if(_area.name.compare("top-left")==0){
     align=BOTTOM_RIGHT;
        console() << "aligning top left";
    }
    if(_area.name.compare("top-right")==0){
        align=BOTTOM_LEFT;
    console() << "aligning top right";
    }
    console() << "this recipemodel has this many steps: " << recipeModel.getNumSteps() << "." << endl;
    for(int i=0;i<recipeModel.getNumSteps();i++){
        console() << "wtf: " << recipeModel.getCookStep(i).img.at(0) << endl;
        gallerytools::Image anImage;
        anImage.load(recipeModel.getCookStep(i).img.at(recipeModel.curLanguage));
        anImage.hide();
        images.push_back(anImage);
        gallerytools::Video aVideo;
        console() << "loading video::: " << aVideo.load(recipeModel.getCookStep(i).video.at(recipeModel.curLanguage)) << endl;
        aVideo.hide();
        videos.push_back(aVideo);
    }
    back_btn.load(areaModel.back_btn.path);
    back_btn.moveTo(areaModel.back_btn.x,areaModel.back_btn.y,false);
    fwd_btn.load(areaModel.fwd_btn.path);
    fwd_btn.moveTo(areaModel.fwd_btn.x,areaModel.fwd_btn.y,false);
    select_btn.load(areaModel.select_btn.path);
    select_btn.moveTo(areaModel.select_btn.x,areaModel.select_btn.y,false);
    
    string normalFont( "Arial" );
    
	TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( normalFont, 24 ) );
	layout.setColor( Color( 1, 1, 1 ) );
	layout.addLine( "testing here");
	Surface8u rendered = layout.render( true, false );
	text_texture = gl::Texture( rendered );
    select_btn.setHalfHidden();
    back_btn.setHalfHidden();
    fwd_btn.setHalfHidden();
    
}
void RecipeView::next(){
    if(++stepState>1){
        stepState = 0;
        if(++curStep>=recipeModel.getNumSteps()){
            curStep = 0;
        }
    }
}

void RecipeView::reload(){
    images.clear();
    videos.clear();
    for(int i=0;i<recipeModel.getNumSteps();i++){
        console() << "wtf: " << recipeModel.getCookStep(i).img.at(recipeModel.curLanguage) << endl;
        gallerytools::Image anImage;
        anImage.load(recipeModel.getCookStep(i).img.at(recipeModel.curLanguage));
        anImage.hide();
        images.push_back(anImage);
        gallerytools::Video aVideo;
        console() << "loading video::: " << aVideo.load(recipeModel.getCookStep(i).video.at(recipeModel.curLanguage)) << endl;
        aVideo.hide();
        videos.push_back(aVideo);
    
    }
    
    if(stepState==0){
        images.at(curStep).show();
    } else {
        videos.at(curStep).show();
    }
}

void RecipeView::forwardRelease(){
    //stepState++;
    if(!(curStep==0 && stepState==0)){
        next();
        fwd_btn.boingScaleOut();
    } 
      //
    delayTimeOut();
    
}

void RecipeView::goStart(){
        // do this on a timeout, basically.
        curStep = 0;
        stepState = 0;
    delayTimeOut();

}

void RecipeView::backwardRelease(){
    //stepState++;
    if(!(curStep==0 && stepState==0)){
        if(--stepState<0){
            stepState = 1;
            if(--curStep<0){
                curStep = recipeModel.getNumSteps()-1;
            }
        }
        back_btn.boingScaleOut();
    } else {
        // okay, try to load all the new crap...
        if(recipeModel.getNumLanguages()>1){
            if(recipeModel.switchLanguage()>0){
                reload();
                back_btn.boingScaleOut();
            }
        }
    }
    
    delayTimeOut();
    //  img.load(recipeModel.getCookStep(curStep).img);
}
    
void RecipeView::selectRelease(){
    select_btn.boingScaleOut();
    if(stepState==0) next();
    
    delayTimeOut();
}

void RecipeView::forwardPress(){
// forward button press
    if(!(curStep==0 && stepState==0)) fwd_btn.boingScaleIn();
    
    delayTimeOut();
}

void RecipeView::backwardPress(){
    // backward button press
    if(!(curStep==0 && stepState==0)){
        back_btn.boingScaleIn();
    } else {
if(recipeModel.getNumLanguages()>1){
   // console() << "the recipe model is reporting " << recipeModel.getNumLanguages() << " languages." << endl;
    back_btn.boingScaleIn();
}
    }
    delayTimeOut();
}
void RecipeView::selectPress(){
    if(stepState==0) select_btn.boingScaleIn();
    delayTimeOut();
}

void RecipeView::delayTimeOut(){
    lastTouched = getElapsedSeconds();
}

void RecipeView::update(){
    
    
    //console() << ":::TIMED OUT:::" << endl;
    if((curStep==0 && stepState==0) || stepState==1){
        // it's already at the start, or if it's on a video...
        delayTimeOut();
    } else {
        double curTime = getElapsedSeconds();
        if((curTime-lastTouched)>timeOut){
            console() << "going to start: " << recipeModel.name << endl;
            goStart();
        }
    }
    
    
      for(int i=0;i<videos.size();i++){
        if(i!=curStep){
                      // videos.at(i).stop();
        }
    }
    if(stepState==1){
        if(videos.size()>curStep){
            videos.at(curStep).update();
            if(videos.at(curStep).isDone()) forwardRelease();
        }
    }
    
    char buffer [40];
    sprintf (buffer, "curStep: %i \n stepState: %i", curStep, stepState);
    TextLayout layout;
	layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
	layout.setFont( Font( "Arial", 18 ) );
	layout.setColor( Color( 1, 1, 1 ) );
    layout.addLine(recipeModel.name.c_str());
	layout.addLine( buffer);
	Surface8u rendered = layout.render( true, false );
    text_texture = gl::Texture( rendered );
    
    
    // this needs work here....
    // this is specifically to handle a goStart() situation...
    if(prevStepState==0 && stepState == 0 && prevStep!=curStep){
        console() << "THIS SHOULD BE FIRING on TIMEOUT >>> " << recipeModel.name << endl;
        if(images.size()>prevStep) images.at(prevStep).hide();
        if(images.size()>curStep) images.at(curStep).show();
        prevStep = curStep;
        
    } else {
        
    if(prevStep!=curStep){
        // moved from video to new start image
        // load both the image and the video for the new step
       if(prevStep>-1) videos.at(prevStep).stop();
        prevStep = curStep;
    }
    if(prevStepState!=stepState){
        // moved from start image to video
        if(stepState==1){
            if(videos.size()>curStep)    videos.at(curStep).show();
            if(images.size()>curStep)  images.at(curStep).hide();
            if(videos.size()>curStep)   videos.at(curStep).play();
        } else {
            if(images.size()>curStep) images.at(curStep).show();
            if(videos.size()>curStep)  videos.at(curStep).hide();
            if(videos.size()>curStep)  videos.at(curStep).stop();
        }
        prevStepState = stepState;
    }
        }
    
}

void RecipeView::draw(){
    gl::pushMatrices();
   
    gl::enableAlphaBlending();
     
    (stepState == 0) ? gl::color(1.0f,1.0f,1.0f,0.5f) : gl::color(0.0f,1.0f,1.0f,0.5f);
    
    gl::translate(pos);
    gl::rotate(rotation);
    if(stepState==0){
            gl::color(1.0f,1.0f,1.0f);
            if(images.size()>curStep) images.at(curStep).draw(align,(debugState!=0));
    } else {
            gl::color(1.0f,1.0f,1.0f);
            if(videos.size()>curStep)  videos.at(curStep).draw(align,(debugState!=0));
    }
    back_btn.draw(CENTER,(debugState!=0));
    select_btn.draw(CENTER,(debugState!=0));
    fwd_btn.draw(CENTER,(debugState!=0));
    
    if(debugState!=0){
    Rectf texRect = Rectf(0.0f,0.0f,text_texture.getWidth(),text_texture.getHeight());
    GalleryHelper::alignElement(align,Area(texRect));
    gl::draw(text_texture);
    }
    gl::popMatrices();
}