/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"


namespace rt{

class Triangle: public Shape{
public:

    Triangle(){};
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;

        norm  = (point2-point1).crossProduct(point3-point1).normalize();
    }
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3, Material* m):Shape(m){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;

        norm  = (point2-point1).crossProduct(point3-point1).normalize(); 
    }

    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

    ~Triangle(){}
private:
    // A, B, C
    Vec3f point[3];
    //cross product of (point1 - point2) and (point3 - point1)
    Vec3f norm;
};



} //namespace rt




#endif /* TRIANGLE_H_ */
