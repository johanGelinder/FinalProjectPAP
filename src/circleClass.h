//
//  circleClass.h
//  PAPver1
//
//  Created by Johan Gelinder on 2015-11-12.
//
//

#ifndef __PAPver1__circleClass__
#define __PAPver1__circleClass__

#include <stdio.h>
#include "ofMain.h"

class circleClass {
    
public:
    
    //methods
    
    void display();
    void update();
    void drawRect(int i);
    
    float x; // posX
    float y; // posY
    float radius;
    int numRects;
    float rectWidth;
    float rectLength;
    float alpha;
    
    circleClass(float x, float y, float radius, int numRects, float rectWidth, float rectLength);
    
    // destructor
    ~circleClass();
    
};


#endif /* defined(__PAPver1__circleClass__) */
