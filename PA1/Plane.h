//
//  Plane.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Plane_h
#define Plane_h
#include "Vector.h"
#include "Ray.h"
#include "Surface.h"
#include "Color.h"

class Plane : public Surface {
    Vector normal;
    Vector point;
    Color colorA;
    Color colorD;
    Color colorS;
    double power;
    double alpha;
    
public:
    
    Plane();
    Plane(Vector, Vector);
    
    //method calls
    virtual double getIntersection(Ray intersectRay) {
//        Vector ray = intersectRay.getDirection().normalize();
//        if (ray.getY() >= 0) {
//            // won't intersect plane at all
//            return -1;
//        } else {
//            return -1 * this->normal.dotproduct(intersectRay.getOrigin().subtract(this->point))/this->normal.dotproduct(ray);
//            //return /normal.dotproduct(intersectRay.getDirection().normalize());
//        }
        Vector p0 = this->point;
        Vector n = this->normal;
        Vector l = intersectRay.getDirection().normalize();
        Vector l0 = intersectRay.getOrigin();
        double denom = l.dotproduct(n);
        if (denom == 0) {
            return -1;
        } else {
            float t = (p0.subtract(l0)).dotproduct(n) / denom;
            if (t > 0.0001) {
                return t;
            } return -1;
        }
        
    }
    virtual Vector getNormal(Vector point) {
        return normal.normalize();
    }
    virtual Color getColorA(){ return colorA; }
    virtual Color getColorD(){ return colorD; }
    virtual Color getColorS(){ return colorS; }
    virtual double getPower(){ return power;  }
    virtual double getAlpha(){ return alpha; }
    
    void setColorA(double r, double g, double b) {colorA = Color(r, g, b);}
    void setColorD(double r, double g, double b) {colorD = Color(r, g, b);}
    void setColorS(double r, double g, double b) {colorS = Color(r, g, b);}
    void setPower(double p) {power = p;}
    void setAlpha(double a) {alpha = a;}
};

Plane::Plane() {
    normal = Vector();
    point = Vector();
}

Plane::Plane(Vector n, Vector p) {
    normal = n;
    point = p;
    
}

#endif /* Plane_h */
