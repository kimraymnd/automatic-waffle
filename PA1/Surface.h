//
//  Surface.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Surface_h
#define Surface_h
#include "Vector.h"
#include "Ray.h"
#include "Color.h"

class Surface {
    
public:
    
    Surface();
    
    virtual double getIntersection(Ray IntersectRay) {
        return 0;
    }
    virtual Vector getNormal(Vector point) {
        return Vector();
    }
    virtual Color getColorA(){
        return Color();
    }
    virtual Color getColorD(){
        return Color();
    }
    virtual Color getColorS(){
        return Color();
    }
    virtual double getPower() {
        return 1;
    }
    virtual double getAlpha() {
        return 1;
    }
    
};

Surface::Surface(){}

#endif /* Surface_h */
