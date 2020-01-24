#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "primitive.h"


class Sphere : public Shape
{
private:
    Point3f mOrigin;
    float mRadius;
public:
    Sphere();
    virtual Opt<Intersection> getIntersection(Ray) const;
    ~Sphere(){}
};

class SquarePlane : public Shape
{
private:
    Point3f mOrigin;
    Vector3f mNormal;
    float mSideLength;
public:
    SquarePlane();
    virtual Opt<Intersection> getIntersection(Ray) const;
    ~SquarePlane(){}
};
#endif // GEOMETRY_H
