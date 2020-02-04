#include "light.h"
#include "scene.h"
PointLight::PointLight(Point3f iP, Color3f iHue)
{
    mHue = iHue;
    mPos = iP;
}

bool PointLight::ShadowTest(Opt<Intersection> &iIntersection, Scene &iScene)
{
    Vector3f dir = glm::normalize(iIntersection->mPoint - mPos);
    Ray tempRay = Ray(mPos, dir);
    Opt<Intersection> tempIntersection = iScene.getIntersection(tempRay);
    if(tempIntersection == std::experimental::nullopt)
    {
        return false;
    }
    else
    {
        if(glm::length(iIntersection->mPoint - tempIntersection->mPoint) < 0.0001)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
