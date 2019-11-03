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

	Vec2f PlanerQuad::uvCompute(Vec3f point_){
        float d20[2];
        float d21;
        Vec3f v2 = point_ - point[0];
        d20[0] = v2.dotProduct(v0[0]); d20[1] = v2.dotProduct(v0[1]);
        d21 = v2.dotProduct(v1);
        float denom[2];
        float v[2], w[2], u[2];
        denom[0] = d00[0] * d11 - d01[0] * d01[0]; denom[1] = d00[1] * d11 - d01[1] * d01[1];

        v[0] = (d11 * d20[0] - d01[0] * d21) / denom[0]; v[1] = (d11 * d20[1] - d01[1] * d21) / denom[1];
        w[0] = (d00[0]* d21 - d01[0] * d20[0]) / denom[0]; w[1] = (d00[1]* d21 - d01[1] * d20[1]) / denom[1];
        
        u[0] = 1.0f - v[0] - w[0];u[1] = 1.0f - v[1] - w[1];
        Vec2f result;
        if(u[0] > 0){
            result= u[0]*material->uv[0] + v[0]*material->uv[1] + w[0]*material->uv[2];
        }else{
            result= u[1]*material->uv[0] + v[1]*material->uv[3] + w[1]*material->uv[2];
        }
    
        return result;
	}


} //namespace rt
