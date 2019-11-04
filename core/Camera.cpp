/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

Camera::Camera(int height, int width, int fov, 	Vec3f position, Vec3f lookAt, Vec3f up):
	height(height), width(width), fov(fov), position(position), lookAt(lookAt), up(up){
		Vec3f forward = (lookAt-position).normalize(); 
		up = up - up.dotProduct(forward)*forward;
		up = up.normalize();
    	Vec3f left = -forward.crossProduct(up);
		left = left.normalize();
 
		Cam2World[0][0] = left.x; 
		Cam2World[0][1] = left.y; 
		Cam2World[0][2] = left.z; 
		Cam2World[0][3] = 0; 
		Cam2World[1][0] = up.x; 
		Cam2World[1][1] = up.y; 
		Cam2World[1][2] = up.z; 
		Cam2World[1][3] = 0; 
		Cam2World[2][0] = forward.x; 
		Cam2World[2][1] = forward.y; 
		Cam2World[2][2] = forward.z; 
		Cam2World[2][3] = 0;

		Cam2World[3][0] = position.x; 
		Cam2World[3][1] = position.y; 
		Cam2World[3][2] = position.z; 
		Cam2World[3][3] =1;
		
	}

	Camera::~Camera(){};


/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){

	//check if cameratype is defined

	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType=cameraSpecs["type"].GetString();

	//return camera object based on camera specs
	if (cameraType.compare("pinhole")==0){
		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				Vec3f(cameraSpecs["position"].GetArray()),
				Vec3f(cameraSpecs["lookAt"].GetArray()),
				Vec3f(cameraSpecs["up"].GetArray()));

	}else if (cameraType.compare("thinlens")==0){
		return new ThinLens(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				Vec3f(cameraSpecs["position"].GetArray()),
				Vec3f(cameraSpecs["lookAt"].GetArray()),
				Vec3f(cameraSpecs["up"].GetArray()),
				cameraSpecs["aperture"].GetFloat(),
				cameraSpecs["focus_dist"].GetFloat()
				);
	}

	return 0;

}




} //namespace rt
