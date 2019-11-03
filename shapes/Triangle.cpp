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
    float t = ray.triangleIntersect(TriPoint[0], TriPoint[1], TriPoint[2]);
    if (t > 0) 
        return Hit(true, ray.reachOut(t), norm.dotProduct(ray.direction) < 0? norm:-norm);
    else return Hit(false);
}

	Vec2f Triangle::uvCompute(Vec3f point){
        Vec3f v2 = point - TriPoint[0];
        v2=v2-v2.dotProduct(norm)*norm;
        // float v = (v1.crossProduct(v2)).length()/area;
        // float w = (v0.crossProduct(v2)).length()/area;
        // float u = 1-v-w;
        float d20 = v2.dotProduct(v0);
        float d21 = v2.dotProduct(v1);
        float denom = d00 * d11 - d01 * d01;

        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;
        //std::cout<<u<<' '<<v<<' '<<w<<' ';
        Vec2f result= u*material->uv[0] + v*material->uv[1] + w*material->uv[2];
        return result;
	}

} //namespace rt
