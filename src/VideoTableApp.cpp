
#include "VideoTableApp.h"



void VideoTable::setup()
{
    //debugState = DEVELOPMENT;
    
    // TODO ISSUE #22


    
    cTarget = new gallerytools::CursorTarget();
    
    controller.setup(&model,&recipeViews);
    
    model.setup("SETTINGS.plist","RECIPES.plist");
    
    if(model.useSensors){
        console() << "this shouldnt be happening" << endl;
        pConnector.useEvents(false);
        pConnector.connect(148920);
    }
        
    // implement fullscreen test here...
    setFullScreen(model.isFullScreen);
    if(model.isFullScreen) hideCursor();
    
    // doubt these still work
    // model.pretendSetup();
    // model.trace();
    
    
     
    int numRecipes = model.recipes.size();
  
  //  myRecipeView = new RecipeView(model.recipes.at(0));
    
    for(int i=0;i<model.areas.size();i++){
        string thisRecipe_str = model.areas.at(i).recipe;
        UserAreaModel theUserAreaModel = model.areas.at(i);
        RecipeModel theRecipeModel = model.getRecipeModel(thisRecipe_str);
        recipeViews.push_back(RecipeView(theUserAreaModel, theRecipeModel));
    }
   /*
    for(int i=0;i<model.recipes.size();i++){
        recipeViews.push_back(RecipeView(model.recipes.at(i)));
    }
    */
    console() << "there are " << numRecipes << " recipes.";
    
    /*
    model.setup("APP.plist","RECIPES.plist");
    
    parseXML();
    
    
    
    
    
    
    if(useTouch){
        pConnector.useEvents(false);
        pConnector.connect(148986);
    }
    
    // get these from the XML
    setWindowSize(defaultWindowSize.x, defaultWindowSize.y);
//    width = 1920.0;
 //   height = 1200.0;
     */
    background_tex = gl::Texture( loadImage( model.backgroundPath  ) );
    foreground_tex = gl::Texture( loadImage(  model.foregroundPath ) );
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

void VideoTable::keyDown( KeyEvent event )
{
    /*
    for(int i=0;i<recipeViews.size();i++){
       recipeViews.at(i).moveForward();
    }
     */
    controller.handleKeyPress(event.getChar());
    
    

    }

void VideoTable::update()
{
    
    for(int i=0;i<recipeViews.size();i++){
        recipeViews.at(i).update();
    }
   
  
    if(model.useSensors){
        
    pConnector.updateKits();
    
   // console() << pConnector.getBool(148920, 0) << pConnector.getBool(148920, 1) << pConnector.getBool(148920, 2) << endl;
    
    for(int i=0;i<model.sensors.size();i++){
      //  if(i>0) console() << ", " ;
      //  console() << pConnector.getBool(model.sensors.at(i).board, model.sensors.at(i).sensor);
        TouchSensorModel * tsm = & model.sensors.at(i);
        tsm->val = pConnector.getVal(tsm->board, tsm->sensor);
        if(abs(tsm->val-tsm->prev)>1){
            console() << tsm->keymap << " : " << tsm->val << ", " << tsm->prev << endl;
            if(tsm->val>tsm->prev){
                console() << "TOUCHED!" << "...omg" << endl;
                controller.handleKeyPress(tsm->keymap);
            } else {
                console() << "RELEASED" << endl;
                controller.handleKeyRelease(tsm->keymap);
            }
            tsm->prev = tsm->val;
        }
    }
        }
    // console() << endl;

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

    // while this should be in update, Cinder likes to throw
    // an exception on application quit
    // ick...
    if(controller.getDebugState()!=0){
        
        char buffer [50];
        int n, a=5, b=3;
        n=sprintf (buffer, "%i, %i, %i", pConnector.getVal(148920, 0),pConnector.getVal(148920,2),pConnector.getVal(148920, 2));
        //printf ("[%s] is a string %d chars long\n",buffer,n);
        
    //    string myString =pConnector.getBool(148920, 0) + pConnector.getBool(148920, 1) +
      //  pConnector.getBool(148920, 2);
        
        
        cTarget->update(buffer);
        cTarget->update(getMousePos());
        cTarget->draw();
    }//
    //
    
    
}

CINDER_APP_BASIC( VideoTable, RendererGl(0) );
