#include "ofApp.h"

//--------------------------------------------------------------
// All images is royalty free from www.pixabay.com

// TO DO:
//
// Get FFT values from song input using ofxMaxim
// Apply the FFT values to the rectLength in dayMode and to the circles in nightMode
// Set up the play button animation by looping the images
// Set up instructions in dayMode
// Write a music piece for the visualizer
// Switch state button
// rotate the circle of rectangles around it own axis when the switch state button is pressed
// Apply fade in and fade out from states
// Have a line that shows the length of the song
// choose your own song ( maybe )
// volume bar?
// mute button
//
//

void ofApp::setup(){
    
    sampleRate = 44100; // initializing the sampleRate
    bufferSize = 512; // initializing the bufferSize
    
    //fft.setup(1024, 512, 256);
    //oct.setup(44100, 1024, 10);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    sound.load(ofToDataPath("sound.wav")); // loading audio track
    
    stateSwitch = false;
    image.load("blog.jpg"); // loading the background image
    image2.load("2.jpg");
    mute.load("mute.png");
    stateButton.load("state.png"); // loading the stateSwitch button
    index = 0; // setting the index to 0 which will be the first image in the loop
    
   // for(int i = 0; playButton.size(); i ++) { // looping through the playButton vector
        
        ofImage img;
    
        img.loadImage("img1.png"); // loading the images
    
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
        
        part[i]->update(); // updating the particles
    }
}

//--------------------------------------------------------------

void ofApp::draw(){
    
    

    //std:: cout << mouseY << std::endl;
    
    switch (state) {
            
/*------------------------ Menu Visualizer -----------------------------------*/
            
        case 0: 
            
            image.draw(0,0); // drawing the background image
            mute.draw(260, 455); // mute button
             ofDrawBitmapString("Music Visualizer", 540, 40); // draw text
             ofDrawBitmapString("Created by johan Gelinder", 510, 60); // draw text
            
            ofPushMatrix();
            f = A*sin(e * ofGetElapsedTimeMillis() + 4); // will move the arrow up and down
            ofTranslate(0, 0+f);
            stateButton.draw(ofGetWidth()/2-25,635); // drawing the state swtich button
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(600,0);
        
            if(stateSwitch == true) { // start rotating when the user pressed the button
                
                rotY += 1 * rate;
                ofRotateY(rotY);
                lLine -= 0.85;
                rLine += 0.85;
            }
            
            if(lLine <= 100){
                lLine = 100;
                state = 1;
                stateSwitch = false;
            }
            if(rLine >= 1100){
                rLine = 1100;
            }
            
            if(state == 1){
                lLine = 400;
                rLine = 800;
            }
            
            ofTranslate(-600,0);
            
            circle->display(); // displaying the cirlce of rectangles
            circle->update(); // updating the cirlce of rectangles
            
            ofPopMatrix();
            
            ofLine(0,ofGetHeight()/2,lLine, ofGetHeight()/2); // left line
            ofLine(rLine,ofGetHeight()/2,ofGetWidth(), ofGetHeight()/2); // right line
            ofLine(100, 330, 100, 370 );
            ofDrawBitmapString("Time", 60, 345); // draw text
            ofDrawBitmapString(ofGetElapsedTimef(), 35, 365); // draw text
            ofLine(1100, 330, 1100, 370 );
            ofDrawBitmapString("Song", 1110, 345); // draw text
             ofDrawBitmapString("Name", 1110, 365); // draw text
            
            ofDrawRectRounded(1110,455, 0, 30, 8, 4);
            ofDrawRectRounded(1110, 475, 0, 30, 8, 4);
            
            //slider
            ofLine(150, 400, 150, 550);
            ofDrawRectRounded(135,475, 30, 10,4);
            ofDrawBitmapString("Volume", 125, 570);
            
            //instructions
            
            ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 400); // draw text
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 420);
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 440);
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 460);
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 480);
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 500);
             ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 520);
            ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 540);
            ofDrawBitmapString("kldkealjfkaekfjaekddfddw", 850, 560);
            //slider
            ofLine(1060, 400, 1060, 550);
            ofDrawRectRounded(1055,465, 10, 10,2);
            
            
            playButton[index].draw(ofGetWidth()/2-20, 325); // drawing the play button
            
            break;
            
/*------------------------ Particle Visualizer -----------------------------------*/
            
            
        case 1:
            image2.draw(0,0); // call black background
            
            for(int i = 0; i < Nums; i ++) { // looping through all the particles
                
                part[i]->display(); // displaying the particles
            }
            
            // draw lines between near points
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
    
    if(play == true){
        
    for (int i = 0; i < bufferSize; i++){
        
        sample = sound.play(); // play the sample
        
        //if (fft.process(wave)) {
       //     oct.calculate(fft.magnitudes);
       // }
        
        output[i*nChannels    ] = sample; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = sample;
        }
    }
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    if(key == 'a') {
        
        state = 1; // switch state to nightMode
    }
    
    if(key == 's') {
        
        state = 0; // switch back to dayMode
    }
    
    if(key == 'p'){ // press p to play the music
        
        play = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(mouseX >= 565 && mouseX <= 635 && mouseY >= 630 && mouseY <= 665 ) {
       
       //state = 1;
        stateSwitch = !stateSwitch;
        
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
