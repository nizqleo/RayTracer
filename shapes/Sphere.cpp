/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"
#include <cmath>

namespace rt{

	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){
		double edge2 = (center-ray.OriginalPoint).norm();
		double l = (center-ray.OriginalPoint).dotProduct(ray.direction);
		//std::cout<<center<<' '<<ray.OriginalPoint<<' '<<l<<' '<<ray.direction<<std::endl;
		if(l <= 0)
			return Hit(false);
		
		double dist = sqrt(edge2-l*l);
		if(dist > radius)
			return Hit(false);

		double cut = sqrt(radius*radius-edge2+l*l);
		Vec3f point = ray.OriginalPoint + ray.direction*(l-cut);
		
		if(abs((point-center).length() - radius)>1){
			std::cout<<ray.OriginalPoint<<' '<<ray.direction<<std::endl;
			std::cout<<center<<' '<<radius<<std::endl;
			std::cout<<point<<std::endl;
			assert(abs((point-center).length() - radius)<1);
		}
		return Hit(true, point, (point-center).normalize());
	}

	Vec2f Sphere::uvCompute(Vec3f point){
		// map to the surface
		Vec3f dire = (point-center).normalize();
		float beta = acos(dire.dotProduct(Vec3f(0,0,1)));
		float u = beta/M_PI;

		// wrap from -y direction
		float alpha = acos(dire.dotProduct(Vec3f(0,-1,0)));
		if(dire.dotProduct(Vec3f(1,0,0)) < 0)
			alpha = 2*M_PI-alpha;
		float v = alpha/(2*M_PI);

		return Vec2f(u,v);

	}

} //namespace rt


