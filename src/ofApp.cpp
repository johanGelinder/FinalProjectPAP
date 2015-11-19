#include "ofApp.h"

//--------------------------------------------------------------
// Created by Johan Gelinder
// All images is royalty free from www.pixabay.com

// TO DO:
//
// Apply the FFT values to the rectLength in state 0 and to the particles in state 1
// Make the particles move in 3D space
// Set up the play button animation by looping the images
// Set up instructions
// Write a music piece for the visualizer
// Apply fade in and fade out from states
// ( choose your own song )
// Load new fonts
// Make sure that the sliders work
// See if I can add a glow filter on the particles in state 1
//

void ofApp::setup(){
    
    sampleRate = 44100; // initializing the sampleRate
    bufferSize = 512; // initializing the bufferSize
    
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 10);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    sound.load(ofToDataPath("sound.wav")); // loading audio track
    
    ts = new maxiTimestretch<grainPlayerWin>(&sound);
   
    stretches.push_back(ts);
    
    speed = 1;
    grainLength = 0.05;
    
    stateSwitch = false;
    image.load("blog.jpg"); // loading the background image
    image2.load("2.jpg");
    mute.load("mute.png");
    stateButton.load("state.png"); // loading the stateSwitch button
    index = 0; // setting the index to 0 which will be the first image in the loop
    
   // for(int i = 0; playButton.size(); i ++) { // looping through the playButton vector
        
        ofImage img;
    
        img.loadImage("img1.png"); // loading the images
        grand.loadImage("grand.png"); // grandular sythesis button
    
        playButton.push_back(img); // pushing the images into the vector
    
    //}
    
    //----------- Creating the circle of rectangles ------------
 

        circle = new circleClass(x, y, circleRadius, numRects, rectWidth, rectLength); // creating the circle object
    
    
    //------------------ Creating Particles --------------------
    
    
    for(int i = 0; i < Nums; i ++) { // looping through all the particles
        
        // create the particles randomly across the canvas and with a random size diamter of the particles
        part[i] = new Particles(ofRandom(500, 700), ofRandom(250,450), ofRandom(1,6));
    }
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------

void ofApp::update(){
    
    for(int i = 0; i < Nums; i ++) { // looping through all the particles
       
            part[i]->update(speed); // updating the spedd the paricles by using the speed of the sample
        
     for(int j = 0; j < *oct.averages; j++) {
         
         part[i]->updatePoints(j); // updating the points using the fft from the audio track
        }
     }
}

//--------------------------------------------------------------

void ofApp::draw(){
    
   std:: cout << mouseX << std::endl;
    
    
    
    if(synth == false){ // if synth is equal to false then the values goes back to normal
        
        speed = 1;
        grainLength = 0.05;
    }
    
/*------------------------ Menu Visualizer -----------------------------------*/
    
     switch (state) {
            
        case 0:
             
             image.draw(0,0); // drawing the background image
             
             mute.draw(260, 500); // mute button
             grand.draw(150,500); // grandular sythesis button
             
             if(play == true) { // if the play button has been pressed
                 
             glPushMatrix();
             ofTranslate(150,175); // translate the array of rectangles to this position
             
             for(int i = 0; i < 30; i++) { // making 30 rectangles
            
                 ofPushStyle();
                 ofSetColor(255); // white colour
                 ofRect(i * 5, 0, 2, -oct.averages[i]); // drawing rectangles and having the fft values from the song change the height of the rectangles
                 ofPopStyle();
             }
             glPopMatrix();
                 
             }
             
             if(lLine <= 100){ // if lLine is less or equal to 100
                 
                 state = 1; // switch states
                 stateSwitch = false; // setting the stateSwitch boolean back to false
                 
             }
             
             if(state == 1){ // if the state is changed then set the values back
                 
                 // original position
                 lLine = 400;
                 rLine = 800;
             }
            
            ofPushMatrix();
             
            f = A*sin(e * ofGetElapsedTimeMillis() + 4); // will move the arrow up and down
            ofTranslate(0, 0+f); // adding f to y will make it move up and down using sin()
            stateButton.draw(ofGetWidth()/2-25,635); // drawing the state swtich button
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(600,0); // translate x to middle of the screen
        
            if(stateSwitch == true) { // start rotating when the user pressed the button
                
                rotY += 1 * rate; // adding 1* rate to rotY so the rotation is smooth
                ofRotateY(rotY); // call the rotation on the cirlce of rectangles
                lLine -= 0.85; // decreasing lLine so that it moves left
                rLine += 0.85; // increasing rLine so that it moves right
            }
    
            ofTranslate(-600,0); // translate again but now - the middle of the screen so the rotation happens around it's own axis
            
            circle->display(); // displaying the cirlce of rectangles
             
             for(int i = 0; i < *oct.averages; i++) {

            circle->update(i); // updating the cirlce of rectangles
                
             }
            
            ofPopMatrix();
            
            ofLine(0,ofGetHeight()/2,lLine, ofGetHeight()/2); // left line
            ofLine(rLine,ofGetHeight()/2,ofGetWidth(), ofGetHeight()/2); // right line
            ofLine(100, 330, 100, 370 ); // vertical left line
            ofDrawBitmapString("Time", 60, 345);
            ofDrawBitmapString(ofGetElapsedTimef(), 35, 365);
            ofLine(1100, 330, 1100, 370 ); // vertical right line
            ofDrawBitmapString("Song", 1110, 345);
            ofDrawBitmapString("Name", 1110, 365);

            // name = ofToDataPath("sound.wav");
            //instructions
            ofDrawBitmapString("To switch state of the", 850, 460);
            ofDrawBitmapString("visualizer, press the", 850, 480);
            ofDrawBitmapString("arrow button at the bottom", 850, 500);
            ofDrawBitmapString("of the screen. To manipulate", 850, 520);
            ofDrawBitmapString("the audio track, click on", 850, 540);
            ofDrawBitmapString("the button at the far left", 850, 560);
            ofDrawBitmapString("corner and then use the", 850, 580);
            ofDrawBitmapString("mouse to activate the", 850, 600);
            ofDrawBitmapString("grandular synthesis", 850, 620);

            
            playButton[index].draw(ofGetWidth()/2-20, 325); // drawing the play button
             
             if( stateSwitch == true) {
                 alpha ++;
                 ofPushStyle();
                 ofSetColor(0, alpha);
                 ofRect(0, 0, ofGetWidth(),ofGetHeight());
                 ofPopStyle();
                 
             }
             
            break;
            
/*------------------------ Particle Visualizer -----------------------------------*/
            
            
        case 1:

            image2.draw(0,0); // draw background image
             
             mute.draw(160, 600); // mute button
             grand.draw(50,600); // grandular sythesis button

             
             alpha2 --;
             ofPushStyle();
             ofSetColor(0, alpha2);
             ofRect(0,0,ofGetWidth(),ofGetHeight());
             ofPopStyle();
             
             if(alpha2 <= 0) {
                 
                 alpha2 = 0;
             }
             
             ofPushMatrix();
             f = A*sin(e * ofGetElapsedTimeMillis() + 4); // will move the arrow up and down
             ofTranslate(0, 0+f); // adding f to y will make it move up and down using sin()
             stateButton.draw(ofGetWidth()/2-25,635); // drawing the state swtich button
             ofPopMatrix();
            
            for(int i = 0; i < Nums; i ++) { // looping through all the particles
                
                part[i]->display(); // displaying the particles
            }
            
            ofPushStyle();
            ofSetColor(255, 70);
            float dist = 60; // Threshold parameter of distance
            
            for (int i = 0; i < Nums; i ++) { // nested for loop
                for (int j = i +1; j < Nums; j ++) {
                    
                    //calculating the distance between two points with ofDist and if the distance between these two points is less than 60 then draw a line between these points
                    if ( ofDist( part[i]->x, part[i]->y, part[j]->x, part[j]->y ) < dist ) {
                        
                        ofLine(part[i]->x,part[i]->y, part[j]->x, part[j]->y );
                        // because I am using pointers you call part[i]->x instead of part[i].x
                    }
                }
            }
            ofPopStyle();
            
            break;
    }
    
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    if(play == true){ // if the play button has been clicked
//        
    for (int i = 0; i < bufferSize; i++){
//        
//        sample = sound.play(); // play the sample
//        
//        if (fft.process(sample)) {
//            oct.calculate(fft.magnitudes);
//        }
//        
//        output[i*nChannels    ] = sample;
//        output[i*nChannels + 1] = sample;
//        
//        }
//    }
        //sample = stretches[0]->mute();
    sample = stretches[0]->play(speed, grainLength, 2, 0);
    // wave = stretches[current]->play(speed, 0.1, 4, 0);
    //		wave = stretches[current]->play2(pos, 0.1, 4);
    if (fft.process(sample)) {
        oct.calculate(fft.magnitudes);
    }
    
    //play result
   // mymix.stereo(wave, outputs, 0.5);
    output[i*nChannels    ] = sample;
    output[i*nChannels + 1] = sample;
        }
    }
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    if(key == 'a') {
        
        state = 1; // manually switch states
    }
    
    if(key == 's') {
        
        state = 0; // manually switch states
    }
//    if( key == ' ') {
//        
//        synth = !synth;
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    if(synth == true) {
    
    speed = ((double ) x / ofGetWidth() * 4.0) - 2.0;
    grainLength = ((double) y / ofGetHeight() * 0.1) + 0.001;
   // pos = ((double) x / ofGetWidth() * 2.0);

    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(mouseX >= 565 && mouseX <= 635 && mouseY >= 650 && mouseY <= 680 ) {
    
        stateSwitch = !stateSwitch; // click in the arrow button to start the animation and then switch state
        
        if(state == 1 ) {
            alpha = 0;
            state = 0;
            stateSwitch = false;
        }
   }
    
    if( state == 0) { // You have to be in the fist state to be able to press the play button
        alpha2 = 255;
    
      if(mouseX >= 585 && mouseX <= 625 && mouseY >= 335 && mouseY <= 365 ) {
          
          play = !play; // play the music of you click on the play button
      }
        
        if(mouseX >= 150 && mouseX <= 200 && mouseY >= 500 && mouseY <= 550 ) {
            
            synth = !synth;
        }
    }
    
    if( state == 1) {
           if(mouseX >= 50 && mouseX <= 100 && mouseY >= 600 && mouseY <= 650 ) {
    
    synth = !synth;
           }
   }
    
    
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

}
