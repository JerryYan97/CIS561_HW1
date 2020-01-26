#include "geometry.h"
#include <iostream>

Sphere::Sphere()
{
    mOrigin = Point3f(0, 0, 0);
    mRadius = 0.5f;
}

SquarePlane::SquarePlane()
{
    mOrigin = Point3f(0, 0, 0);
    mSideLength = 1.f;
    mNormal = Vector3f(0, 0, 1.f);
}

Opt<Intersection> Sphere::getIntersection(Ray iRay) const
{
    Ray localRay = iRay.Transform(mTransform.mWorldTransformInverse);
    Point3f localPos = localRay.pos;
    Vector3f localDir = localRay.dir;

    glm::vec3 oc = localPos - mOrigin;
    float a = glm::dot(localDir, localDir);
    float b = 2.0 * glm::dot(localDir, oc);
    float c = glm::dot(oc, oc) - mRadius * mRadius;

    float discriminant = b * b - 4 * a * c;
    if(discriminant > 0)
    {
        Intersection tempIntersection;
        float temp_t = (-b - glm::sqrt(discriminant)) / (2.f * a);
        if(temp_t < 0.f)
        {
            temp_t = (-b + glm::sqrt(discriminant)) / (2.f * a);
        }

        if(temp_t < 0.f)
        {
            return std::experimental::nullopt;
        }
        else
        {
            tempIntersection.t = temp_t;
            tempIntersection.mPoint = localDir * temp_t + localPos;
            tempIntersection.mNormal =
                    glm::normalize(mTransform.mWorldTransformInverseTranspose * tempIntersection.mPoint);
            return Opt<Intersection>(tempIntersection);
        }
    }
    else
    {
        return std::experimental::nullopt;
    }
}

Opt<Intersection> SquarePlane::getIntersection(Ray iRay) const
{
    Ray localRay = iRay.Transform(mTransform.mWorldTransformInverse);
    Point3f localPos = localRay.pos;
    Vector3f localDir = localRay.dir;

    float t = glm::dot(mNormal, (mOrigin - localPos)) / glm::dot(mNormal, localDir);

    Point3f intersectionPoint = localDir * t + localPos;
    Normal3f worldNormal = Normal3f(mTransform.mWorldTransformInverseTranspose * mNormal);


    if(intersectionPoint.x < 0.5 && intersectionPoint.x > -0.5 && intersectionPoint.y < 0.5 && intersectionPoint.y > -0.5)
    {
        Intersection tempIntersection;
        tempIntersection.mPoint = Point3f(mTransform.mWorldTransform * glm::vec4(intersectionPoint, 1.0f));
        tempIntersection.mNormal = worldNormal;
        tempIntersection.t = t;
        return Opt<Intersection>(tempIntersection);
    }
    else
    {
        return std::experimental::nullopt;
    }
}
