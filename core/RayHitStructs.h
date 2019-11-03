/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include <stdlib.h>
#include <time.h>

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Hit{
	Hit(){}
	Hit(bool e, Vec3f p, Vec3f norm):exist(e), point(p), normVector(norm){}
	Hit(bool e):exist(e){}

	bool exist;
	Vec3f point; //point where ray hits a shape	
	Vec3f normVector;
};

struct Ray{

	RayType raytype;
	Vec3f OriginalPoint;
	Vec3f direction;

	// constructor with ramdonness.
	Ray(){}
	Ray(Hit hit):OriginalPoint(hit.point){
		// ramdonly generate direction.
		direction = Vec3f(rand(), rand(), rand())-RAND_MAX;
		if (direction.dotProduct(hit.normVector) < 0)
			direction = -direction;	
		
		direction=direction.normalize();
	}
	Ray(Vec3f posi, Vec3f dire):OriginalPoint(posi), direction(dire){}

	Vec3f reachOut(float t){return OriginalPoint+t*direction;}

	float triangleIntersect(Vec3f p1, Vec3f p2, Vec3f p3){
		Vec3f e1 = p2-p1;
		Vec3f e2 = p3-p1;
	    Vec3f pvec = direction.crossProduct(e2);
		float det = e1.dotProduct(pvec);

		if (det < 0) 
			return triangleIntersect(p1, p3, p2);
		
		Vec3f tvec = OriginalPoint - p1;
		float u = tvec.dotProduct(pvec)/det;

		if (u < 0 || u > 1) return -1;

		Vec3f qvec = tvec.crossProduct(e1);
		float v = direction.dotProduct(qvec)/det;

		if (v < 0 || u + v > 1) return -1;
		float t = e2.dotProduct(qvec)/det;

		if (t > 0) 
			return t;
		else return -1;
	}
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
