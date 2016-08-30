//
//  Color.h
//  PA1
//
//  Created by Raymond Kim on 2/14/16.
//  Copyright © 2016 raymnd. All rights reserved.
//

#ifndef Color_h
#define Color_h
#include <math.h>

class Color {
    double red, green, blue;

public:
    
    Color();
    Color(double, double, double);
    
    //method calls
    double getRed()     { return red;   }
    double getGreen()   { return green; }
    double getBlue()    { return blue;  }
    
    void setRed( double r )     { red = r;   }
    void setGreen( double g )   { green = g; }
    void setBlue( double b )    { blue = b;  }
    
    Color scale(double k) {
        return Color(k*red, k*green, k*blue);
    }
    Color add(Color c) {
        return Color(red + c.getRed(), green + c.getGreen(),blue + c.getBlue());
    }
    Color clip() {
        double all = red + green + blue;
        double excess = all - 3*255;
        if (excess > 0) {
            red = red + excess*(red/all);
            green = green + excess*(green/all);
            blue = blue + excess*(blue/all);
        }
        if (red > 255) {red = 255;}
        if (green > 255) {green = 255;}
        if (blue > 255) {blue = 255;}
        if (red < 0) {red = 0;}
        if (green < 0) {green = 0;}
        if (blue < 0) {blue = 0;}
        
        return Color(red, green, blue);
    }
    
};

Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
}

Color::Color(double r, double g, double b) {
    red = r;
    green = g;
    blue = b;
}

#endif /* Color_h */
