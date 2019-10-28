/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt{

class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);
	
	/* go through all the shape in the scene and sort by the distance.
	 * find the one with smallest distance.
	 */ 
	std::pair<Shape*, Hit> find_first_hit(Ray ray);

	void printScene();


	// getters
	std::vector<LightSource*>::iterator getlightSourceBegin(){return lightSources.begin();}
	std::vector<LightSource*>::iterator getlightSourceEnd(){return lightSources.end();}
	
	friend class RayTracer;

private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;

	Vec3f bgcolor;

};

} //namespace rt



#endif /* SCENE_H_ */
