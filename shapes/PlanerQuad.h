/*
 * PlanerQuad.h
 *
 *
 */

#ifndef PLANERQUAD_H_
#define PLANERQUAD_H_


#include "shapes/Triangle.h"

namespace rt{

class PlanerQuad: public Shape{
public:

    PlanerQuad(){};
	PlanerQuad(Vec3f point1, Vec3f point2, Vec3f point3, Vec3f point4){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
        point[3] = point4;

        norm  = (point2- point1).crossProduct(point3-point1).normalize();
    }
	PlanerQuad(Vec3f point1, Vec3f point2, Vec3f point3, Vec3f point4, Material* m):Shape(m){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
        point[3] = point4;

        norm  = (point2- point1).crossProduct(point3-point1).normalize();
    }
    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

    ~PlanerQuad(){}

private:
    Vec3f point[4];
    //cross product of (point1 - point2) and (point2 - point3)
    Vec3f norm;
};

} //namespace rt

#endif /* PLANERQUAD_H_ */
