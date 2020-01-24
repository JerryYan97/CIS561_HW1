#include "primitive.h"


Primitive::Primitive()
{

}

Opt<Intersection> Primitive::getIntersection(Ray iRay) const
{
    Opt<Intersection> temp = mUPtrShape->getIntersection(iRay);

    if(temp != std::experimental::nullopt)
    {
        temp->mPtrObjectHit = this;
    }
    return temp;

    // The Ray does not intersect with the object.

    // Return an Intersection value if the ray intersects the object.
    // The Intersection's objectHit should point to this.
}
