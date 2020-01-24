#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "globalincludes.h"
#include "transform.h"
#include "intersection.h"
#include "ray.h"

///
/// \brief The Shape class
/// The Shape class will be an abstract superclass for all intersectable surfaces,
/// such as spheres and planes.
///
class Shape
{
public:
    // A Transform member variable to enable you to
    // move the basic Shape around the scene and alter its scale and orientation.
    Transform mTransform;

    Shape(){}
    Shape(Transform& iTransform);
    virtual Opt<Intersection> getIntersection(Ray) const = 0;
    virtual ~Shape(){}
};

///
/// \brief Primitive::Primitive
///
/// contains data such as a shape, a material, and a light source.
///

class Primitive
{
public:
    QString mName;
    // be used to store an intersectable surface.
    uPtr<Shape> mUPtrShape;

    Primitive();
    Opt<Intersection> getIntersection(Ray iRay) const;
};


#endif // PRIMITIVE_H
