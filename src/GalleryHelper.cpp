//
//  GalleryHelper.cpp
//  CinderProject
//
//  Created by Cameron Browning on 8/2/12.
//
//

#include "GalleryHelper.h"

int GalleryHelper::alignElement(char _align, gl::Texture * _tex){
    
    Rectf texRect = Rectf(0.0f,0.0f,_tex->getWidth(),_tex->getHeight());
    return alignElement(_align,Area(texRect));
   
}

int GalleryHelper::alignElement(char _align,cinder::Area _bounds){
    float xOffset, yOffset;
    if(_bounds.getWidth()>1){
        switch(_align){
            case TOP_LEFT:
            case TOP_MIDDLE:
            case TOP_RIGHT:
                yOffset = 0;
                break;
            case MIDDLE_LEFT:
            case CENTER:
            case MIDDLE_RIGHT:
                yOffset = -1*_bounds.getHeight()/2;
                break;
            case BOTTOM_LEFT:
            case BOTTOM_MIDDLE:
            case BOTTOM_RIGHT:
                yOffset = -1*_bounds.getHeight();
                break;
        }
        switch(_align){
            case TOP_LEFT:
            case MIDDLE_LEFT:
            case BOTTOM_LEFT:
                xOffset = 0;
                break;
            case TOP_MIDDLE:
            case CENTER:
            case BOTTOM_MIDDLE:
                xOffset = -1*_bounds.getWidth()/2;
                break;
            case TOP_RIGHT:
            case MIDDLE_RIGHT:
            case BOTTOM_RIGHT:
                xOffset = -1*_bounds.getWidth();
                break;
        }
        
        
        gl::translate(xOffset,yOffset);
        return 0;
    } else {
        return -1;
    }
}