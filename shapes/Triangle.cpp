/*
 * Triangle.cpp
 *
 *
 */
#include "shapes/Triangle.h"

namespace rt{


Hit Triangle::intersect(Ray ray){
    // Moller-Trumbore's algorithm
    //std::cout<<std::endl;
    float t = ray.triangleIntersect(point[0], point[1], point[2]);
    if (t > 0) 
        return Hit(true, ray.reachOut(t), norm.dotProduct(ray.direction) < 0? norm:-norm);
    else return Hit(false);
}


} //namespace rt
