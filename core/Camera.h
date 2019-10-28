/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt{

class Camera{
public:

	//
	// Constructors
	//
	Camera(){};
	Camera(int height, int width, int fov, Vec3f position, Vec3f lookAt, Vec3f up);

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;


	/**	generate ray for every pixel
	 *  pixels are distributed like:
	 * 				0-->j
	 * 				| 
	 * 				v i
	 * 
	 * 0  0  0   100 0  0       0  0  0    255   0 255
	 * 0  0  0    0 255 175     0  0  0     0    0  0
	 * 0  0  0    0  0  0       0 15 175    0    0  0
	 * 255 0 255  0  0  0       0  0  0    255  255 255
	 * 
	 **/
	virtual Ray generate_ray(int i, int j)=0;










	//
	// Getters and Setters
	//
	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}



protected:

	//
	//camera members
	//
	int height;
	int width;
	int fov; //field of view

	Vec3f position;
	Vec3f lookAt;
	Vec3f up;

	/** Description of camera coordinate:
	 * 				^ y
	 * 				|
	 * 			x<--0
	 *  and Z is the front direction.
	 **/
	Matrix44f Cam2World;

};

} //namespace rt



#endif /* CAMERA_H_ */
