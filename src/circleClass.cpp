//
//  circleClass.cpp
//  PAPver1
//
//  Created by Johan Gelinder on 2015-11-12.
//
//

#include "circleClass.h"

circleClass::circleClass(float _x, float _y, float _radius, int _numRects, float _rectWidth, float _rectLength) {
    
    x = _x;
    y = _y;
    radius = _radius;
    numRects = _numRects;
    rectWidth = _rectWidth;
    rectLength =_rectLength;
    
    alpha = 200; // set the oppacity
}

void circleClass::drawRect( int i )  {
    
    ofPushStyle();
    ofSetColor(255,alpha); // setting the colour of the rectangle to white with oppacity
    ofRect(100, 0, rectLength, rectWidth); // drawing the rectangles
    ofPopStyle();
}

void circleClass::update(float i){
    
    rectLength = 10 +i/2; // the lenght of the rectangles is reacting to the fft
}

void circleClass::display() {
    
    //float angle = TWO_PI / numRects; // getting the angle for the rotation by dividing TWO_PI by the number if rectagles
    
    for ( int i = 0; i < numRects; i ++) { // looping through all the rectangles
      
        ofPushMatrix();
        ofTranslate(x, y); // center of the screen
        ofRotate(i * 3.6); // rotating i * angle = 360/ 100 rectangles
        drawRect( i ); // calling the drawRect function to draw the colour wheel by using i that also has been used to rotate it
        ofPopMatrix();
        
    }
}

circleClass::~circleClass(){
    
    delete this;
}
