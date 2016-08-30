//
//  Vector.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Vector_h
#define Vector_h
#include <math.h>

class Vector {
    double x, y, z;
    
public:
    
    Vector();
    Vector(double, double, double);
    
    //method calls
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    Vector scale(double k) {
        return Vector(k*x, k*y, k*z);
    }
    Vector add(Vector v) {
        return Vector(x+v.getX(), y+v.getY(), z+v.getZ());
    }
    Vector subtract(Vector v) {
        return Vector(x-v.getX(), y-v.getY(), z-v.getZ());
    }
    double magnitude() {
        return sqrt(x*x + y*y + z*z);
    }
    Vector normalize() {
        double magnitude = sqrt(x*x + y*y + z*z);
        return Vector(x/magnitude, y/magnitude, z/magnitude);
    }
    double dotproduct(Vector v) {
        double dp = x*v.getX() + y*v.getY() + z*v.getZ();
        return dp;
    }
    Vector negate() {
        return Vector(-x, -y, -z);
    }
    
};

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}


#endif /* Vector_h */
