/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"

namespace rt{

class Pinhole:public Camera{
public:

	//
	// Constructors
	//
	Pinhole();
	Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookAt, Vec3f up);

	//
	//Destructor
	// 
	~Pinhole(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();


	Ray generate_ray(int i, int j);
};



} //namespace rt




#endif /* PINHOLE_H_ */
