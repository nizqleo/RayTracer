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

        v1 = point[2] - point[0];
        d11 = v1.dotProduct(v1);
        // 0,1,2 and 0,3,2
        v0[0] = point[1] - point[0];v0[1]=point[3] - point[0];
        d00[0] = v0[0].dotProduct(v0[0]);d00[1] = v0[1].dotProduct(v0[1]);
        d01[0] = v0[0].dotProduct(v1);d01[1] = v0[1].dotProduct(v1);
        norm  = (point2- point1).crossProduct(point4-point1).normalize();
    }
	PlanerQuad(Vec3f point1, Vec3f point2, Vec3f point3, Vec3f point4, Material* m, Vec3f e):Shape(m,e){
        point[0] = point1;
        point[1] = point2;
        point[2] = point3;
        point[3] = point4;

        v1 = point[2] - point[0];
        d11 = v1.dotProduct(v1);
        // 0,1,2 and 0,3,2
        v0[0] = point[1] - point[0];v0[1]=point[3] - point[0];
        d00[0] = v0[0].dotProduct(v0[0]);d00[1] = v0[1].dotProduct(v0[1]);
        d01[0] = v0[0].dotProduct(v1);d01[1] = v0[1].dotProduct(v1);
        norm  = (point2- point1).crossProduct(point4-point1).normalize();
    }
    //
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

	Vec2f uvCompute(Vec3f point);

    ~PlanerQuad(){}

private:
    Vec3f point[4];

    // comprised of two triangles:
    // 0,1,2 and 0,3,2
    // parameters used in texture mapping
    Vec3f v0[2];// = point[1] - point[0];
    Vec3f v1;// = point[2] - point[0];
    float d00[2];// = Dot(v0, v0);
    float d01[2];// = Dot(v0, v1);
    float d11;// = Dot(v1, v1);

    //cross product of (point1 - point2) and (point2 - point3)
    Vec3f norm;
};

} //namespace rt

#endif /* PLANERQUAD_H_ */
