//
//  particleClass.cpp
//  PAPver1
//
//  Created by Johan Gelinder on 2015-11-12.
//
//

#include "particleClass.h"

Particles::Particles(float _x, float _y, int _dim) {  // implementation of the constructor :: means that we are calling a function on Particles object
    
    x = _x;
    y = _y;
    dim = _dim;
    
    // random speed
    speedX = ofRandom(-0.8,0.8);
    speedY = ofRandom(-0.8,0.8);
    
    color.set(255,70); // white color with opacity
}

void Particles::update() {
    
    /*---------------- collision ------------*/
    
    if(x < 300) { // checks if the x position is less than 300
        x = 900; // moves the particle to the opposite side
        
    } else if (x > 900) { // checks if the x position is greater than 900
        x = 300; // moves the particle to the opposite side
    }
    
    if( y < 50) { // checks if the y position is less than 50
        y = 650; // moves the particle to the opposite side

    } else if (y > 650) { // checks if the x position is greater than 600
        y = 50; // moves the particle to the opposite side
    }
    
    x += speedX; // assign speedX to the x position which is a random number
    y += speedY; // assign speedY to the y position which is a random number
    
    //dim = ofRandom(4,8); // setting the dimention of the particles to be a random number this will be replaced by the fft values from audio file that plays
}

void Particles::display() {  // display function
    
    ofPushStyle();
    ofSetColor(color); // assigning the color
    ofCircle( x, y, dim); // drawing the particles with numbers set by the constructor
    ofPopStyle();
    
}


