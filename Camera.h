//
//  Camera.h
//  Parser
//
//  Created by Clinton Medbery on 10/1/14.
//  Copyright (c) 2014 Clinton Medbery. All rights reserved.
//

#ifndef __Parser__Camera__
#define __Parser__Camera__

#include <stdio.h>

// Declare Vector3 class to be used by attributes of Camera.
class Vector3{
public:
    float x;
    float y;
    float z;
};

class Camera
{
    
    
public:
    float fov;
    float aspect;
    float near;
    float far;
    
    // Attributes of type Vector3
    Vector3 myUpVec;
    Vector3 myPositionVec;
    Vector3 myScaleVec;
    
    // Move these outside of class Camera...can all be in Camera.h
    class Rotation {
        float x;
        float y;
        float z;
    } rotation;
    
    class Quaternion {
        float x;
        float y;
        float z;
        float w;
    } quaternion;
    
    
    Camera();
    void Test();
    ~Camera();
};

#endif /* defined(__Parser__Camera__) */
