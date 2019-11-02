/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{


Hit Triangle::intersect(Ray ray){
    // Moller-Trumbore's algorithm
    //std::cout<<std::endl;
    Vec3f pvec = ray.direction.crossProduct(edge[1]);
    float det = edge[0].dotProduct(pvec);
    //std::cout<<"det"<<det<<' ';
    if (det < 0) {
        exchange();
        return intersect(ray);
    }

    Vec3f tvec = ray.OriginalPoint - point[0];
    float u = tvec.dotProduct(pvec)/det;
    //std::cout<<"u"<<u<<' ';

    if (u < 0 || u > 1) return Hit(false);

    Vec3f qvec = tvec.crossProduct(edge[0]);
    float v = ray.direction.dotProduct(qvec)/det;
    //std::cout<<"v"<<v<<' ';

    if (v < 0 || u + v > 1) return Hit(false);
    float t = edge[1].dotProduct(qvec)/det;
    //std::cout<<"t"<<t;

    if (t > 0) 
        return Hit(true, ray.reachOut(t), norm.dotProduct(ray.direction) < 0? norm:-norm);
    else return Hit(false);
    
}


} //namespace rt
