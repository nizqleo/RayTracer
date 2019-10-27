/*
 * Scene.cpp
 *
 */
#include "Scene.h"




namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------

}

std::pair<Shape*, Hit> Scene::find_first_hit(Ray ray){
	float min_dis = INT32_MAX;
	Shape* min_shape = NULL;
	Hit closestHit;
	for(std::vector<Shape*>::iterator p = shapes.begin(); p != shapes.end(); p++){
		Hit hit = (*p)->intersect(ray);
		if(hit.exist != false){
			float distance = (ray.OriginalPoint-hit.point).length();
			if(distance < min_dis){
				min_dis = distance;
				min_shape = *p;
				closestHit = hit;
			}
		}		
	}
	if( min_shape != NULL ){
		return std::make_pair(min_shape, closestHit);
	}
}

} //namespace rt
