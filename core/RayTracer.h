/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/RayHitStructs.h"


namespace rt{



/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	/* Return the a pixelbuffer with size (height, width),
	 * Height & Width get from the camera. 
	 */ 
	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);

	// take in pixelbuffer (size (height, width)), return a pixel_mapped_buffer
	static Vec3f* tonemap(Vec3f* pixelbuffer);

	static Vec3f TracePath(Scene* scene, int nbounces_left);
private:


};




} //namespace rt



#endif /* RAYTRACER_H_ */

