
RUNNING THE CODE METHOD 1
    open up "PA1.xcodeproj" via Xcode
    hit Run under [Product > Run] or by pressing command-R
    output should generate in a new window

RUNNING THE CODE METHOD 2
    create a new Xcode project
    delete main.cpp in source folder
    right click folder > add files to "<whatever you named your project>"...
    add all 8 files to the project
        main.cpp
        Vector.h
        Sphere.h
        Plane.h
        Ray.h
        Light.h
        Surface.h
        Color.h
    click root(?) folder with blue icon on top of folder hierarchy
    under "Build Phases" click "Link Binary With Libraries"
    click the 'add' sign and add "OpenGL.framework" and "GLUT.framework"
    there should be 4 main folder under root project called
        OpenGL.framwork
        GLUT.framework
        <name of project>
        Products
    hit Run under [Product > Run] or by pressing command-R
    output should generate in a new window


RUNNING TIME
    should generate w/ reflections in less than 20s with 16 samples (anti aliasing)