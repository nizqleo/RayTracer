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
        edge[0] = point2-point1;
        edge[1] = point3-point1;
        norm  = (edge[0]).crossProduct(edge[1]).normalize();
    };
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3, Material* m):Shape(m){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
        edge[0] = point2-point1;
        edge[1] = point3-point1;
        norm  = (edge[0]).crossProduct(edge[1]).normalize();   
    };

    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

    void exchange(){
        Vec3f temp = point[1]; point[1] = point[2]; point[2]=temp;
        temp = edge[0]; edge[0]=edge[1]; edge[1] = temp;
    }
    ~Triangle(){}

private:
    // A, B, C
    Vec3f point[3];
    // room-time trade-off: 1-0, 2-0
    Vec3f edge[2];
    //cross product of (point1 - point2) and (point2 - point3)
    Vec3f norm;
};



} //namespace rt




#endif /* TRIANGLE_H_ */
