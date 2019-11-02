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
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
