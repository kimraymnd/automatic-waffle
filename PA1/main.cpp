//
//  main.cpp
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Light.h"
#include "Surface.h"
#include "Color.h"

#include <vector>
#include <math.h>
#include <cstdlib>

using namespace std;
void init();
void display(void);
void drawObject();
//double gammaEncode(double, double);

int window_x;
int window_y;

int window_width = 512;
int window_height = 512;

char *window_title = "Ray's Recursive Ray Tracer";

struct RGBtype {
    char r;
    char g;
    char b;
};

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

/*************************************************************************
    helper function that returns the index with the least greatest value
    input: vector<>, output: int
 *************************************************************************/
int closestIndex(vector<double> intersections) {
    int index = 0;
    if (intersections.size() == 0) { return -1; }
    else if (intersections.size() == 1) {
        if (intersections.at(0) > 0) {
            return 0;
        } else return -1;
    }
    else {
        double greatest = 0;
        for (int i=0; i<intersections.size(); i++) {
            if (greatest < intersections.at(i)) {
                greatest = intersections.at(i);
            }
        }
        if (greatest > 0) {
            for (int j=0; j<intersections.size(); j++) {
                if (intersections.at(j)>0 && intersections.at(j) <= greatest) {
                    greatest = intersections.at(j);
                    index = j;
                }
            }
            return index;
        }
        else { return -1; }
    }
}

/*******************************************************************************
 helper function that returns the color on the surface given material parameters
 input: a bunch of stuff, output: Color type
    * viewing ray with origin and a direction
    * an intersection point (namely, origin + direction)
 *******************************************************************************/

// fix up getColor parameters, shadow, mirror calculations

Color getColor(Ray view, Vector point,
               vector<Surface*> sceneSurfaces, int indexofClosestObject,
               double accuracy, Light lightsource, int count) {
    
    //Phong Shading Algorithm
    //**************************************************************************
    double power = sceneSurfaces.at(indexofClosestObject)->getPower();
    Vector n = sceneSurfaces.at(indexofClosestObject)->getNormal(point);
    Vector l = lightsource.getPosition().subtract(point).normalize();
    Vector v = view.getDirection().negate().normalize();
    Vector h = v.add(l).normalize();
    
    double nl = fmax(0, n.dotproduct(l));
    double nh = pow(fmax(0, n.dotproduct(h)), power);
    
    //ambient (lA), diffusion (lD), and specular (lS)
    Color lA = sceneSurfaces.at(indexofClosestObject)->getColorA().scale(255);
    Color lD = sceneSurfaces.at(indexofClosestObject)->getColorD().scale(255).scale(nl);
    Color lS = sceneSurfaces.at(indexofClosestObject)->getColorS().scale(255).scale(nh);
    double alpha = sceneSurfaces.at(indexofClosestObject)->getAlpha();
    Color final = lA.add(lD).add(lS).clip();
    
    //Shadowing
    //***************************************************************************
    Ray shadowRay = Ray(point, lightsource.getPosition().subtract(point));
    vector<double> shadowIntersections;
    for (int i=0; i<sceneSurfaces.size(); i++) {
        shadowIntersections.push_back(sceneSurfaces.at(i)->getIntersection(shadowRay));
    }
    int indexOfIntersection = closestIndex(shadowIntersections);
    if (indexOfIntersection != -1) {
        //intersection exists, must shade
        final =  lA;
    }
    
    //Mirroring
    //***************************************************************************
    Color lM;
    if(alpha == 0) {
        //not a reflective surface
        return final;
    } else if (count == 2) {
        //end of recursive statement
        return final.scale(1-alpha);
    } else  {
        //determine mirror ray
        Vector incident = point;
        double scalar = view.getDirection().dotproduct(n)*2;
        Vector mirrorDirection = view.getDirection().subtract(n.scale(scalar)).normalize();
        Ray mirror = Ray(incident, mirrorDirection);
        
        //calculate intersection spot w/ mirror
        //***********************************************************************
        vector<double> mirrorIntersections;
        for (int i=0; i<sceneSurfaces.size(); i++) {
            mirrorIntersections.push_back(sceneSurfaces.at(i)->getIntersection(mirror));
        }
        //parameter of interseciton mirror
        int indexOfMirror = closestIndex(mirrorIntersections);
        //***********************************************************************
        
        if(indexOfMirror == -1) {
            //no intersections in the mirror
            //hits sky, return black
            lM = Color(0,0,0);
        } else if (mirrorIntersections.at(indexOfMirror) > accuracy){
            //intersection exists
            //determine new parameters and recurse
            Ray newView = Ray(point, mirrorDirection.scale(mirrorIntersections.at(indexOfMirror)));
            Vector newPoint = point.add(mirrorDirection.scale(mirrorIntersections.at(indexOfMirror)));
            lM = getColor(newView, newPoint, sceneSurfaces, indexOfMirror, accuracy, lightsource, count+1);
        }
        final = final.scale(1 - alpha).add(lM.scale(alpha));
        
    }

    return final;
}

/*******************************************************
 helper function that return the gamma corrected r/g/b value
 input: color value and gamma, output: double
 *******************************************************/

double gammaEncode(double color, double gamma) {
    return pow(color/255, 1/gamma)*255;
}
/*******************************************************
 function to set up all our objects in the scene
 *******************************************************/
void drawObject() {
    int width = window_width;
    int height = window_height;
    int size = width*height;
    
    //colors
    RGBtype *pixels = new RGBtype[size];
    Color white = Color(255, 255, 255);
    
    //light
    Vector light = Vector(-4, 4, -3);
    Light sceneLight = Light(light, white);
    
    //creating surfaces
    //**********************************************************
    Sphere sphereOne = Sphere(Vector(-4, 0, -7), 1);
    sphereOne.setColorA(0.2, 0, 0);
    sphereOne.setColorD(1, 0, 0);
    sphereOne.setColorS(0, 0, 0);
    sphereOne.setPower(0);
    sphereOne.setAlpha(0);
    
    Sphere sphereTwo = Sphere(Vector(0, 0, -7), 2);
    sphereTwo.setColorA(0, 0.2, 0);
    sphereTwo.setColorD(0, 0.5, 0);
    sphereTwo.setColorS(0.5, 0.5, 0.5);
    sphereTwo.setPower(32);
    sphereTwo.setAlpha(0);
    
    Sphere sphereThree = Sphere(Vector(4, 0, -7), 1);
    sphereThree.setColorA(0, 0, 0.2);
    sphereThree.setColorD(0, 0, 1);
    sphereThree.setColorS(0, 0, 0);
    sphereThree.setPower(0);
    sphereThree.setAlpha(0.8);
    
    Plane planeOne = Plane(Vector(0, 1, 0), Vector(1,-2,1));
    planeOne.setColorA(0.2, 0.2, 0.2);
    planeOne.setColorD(1, 1, 1);
    planeOne.setColorS(0, 0, 0);
    planeOne.setPower(0);
    planeOne.setAlpha(0.5);
    
    //scene array build
    vector<Surface*> sceneSurfaces;
    sceneSurfaces.push_back(dynamic_cast<Surface*>(&sphereOne));
    sceneSurfaces.push_back(dynamic_cast<Surface*>(&sphereTwo));
    sceneSurfaces.push_back(dynamic_cast<Surface*>(&sphereThree));
    sceneSurfaces.push_back(dynamic_cast<Surface*>(&planeOne));
    
    //some other values
    double accuracy = 0.000001;
    double gamma = 2.2;
    int samples = 16;
    
    int pixel;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            pixel = y*width + x;
            
            // anti aliasing process
            /******************************************************************************
            for each pixel (x,y), pick N samples of random x and y values within the pixel
            generate rays and add up total color then uniformly average with box filter
             ******************************************************************************/
            Color total = Color(0,0,0);
            for (int a=0; a<samples; a++) {
                // random number between 0-1
                double randomX = rand() % 1000;
                double randomY = rand() % 1000;
                randomX /= 1000;
                randomY /= 1000;
                randomX -= 0.5;
                randomY -= 0.5;
                randomX += x;
                randomY += y;
                
                //viewing ray given randomX and randomY
                double u = -.1 + (.2)*((randomX-1) + .5) / 512;
                double v = -.1 + (.2)*((randomY-1) + .5) / 512;
                
//                double u = -.1 + (.2)*((x-1) + .5) / 512;
//                double v = -.1 + (.2)*((y-1) + .5) / 512;
                Vector origin = Vector(0, 0, 0);
                Vector direction = Vector(u,v,-0.1).normalize();
                Ray intersect = Ray(origin, direction);
                
                //getting intersections with the new viewing ray
                vector<double> intersections;
                for (int i=0; i<sceneSurfaces.size(); i++) {
                    intersections.push_back(sceneSurfaces.at(i)->getIntersection(intersect));
                }
                int indexOfClosest = closestIndex(intersections);
                
                // misses surface
                if (indexOfClosest == -1) {
                    pixels[pixel].r = 0;
                    pixels[pixel].g = 0;
                    pixels[pixel].b = 0;
                }
                // hits surface
                else {
                    if (intersections.at(indexOfClosest) > accuracy) {
                        Vector intersectionPosition = direction.scale(intersections.at(indexOfClosest));
                        Vector intersectingDirection = direction;
                        Ray view = Ray(origin, intersectionPosition);
                        Color colorAtIntersection = getColor(view, intersectionPosition, sceneSurfaces, indexOfClosest, accuracy, sceneLight, 0);
                        total = total.add(colorAtIntersection);
                    }
                }
            }
            
            //uniform average of random sample colors
            total = total.scale((double)1/samples);
            //gamma correction
            pixels[pixel].r = gammaEncode(total.getRed(), gamma);
            pixels[pixel].g = gammaEncode(total.getGreen(), gamma);
            pixels[pixel].b = gammaEncode(total.getBlue(), gamma);
            
        }
    }
    //some openGL stuff
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glFlush();
}

void display(void) {
    //more openGL stuff
    glClear(GL_COLOR_BUFFER_BIT);
    drawObject();
    glutSwapBuffers();
}



int main(int argc, char * argv[]) {
    
    //even more openGL stuff
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(window_x, window_y);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(window_title);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}














