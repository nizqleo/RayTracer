/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/BVH.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/PlanerQuad.h"
#include "shapes/TriMesh.h"


namespace rt{

Shape::Shape(Material* m){
	material = m;
}

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
	}
	else if (shapeType.compare("Triangle")==0){
		return new Triangle(Vec3f(shapeSpecs["point1"].GetArray()),
				Vec3f(shapeSpecs["point2"].GetArray()),
                Vec3f(shapeSpecs["point3"].GetArray()),
				m);
	}
	else if (shapeType.compare("PlanerQuad")==0){
		return new PlanerQuad(Vec3f(shapeSpecs["point1"].GetArray()),
				Vec3f(shapeSpecs["point2"].GetArray()),
                Vec3f(shapeSpecs["point3"].GetArray()),
				Vec3f(shapeSpecs["point4"].GetArray()),
				m);
	}

    std::cerr<<"shape creating failed.\n";
	return NULL;
}

	Vec3f Shape::computeReflection(Vec3f incomingIntensity, Vec3f L, Vec3f V, Hit hit){
		Vec3f N = hit.normVector;
		if(material->isTexture == true){
			Vec2f uv = this->uvCompute(hit.point);
			return material->computeBPTReflection(incomingIntensity, L, N, V, uv.x, uv.y);
		}
		else
			return material->computeBPReflection(incomingIntensity, L, N, V);
	}


} //namespace rt

