#pragma once

#include "ofMain.h"
#include "circleClass.h"
#include "particleClass.h"
#include "ofxMaxim.h"


#define Nums 200 // number of particles

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
   
        ofImage image; // initializing the background image
        ofImage image2,mute;
        vector<ofImage> playButton;
        ofImage stateButton;
        int index;
        bool play = false;
        int state = 0;
        float rotY = PI / 4;
        float rate = 0.5;
        bool stateSwitch;
        float f;
        float A = 5;
        float e = 0.005;
        float rLine = 800;
        float lLine = 400;
    
        int circleRadius = 100;
        int numRects = 100;
        int rectLength = 40;
        float rectWidth = 2;
    
        float x = ofGetWidth()/2;
        float y = ofGetHeight()/2;
    
        circleClass *circle;
    
        Particles *part[Nums]; // creating a pointer ( a refrence in memory) for each object
    
        void audioOut(float * output, int bufferSize, int nChannels);
   // void audioIn(float * input, int bufferSize, int nChannels);
    
    
        int bufferSize;
        int sampleRate;
        ofxMaxiMix myMix;
        maxiSample sound;
        double sample;
        double outputs[2];
   // ofxMaxiFFT fft;
   // ofxMaxiFFTOctaveAnalyzer oct
    
   // vector <float> lAudio;
   // vector <float> rAudio;

    
    

		
};