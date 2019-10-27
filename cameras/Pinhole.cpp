/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"



namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookAt, Vec3f up)
	:Camera(width, height, fov,  position,  lookAt,  up){

		// to fill

	}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}


	Ray Pinhole::generate_ray(int i, int j){

		// compute ray in camera coordinate first
		float u = 2*tan(fov/2)/height;
		Vec3f direction((width/2-j),(height/2-i),1);
		Vec3f final_direction;
		Cam2World.multDirMatrix(direction.normalize(), final_direction);
		return Ray(position, final_direction);
}

} //namespace rt

