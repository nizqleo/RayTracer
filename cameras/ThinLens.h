/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include "math/geometry.h"
#include <stdlib.h>

namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookAt, Vec3f up, float aperture, float focus_dist);
	
	static Vec2f random_in_unit_disk(){
		Vec2f p(drand48()-1, drand48()-1);
		while(p.norm() >= 1){
			p=Vec2f(drand48()-1, drand48()-1);
		}
		return p;
	}	


	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
	Ray generate_ray(int i, int j);

private:
	float aperture;
	float lens_radius;
	float focus_dist;

};



} //namespace rt




#endif /* THINLENS_H_ */
