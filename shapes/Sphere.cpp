/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


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
		double edge = (center-ray.OriginalPoint).length();
		double l = (center-ray.OriginalPoint).dotProduct(ray.direction);
		//std::cout<<center<<' '<<ray.OriginalPoint<<' '<<l<<' '<<ray.direction<<std::endl;
		if(l <= 0)
			return Hit(false);
		
		double dist = sqrt(edge*edge-l*l);
		if(dist > radius)
			return Hit(false);

		double cut = sqrt(radius*radius-dist*dist);
		Vec3f point = ray.OriginalPoint + ray.direction*(l-cut);
		
		assert(abs((point-center).length() - radius)<1);

		return Hit(true, point, (point-center).normalize());

	}



} //namespace rt


