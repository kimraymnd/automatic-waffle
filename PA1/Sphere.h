//
//  Sphere.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h
#include "Vector.h"
#include "Surface.h"
#include "Color.h"
#include <math.h>

class Sphere : public Surface {
    Vector center;
    double radius;
    Color colorA;
    Color colorD;
    Color colorS;
    double power;
    double alpha;
    
public:
    
    Sphere();
    Sphere(Vector, double);
    
    //method calls
    virtual Vector getNormal(Vector point) {
        return point.subtract(center).normalize();
    }
    virtual Color getColorA(){ return colorA; }
    virtual Color getColorD(){ return colorD; }
    virtual Color getColorS(){ return colorS; }
    virtual double getPower() { return power; }
    virtual double getAlpha() {return alpha;}
    
    void setColorA(double r, double g, double b) {colorA = Color(r, g, b);}
    void setColorD(double r, double g, double b) {colorD = Color(r, g, b);}
    void setColorS(double r, double g, double b) {colorS = Color(r, g, b);}
    void setPower(double p) {power = p;}
    void setAlpha(double a) {alpha = a;}
    
    virtual double getIntersection(Ray ray) {
 
        Vector c = center;
        Vector o = ray.getOrigin();
        Vector l = ray.getDirection().normalize();
        double r = radius;
        double discriminant = pow(l.dotproduct(o.subtract(c)), 2) - pow(o.subtract(c).magnitude(), 2) + r*r;
        
        if (discriminant >= 0) {
            double d1 = -l.dotproduct(o.subtract(c)) - sqrt(discriminant);
            double d2 = -l.dotproduct(o.subtract(c)) + sqrt(discriminant);
            if(d1 > 0.0001) {
                    return d1;
            }
            else if (d2 > 0.0001) {
                return d2;
            }
        }
        return -1;
        
    }

};

Sphere::Sphere() {
    center = Vector();
    radius = 1;
}
Sphere::Sphere(Vector c, double r) {
    center = c;
    radius = r;
}

#endif /* Sphere_h */
