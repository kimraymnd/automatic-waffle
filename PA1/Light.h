//
//  Light.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Light_h
#define Light_h
#include <math.h>
#include "Vector.h"

class Light {
    Vector position;
    Color color;
    
public:
    
    Light();
    Light(Vector, Color);
    
    //method calls
    Color getColor() {return color;}
    Vector getPosition() {return position;}
    
};

Light::Light() {
    position = Vector();
    color = Color();
}

Light::Light(Vector p, Color c) {
    position = p;
    color = c;
}

#endif /* Light_h */
