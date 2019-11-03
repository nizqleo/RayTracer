/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "rapidjson/document.h"
#include "core/RayHitStructs.h"
#include "core/Material.h"

using namespace rapidjson;

namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape();
	Shape(Material* m);
	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape(){
		if (material != NULL)
			delete material;
	}

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray)=0;

	// getter
    static Shape* createShape(Value& shapeSpecs);

	Material* getMaterial(){
		return material;
	}
protected:

	Material * material;

};


} //namespace rt


#endif /* SHAPE_H_ */
