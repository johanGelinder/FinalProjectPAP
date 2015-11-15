//
//  particleClass.h
//  PAPver1
//
//  Created by Johan Gelinder on 2015-11-12.
//
//

#ifndef __PAPver1__particleClass__
#define __PAPver1__particleClass__

#include <stdio.h>
#include "ofMain.h"

class Particles {
    
public:
    
    // Methods
    
    void display(); // display method
    void update();  // update method
    
    // variables
    
    float x; // position
    float y;
    int dim; // size of the particles
    
    // speed and direction
    float speedX;
    float speedY;
    
    ofColor color; // color
    
    // Constructor
    
    Particles(float x, float y, int dim);
    
};

#endif /* defined(__PAPver1__particleClass__) */
