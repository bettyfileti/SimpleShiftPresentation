#pragma once

#include "ofMain.h"

// This example is  based on the Processing "ASCII Video" example by Ben Fry
// and it is designed to demonstrate how to re-interpret live video as text
// to make it look like some good old ASCII art!
//
// For more information regarding this example take a look at the README.md.

class ofApp : public ofBaseApp{
    
    public:
        
        void setup();
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    //Functions
    void videoInFront();
    void videoBehind();
    void folderImageLoader();
        
        ofVideoGrabber vidGrabber;
        int camWidth;
        int camHeight;
    
    //variables for presentation display
    float presFrameWidth;
    float presFrameHeight;
    int presSizeCount;
    int presMargin;
    bool tabVidOn;
    
//    //variables for image load
    int   appFPS;
    float sequenceFPS;
    bool  bFrameIndependent;
    vector <ofImage> images;
    float totalSlides;
    int slideCount;
    float slideWidth;
    float slideHeight;
    
    //variables for dragged image load
    bool dragTruth;
    vector <ofImage> draggedImages;
    
    //variable for toggle between mouse position
    int mouseControlOn;
        
};
