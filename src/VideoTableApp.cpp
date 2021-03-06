
#include "VideoTableApp.h"



void VideoTable::setup(){
    
    cTarget = new gallerytools::CursorTarget();
    
    model.setup("SETTINGS.plist","RECIPES.plist");
    
    if(model.useSensors){
        pConnector.useEvents(false);
        
    }
    
    setFullScreen(model.isFullScreen);
    if(model.isFullScreen) hideCursor();
    
    int numRecipes = model.recipes.size();
    
    for(int i=0;i<model.areas.size();i++){
        string thisRecipe_str = model.areas.at(i).recipe;
        UserAreaModel theUserAreaModel = model.areas.at(i);
        RecipeModel theRecipeModel = model.getRecipeModel(thisRecipe_str);
        recipeViews.push_back(RecipeView(theUserAreaModel, theRecipeModel));
    }
    
    controller.setup(&model,&recipeViews);
    
    console() << "there are " << numRecipes << " recipes.";
    
    background_tex = gl::Texture( loadImage( model.backgroundPath  ) );
    foreground_tex = gl::Texture( loadImage(  model.foregroundPath ) );
    
    if(model.useSensors){
    vector<int> uniqueSensorBoards;
    
    for(int i=0;i<model.sensors.size();i++){
        TouchSensorModel thisParticularSensor = model.sensors.at(i);
        int thisParticularInt = thisParticularSensor.board;
        bool isThisParticularIntUnique = true;
        for(int j=0;j<uniqueSensorBoards.size();j++){
            if(uniqueSensorBoards.at(j) == thisParticularInt){
                isThisParticularIntUnique = false;
            }
        }
        if(isThisParticularIntUnique){
            uniqueSensorBoards.push_back(thisParticularInt);
        }
    }
    for(int i=0;i<uniqueSensorBoards.size();i++){
        pConnector.connect(uniqueSensorBoards.at(i), model.sensorTimeOut);
    }
        pg.setup(&pConnector, &model.sensors);
    }
    
    
    
    
    
    mParams = params::InterfaceGl( "CardBox Functions", Vec2i( 225, 200 ) );
    mParams.addButton("select button", std::bind( &VideoTable::selectButtonHandler, this ));
    mParams.addButton("back button", std::bind( &VideoTable::backButtonHandler, this ));
    mParams.addButton("skip button", std::bind( &VideoTable::skipButtonHandler, this ));
    
    mParams.show();

}

void VideoTable::selectButtonHandler(){
    console() << "select button handler" << endl;
}
void VideoTable::backButtonHandler(){
    console() << "back button handler" << endl;
}
void VideoTable::skipButtonHandler(){
    console() << "skip button handler" << endl;
}

void VideoTable::parseXML()
{
    console() << "VideoTableApp::parseXML has been deprecated" << endl;
}

void VideoTable::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1920,1200 );
    
    // maybe lowering might smooth things out?
	settings->setFrameRate( 60.0f );
}
void VideoTable::keyUp(KeyEvent event){
    controller.handleKeyRelease(event.getChar());
}

void VideoTable::mouseDown( MouseEvent evt){
    if(controller.getDebugState()!=0) cTarget->push();
}

void VideoTable::keyDown( KeyEvent event ){
    controller.handleKeyPress(event.getChar());
}

void VideoTable::update(){
    
    if(model.useSensors){
        
        pConnector.updateKits();
        
        for(int i=0;i<model.sensors.size();i++){
            TouchSensorModel * tsm = & model.sensors.at(i);
            tsm->val = pConnector.getVal(tsm->board, tsm->sensor);
            if(abs(tsm->val-tsm->prev)>1){
                console() << tsm->keymap << " : " << tsm->val << ", " << tsm->prev << endl;
                if(tsm->val>tsm->prev && !tsm->isTouched){
                    console() << "TOUCHED!" << "...omg" << endl;
                    controller.handleKeyPress(tsm->keymap);
                    tsm->isTouched = true;
                } else if(tsm->isTouched){
                    console() << "RELEASED" << endl;
                    controller.handleKeyRelease(tsm->keymap);
                    tsm->isTouched = false;
                }
                tsm->prev = tsm->val;
            }
            if(controller.getDebugState()!=0 && model.useSensors) pg.update();
            
            
        }
    }
    for(int i=0;i<recipeViews.size();i++){
        recipeViews.at(i).update();
    }
    
}

void VideoTable::draw()
{
    
    
    gl::clear( Color( 0, 0, 0) );
    gl::enableAlphaBlending();
    gl::color(1.0f,1.0f,1.0f);
    gl::draw(background_tex,getWindowBounds());
    for(int i=0;i<recipeViews.size();i++){
        recipeViews.at(i).draw();
    }
    if(model.useFrontPlate)    gl::draw(foreground_tex,getWindowBounds());
    
    if(controller.getDebugState()!=0){
        
        char buffer [50];
        int n;
        n=sprintf (buffer, "%i, %i, %i", pConnector.getVal(148920, 0),pConnector.getVal(148920,2),pConnector.getVal(148920, 2));
        
        if(controller.getDebugState()!=0){
            cTarget->update(buffer);
            cTarget->update(getMousePos());
            cTarget->draw();
        }
        if(model.useSensors) pg.draw(Rectf(getWindowWidth()/3.0f,getWindowHeight()/3.0f,getWindowWidth()*2.0f/3.0f,getWindowHeight()*2.0f/3.0f));
        
        mParams.show();
             params::InterfaceGl::draw();
    } else {
        mParams.hide();
    }
    

}

CINDER_APP_BASIC( VideoTable, RendererGl(0) );
