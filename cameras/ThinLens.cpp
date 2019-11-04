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
	ThinLens::ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookAt, Vec3f up, float a, float f):Camera(width, height, fov,  position,  lookAt,  up),focus_dist(f),aperture(a) {
		lens_radius = aperture/2;
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("\nCamera information:\n");
		printf("Type: thinlens camera width: %dpx, height: %dpx, fov:%d, focus:%f, aperture:%f \n", width, height, fov, focus_dist, aperture);
	}

	Ray ThinLens::generate_ray(int i, int j){
		float u = 2*tan(fov/2)/height;
		Vec2f rd = lens_radius*ThinLens::random_in_unit_disk();
		Vec3f original = Vec3f(rd.x, rd.y, 0);
		Vec3f pixel = Vec3f((width/2-j)*u,(height/2-i)*u,focus_dist);
		Vec3f worldO, worldDir;
		Cam2World.multVecMatrix(original, worldO);
		Cam2World.multDirMatrix(pixel-original, worldDir);

		return Ray(worldO, worldDir.normalize());
	}

} //namespace rt
