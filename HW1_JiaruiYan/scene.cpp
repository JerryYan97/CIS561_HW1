#include "scene.h"

Scene::Scene()
{}

bool Scene::getIntersection(Ray iRay, Intersection* iIntersection) const
{
    bool flag = false;
    Opt<Intersection> nearrestIntersection;
    nearrestIntersection->t = FLT_MAX;

    // Iterater through all the primitives in the scene.
    for(auto itr = mPrimitiveList.begin(); itr != mPrimitiveList.end(); itr++)
    {
        Primitive* primPtr = itr->get();
        Opt<Intersection> tempIntersection = primPtr->getIntersection(iRay);

        // Get the nearestIntersection.
        if(tempIntersection != std::experimental::nullopt)
        {
            if(tempIntersection->t < nearrestIntersection->t)
            {
                iIntersection->mNormal = tempIntersection->mNormal;
                iIntersection->mPoint = tempIntersection->mPoint;
                iIntersection->mPtrObjectHit = tempIntersection->mPtrObjectHit;
                iIntersection->t = tempIntersection->t;
                nearrestIntersection = tempIntersection;
                flag = true;
            }
        }
    }
    return flag;
}
