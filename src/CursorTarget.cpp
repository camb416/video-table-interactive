//
//  CursorTarget.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/29/12.
//
//

#include "CursorTarget.h"



using namespace gallerytools;

CursorTarget::CursorTarget(){
    
    app = (AppBasic*)app::App::get();
    
string normalFont( "Arial" );
TextLayout layout;
layout.clear( ColorA( 0.5f, 0.5f, 0.5f, 0.5f ) );
layout.setFont( Font( normalFont, 24 ) );
layout.setColor( Color( 1, 1, 1 ) );
layout.addLine( "...");
Surface8u rendered = layout.render( true, false );
text_texture = gl::Texture( rendered );
  
}

void CursorTarget::push(){
   
    stringstream ss;
    ss << app->getMousePos().x << "," << app->getMousePos().y;
    poslist.push_back(ss.str());
}

void CursorTarget::update(Vec2i pos){
try{
     //  app= (AppBasic*)app::App::get();
    //    Vec2i pos = app->getMousePos();
    string normalFont( "Arial" );
    TextLayout layout;
    layout.clear( ColorA( 0.0f, 0.0f, 0.0f, 0.5f ) );
    layout.setFont( Font( normalFont, 24 ) );
    layout.setColor( Color( 1, 0.75f,0.75f ) );
    

    stringstream ss;//create a stringstream
        ss << pos.x << "," << pos.y;//add number to the stream
   //     return ss.str();//return a string with the contents of the stream
    
    layout.addLine( ss.str());
     layout.setColor( Color( 1, 1,1 ) );
    for(int i=0;i<poslist.size();i++){
        layout.addLine(poslist.at(i).c_str());
    }
    Surface8u rendered = layout.render( true, false );
    text_texture = gl::Texture( rendered );
} catch(Exception ex){
    console() << "caught an exception" << endl;
}
}

void CursorTarget::draw(){
    Vec2i pos = app->getMousePos();
    Vec2i windowCenter = app->getWindowCenter();
    char align;
    if(pos.x>windowCenter.x){
        if(pos.y>windowCenter.y){
            align=BOTTOM_RIGHT;
        } else {
            align=TOP_RIGHT;
        }
    } else {
        if(pos.y>windowCenter.y){
            align = BOTTOM_LEFT;
        } else {
            align = TOP_LEFT;
        }
    }
    gl::pushMatrices();
    GalleryHelper::alignElement(align,&text_texture);
    gl::draw(text_texture,pos);
    gl::popMatrices();
}