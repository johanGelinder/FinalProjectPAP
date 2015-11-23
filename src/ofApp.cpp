#include "ofApp.h"

//--------------------------------------------------------------
// Created by Johan Gelinder
// All images is royalty free from www.pixabay.com

// TO DO:
//
// Apply the FFT values to the rectLength in state 0 and to the particles in state 1
// Make the particles move in 3D space
// Set up the play button animation by looping the images
// Write a music piece for the visualizer
// See if I can add a glow filter on the particles in state 1
//

void ofApp::setup(){
    
    sampleRate = 44100; // initializing the sampleRate
    bufferSize = 512; // initializing the bufferSize
    volume = 1;
    
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 10);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    sound.load(ofToDataPath("sound.wav")); // loading audio track
  //  sound2.oad(ofToDataPath("sound2.wav"));
    
    
    ts = new maxiTimestretch<grainPlayerWin>(&sound);
   // ts2 new maxiTimestretch<grainPlayerWin>(&sound2);

   
    stretches.push_back(ts);
    //stretches.push_back(ts2);
    
    speed = 1;
    grainLength = 0.05;
    
    stateSwitch = false;
    image.load("blog.jpg"); // loading the background image
    image2.load("2.jpg");
    mute.load("mute.png");
    mute2.load("mute2.png");
    stateButton.load("state.png"); // loading the stateSwitch button
    change.load("change.png");
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
    
    if(vol == true){
        volume = 1;
        
    }else{
        volume = 0;
    }
}

//--------------------------------------------------------------

void ofApp::draw(){
    
   std:: cout << mouseY << std::endl;
    // std:: cout << fade << std::endl;
    
    if(synth == false){ // if synth is equal to false then the values goes back to normal
        
        speed = 1;
        grainLength = 0.05;
    }
    
/*------------------------ Menu Visualizer -----------------------------------*/
    
     switch (state) {
            
        case 0:
             
             image.draw(0,0); // drawing the background image
             grand.draw(145,500); // grandular sythesis button
             if(vol == true) {
             mute.draw(225, 500); // mute button
             }else{
                 mute2.draw(225,500);
             }
             change.draw(305,500);
             
             if( synth == true) {
                 ofDrawRectRounded(145,560, 50,10,5);
             }
             
             if(play == true) { // if the play button has been pressed
                 
             glPushMatrix();
             ofTranslate(145,175); // translate the array of rectangles to this position
             
             for(int i = 0; i < 42; i++) { // making 30 rectangles
            
                 ofPushStyle();
                 ofSetColor(255); // white colour
                 
                 ofRect(i * 5, 0, 2, -oct.averages[i]); // drawing rectangles and having the fft values from the song change the height of the rectangles
                 ofPopStyle();
             }
             glPopMatrix();
                 
             }
             
             if(lLine <= 150){ // if lLine is less or equal to 100
                 
                 state = 1; // switch states
                 rotY = PI / 4;
                 
             }
             
             if(state == 1){ // if the state is changed then set the values back
                 
                 // original position
                 lLine = 400;
                 rLine = 800;
                 stateSwitch = false; // setting the stateSwitch boolean back to false
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

            
            playButton[0].draw(ofGetWidth()/2-20, 325); // drawing the play button
             
             if( fade == true) {
                 
                 alpha ++;
                 ofPushStyle();
                 ofSetColor(0, alpha);
                 ofRect(0, 0, ofGetWidth(),ofGetHeight());
                 ofPopStyle();
                 
             }
             
             if(alpha == 296){
                 fade = false;
             }
             
            break;
            
/*------------------------ Particle Visualizer -----------------------------------*/
            
            
        case 1:

            image2.draw(0,0); // draw background image
             
            grand.draw(50,600); // grandular sythesis button
            mute.draw(130, 600); // mute button
             change.draw(210,600);
            playButton[0].draw(1100, 600); // drawing the play buttonchange.draw(210,600);
             

             if(synth == true) {
                 ofDrawRectRounded(50,660, 50,10,5);
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
             
             alpha2 --; // fading in by decreaing the rectangle alpha value
             ofPushStyle();
             ofSetColor(0, alpha2); // back colour with changing alpha
             ofRect(0,0,ofGetWidth(),ofGetHeight()); // drawing a rectangle of the whole screen
             ofPopStyle();
             
             if(alpha2 <= 0) { // when aplha2 is fully transparant then is will stay that way until the state switches again
                 
                 alpha2 = 0;
             }
             
             if(state == 0){
                 alpha2 == 255; // if the state switches back then set alpha2 back to it's original position
             }
            break;
    }
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    if(play == true){ // if the play button has been clicked
        
    for (int i = 0; i < bufferSize; i++){ // looping through the bufferSize

        //sample = stretches[0]->mute();
    sample = stretches[index]->play(speed, grainLength, 2, 0);
 
    if (fft.process(sample)) {
        oct.calculate(fft.magnitudes);
    }
    
    //play result
   // mymix.stereo(wave, outputs, 0.5);
    output[i*nChannels    ] = sample * volume;
    output[i*nChannels + 1] = sample * volume;
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
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    if(synth == true) {
    
    speed = ((double ) x / ofGetWidth() * 4.0) - 2.0;
    grainLength = ((double) y / ofGetHeight() * 0.1) + 0.001;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(mouseX >= 565 && mouseX <= 635 && mouseY >= 650 && mouseY <= 680 ) {
    
        stateSwitch = !stateSwitch; // click in the arrow button to start the animation and then switch state
        if(state == 0) {
            fade = !fade;
            clickedOn = true;
            alpha = 0;
            rotY = PI /4;
            lLine = 400;
            rLine = 800;
            
        }
        
        if(state == 1 ) {
            alpha = 0;
            state = 0;
            stateSwitch = false;
            clickedOn = false;
            
        }
   }
    
    if( state == 0) { // You have to be in the fist state to be able to press the play button
        alpha2 = 255;
        
      if(mouseX >= 585 && mouseX <= 625 && mouseY >= 335 && mouseY <= 365 ) {
          
          play = !play; // play the music of you click on the play button
      }
        
        if(x >= 145 && x <= 195 && y >= 500 && y <= 550 ) { // click on the grandular sythesiser button
            
            synth = !synth;
        }
        if(x >= 225 && x <= 275 && y >= 500 && y <= 550){
            vol = !vol;
           
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
