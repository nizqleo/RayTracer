/*
 * PlanerQuad.cpp
 *
 *
 */
#include "PlanerQuad.h"
#include "Triangle.h"
namespace rt{

Hit PlanerQuad::intersect(Ray ray){
    // assume that point 1,2,3,4 are seen to be clockwise
    // Moller-Trumbore's algorithm

    // point: 1,2,3 edge:0,1
    float t = ray.triangleIntersect(point[0], point[1], point[2]);
    if (t > 0) 
        return Hit(true, ray.reachOut(t), norm.dotProduct(ray.direction) < 0? norm:-norm);
    else {
        t = ray.triangleIntersect(point[0], point[3], point[2]);
        if (t > 0) 
            return Hit(true, ray.reachOut(t), norm.dotProduct(ray.direction) < 0? norm:-norm);
        else return Hit(false);
    }
}

} //namespace rt
