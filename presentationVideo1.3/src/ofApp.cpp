#include "ofApp.h"
//#include "iostream"

//TO-DO LIST:
//
//Figure out the front-end. Drag and Drop images?
//Can you drag a folder of images onto the screen, and generate the directory from that instead?
//Think about accessibility

//move mouse-move functionality to the newscaster view
//lock preso in place after moving the newscaster view.


//--------------------------------------------------------------
void ofApp::videoBehind(){
    
//STEP: Pull the video
    // draw the raw video frame
    vidGrabber.draw(camWidth,0,-camWidth, camHeight);
    
    
//STEP: Display the images on top of the video

    // we need some images if not return
    if((int)images.size() <= 0) {
        ofSetColor(255);
        ofDrawBitmapString("Drag and drop images on top of this window.", 250, ofGetHeight()/2);
        return;
    }
    
    
    // draw where we are in the sequence
    float x = 0;
    images[slideCount].draw(presMargin,presMargin,presFrameWidth, presFrameHeight);

}

//--------------------------------------------------------------
void ofApp::videoInFront(){
    
    //STEP: Display the behind the video

    // we need some images if not return
    if((int)images.size() <= 0) {
        ofSetColor(255);
        ofDrawBitmapString("No Images...", 150, ofGetHeight()/2);
        return;
    }
    
    // draw where we are in the sequence
    float x = 0;
    images[slideCount].draw(presMargin,presMargin,presFrameWidth, presFrameHeight);
    
    //STEP: Pull the video
        // draw the raw video frame
    
    if (mouseControlOn >= 0){
    vidGrabber.draw((camWidth/4)+20,camHeight-(camHeight/4)-20,camWidth/-4, camHeight/4);
    }else{
        vidGrabber.draw(ofGetMouseX(),ofGetMouseY(),camWidth/-4, camHeight/4);
            }
    
}

//--------------------------------------------------------------
void ofApp::folderImageLoader(){
//STEP: image loader

ofDrawBitmapString("Drag and drop slides on top of this window. Use up/down arrow keys to rotate through presentation modes. Use left/right arrow keys to flip through slides.", 150, ofGetHeight()/2);
    
// read the directory for the images
// we know that they are named in seq
ofDirectory dir;


float nFiles = dir.listDir("pres");
    // get total number of slides
    totalSlides =  dir.size();
    slideCount = 0;
    
    //sort directory by filename
    dir.sort();
    
    
if(nFiles) {

    for(size_t i=0; i<dir.size(); i++) {

        // add the image to the vector
        string filePath = dir.getPath(i);
        images.push_back(ofImage());
        images.back().load(filePath);

    }
}

else ofLog(OF_LOG_WARNING) << "Could not find folder";

}

//--------------------------------------------------------------
void ofApp::setup(){
    
    
//    ofBackground(0,0,0);
    mouseControlOn = 1;
    dragTruth == false;
    tabVidOn == true;

    // set size and margin here
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    presMargin = 20;
    
    // set sizes for presentation frame here
    presFrameWidth = camWidth/2.5;
    presFrameHeight = camHeight/2.5;
    
    // set the presSizeCount to control tab between sizes
    presSizeCount = 0;
    
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    ofEnableAlphaBlending();

    folderImageLoader();
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    //determine what presSizeCount changes
    if (presSizeCount == 0){
        presFrameWidth = camWidth/2.5;
        presFrameHeight = camHeight/2.5;
        presMargin = 20;
    }
    
    if (presSizeCount == 1){
        presFrameWidth = ofGetWidth();
        presFrameHeight = ofGetHeight();
        presMargin = 0;
    }
    
    if (presSizeCount == -1){
        presFrameWidth = 0;
        presFrameHeight = 0;
        presMargin = 0;
    }
    
    //SUPER FUTURE CHALLENGE: have the preso deck be repositionable using your fingers from behind the video. AR style.
    
    
    if (presSizeCount == 3){
        presFrameWidth = ofGetWidth();
        presFrameHeight = ofGetHeight();
        presMargin = 0;
    }
    
    if (presSizeCount == 4){
        presFrameWidth = ofGetWidth();
        presFrameHeight = ofGetHeight();
        presMargin = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //STEP: Pull the slideWidth and Height
    for(int i=0; i < slideCount; i++) {
        slideWidth = images[i].getWidth();
        slideHeight = images[i].getHeight();
        
        std::cout  <<  "slideWidth: "  << slideWidth << endl;
        std::cout  <<  "slideHeight: "  << slideHeight << endl;
        }
    
    
    if (presSizeCount == 1){
        videoInFront();
    }else{
        videoBehind();
    }
    

}
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    if (key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

//    //Cycle through preso size / using up and down arrows
//    if (key == OF_KEY_DOWN){
//        presSizeCount = presSizeCount + 1;
//
//        //VIDEO IN FRONT FUNCTIONALITY IS ACCESSIBLE BY CHANGING THE 2 HERE TO 3
//        if (presSizeCount > 3) {
//            presSizeCount = 0;}
//    }
//
//    if (key == OF_KEY_UP){
//        presSizeCount = presSizeCount-1;
//
//        if (presSizeCount < 0){
//            presSizeCount = 2;}
//
//        }
    
    //Cycle through preso size / using up and down arrows
    if (key == OF_KEY_DOWN){
        presSizeCount = presSizeCount + 1;
       
        if (presSizeCount > 1) {
            presSizeCount = 0;}
    }
    
    if (key == OF_KEY_UP){
        presSizeCount = presSizeCount-1;
        
        if (presSizeCount < -1){
            presSizeCount = 0;}
    
        }
    
    if (key == OF_KEY_TAB){
        
        tabVidOn = !tabVidOn;
        
        if (tabVidOn == true){
            presSizeCount = 3;
        }else{
            presSizeCount = 1;
        }
        
        cout << "tabVidOn:" << tabVidOn << endl;
        
    }
            
    
    //--------------------------------------------------------------


    //Cycle through the slides using Left/Right
    if (key == OF_KEY_RIGHT){
        slideCount = slideCount + 1;
        if (slideCount == totalSlides){
            slideCount = 0;
        }
    }
    
    if (key == OF_KEY_LEFT){
        slideCount = slideCount - 1;
        if (slideCount == -1){
            slideCount = 0;
        }
    }
    
    //--------------------------------------------------------------

    if (key == 'm'){
        mouseControlOn = mouseControlOn * -1;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if( dragInfo.files.size() > 0 ){
        
        cout  <<  "images.size before clearing:" << images.size()  <<  endl;
        
        //First clear images of all info
        images.clear();
        
        cout  <<  "images.size after clearing:" << images.size()  <<  endl;

        images.assign(dragInfo.files.size(), ofImage() );
        for(unsigned int k = 0; k < dragInfo.files.size(); k++){
            images[k].load(dragInfo.files[k]);
            
        }
        
        totalSlides =  images.size();
        slideCount = 0;
        
        dragTruth = true;
        std::cout  <<  "after dragging something, dragTruth is "  << dragTruth <<  endl;
        
        cout  <<  "images.size after re-adding:" << images.size()  <<  endl;

        
    }
}
