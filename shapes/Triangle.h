/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Material.h"

namespace rt{

class Triangle: public Shape{
public:

    Triangle(){}
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
    };
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3, Material* m):Shape(m){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
    };

    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

    ~Triangle(){}

private:
    Vec3f point[3];

};



} //namespace rt




#endif /* TRIANGLE_H_ */
