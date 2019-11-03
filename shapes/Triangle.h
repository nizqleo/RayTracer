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
        TriPoint[0] = point1;
        TriPoint[1] = point2;
        TriPoint[2] = point3;
        v0 = TriPoint[1] - TriPoint[0];
        v1 = TriPoint[2] - TriPoint[0];
        d00 = v0.dotProduct(v0);
        d01 = v0.dotProduct(v1);
        d11 = v1.dotProduct(v1);
        norm  = (point2-point1).crossProduct(point3-point1).normalize();
    }
	Triangle(Vec3f point1, Vec3f point2, Vec3f point3, Material* m):Shape(m){
        TriPoint[0] = point1;
        TriPoint[1] = point2;
        TriPoint[2] = point3;
        v0 = TriPoint[1] - TriPoint[0];
        v1 = TriPoint[2] - TriPoint[0];
        area = (v0.crossProduct(v1)).length();
        d00 = v0.dotProduct(v0);
        d01 = v0.dotProduct(v1);
        d11 = v1.dotProduct(v1);
        norm  = (point2-point1).crossProduct(point3-point1).normalize(); 
    }

    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);
	Vec2f uvCompute(Vec3f point);

    ~Triangle(){}
private:
    // A, B, C
    Vec3f TriPoint[3];

    // parameters used in texture mapping
    Vec3f v0;// = point[1] - point[0];
    Vec3f v1;// = point[2] - point[0];
    float area;
    float d00;// = Dot(v0, v0);
    float d01;// = Dot(v0, v1);
    float d11;// = Dot(v1, v1);

    //cross product of (point1 - point2) and (point3 - point1)
    Vec3f norm;
};



} //namespace rt




#endif /* TRIANGLE_H_ */
