#ifndef LIGHT_H
#define LIGHT_H
#include "globalincludes.h"
#include "intersection.h"
class Scene;


class Light
{
public:
    Color3f mHue;
    Point3f mPos;
    Light(){}
    virtual bool ShadowTest(Opt<Intersection>& iIntersection, Scene& iScene) = 0; // true: can see the light (no shadow);
    ~Light(){}
};

class PointLight : public Light
{
public:
    PointLight(Point3f iP, Color3f iHue);
    virtual bool ShadowTest(Opt<Intersection>& iIntersection, Scene& iScene);
    ~PointLight(){}
};

#endif // LIGHT_H
