//
//  Ray.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Ray_h
#define Ray_h
#include <math.h>
#include "Vector.h"

class Ray {
    Vector origin;
    Vector direction;
    
public:
    
    Ray();
    Ray(Vector, Vector);
    
    //method calls
    Vector getOrigin() {
        return origin;
    }
    Vector getDirection() {
        return direction;
    }
    
};

Ray::Ray() {
    origin = Vector(0, 0, 0);
    direction = Vector(0, 0, 0);
}

Ray::Ray(Vector o, Vector d) {
    origin = o;
    direction = d;
}

#endif /* Ray_h */
