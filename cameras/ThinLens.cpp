/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>


#include "ThinLens.h"


namespace rt{

	//
	// ThinLens constructor (example)
	//
	ThinLens::ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookAt, Vec3f up):Camera(width, height, fov,  position,  lookAt,  up){

		//to fill

	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("I am a thin lens camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	Ray ThinLens::generate_ray(int i, int j){
		std::cout<<"Oops! Temperate function called!"<<std::endl;
		return Ray(Vec3f(0,0,0), Vec3f(0,0,0));
	}

} //namespace rt
