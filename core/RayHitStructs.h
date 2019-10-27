/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{

	RayType raytype;
	//----------Ray variables to be filled------
	Vec3f OriginalPoint;
	Vec3f direction;

	// constructor with ramdonness.
	Ray(){}
	Ray(Vec3f posi):OriginalPoint(posi)	{
		// ramdonly generate direction.
	}
	Ray(Vec3f posi, Vec3f dire):OriginalPoint(posi), direction(dire){}


};


struct Hit{

	Vec3f point; //point where ray hits a shape
	//----------Hit variables to be filled------

};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
