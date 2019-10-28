/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/BVH.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"


namespace rt{

Shape* Shape::createShape(Value& shapeSpecs){
    
    // type
    if (!shapeSpecs.HasMember("type")){
		std::cerr<<"Shape type not specified"<<std::endl;
		exit(-1);
	}
	std::string shapeType=shapeSpecs["type"].GetString();

    // material
    if (!shapeSpecs.HasMember("material")){
		std::cerr<<"Shape material not specified"<<std::endl;
		exit(-1);
	}

	Material* m = new Material(shapeSpecs["material"]);
	
	//return shape object based on shape specs
	if (shapeType.compare("sphere")==0){
		return new Sphere(Vec3f(shapeSpecs["center"].GetArray()),
				shapeSpecs["radius"].GetFloat(),
				m);

	}else if (shapeType.compare("Traingle")==0){
		return new Triangle(Vec3f(shapeSpecs["point1"].GetArray()),
				Vec3f(shapeSpecs["point2"].GetArray()),
                Vec3f(shapeSpecs["point3"].GetArray()),
				m);
	}

    std::cerr<<"shape creating failed.\n";
	return NULL;
}



} //namespace rt

