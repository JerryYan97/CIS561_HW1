#ifndef SCENE_H
#define SCENE_H

#include "qlist.h"
#include "globalincludes.h"
#include "primitive.h"
#include "camera.h"
#include <list>

class Scene
{
public:
    // QList<uPtr<Primitive>> mPrimitiveList;
    std::list<uPtr<Primitive>> mPrimitiveList;
    Camera mCamera;

    Scene();

    // Tests the input Ray for intersection with all Primitives in the Scene
    // Outputs the Intersection with the smallest non-negative t value via the Intersection* input to the function.
    // It should return false if the Ray does not intersect any geometry.
    bool getIntersection(Ray iRay, Intersection* iIntersection) const;
};

#endif // SCENE_H
