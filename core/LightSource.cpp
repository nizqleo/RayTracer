/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "lights/PointLight.h"
#include "lights/AreaLight.h"

namespace rt{

LightSource* LightSource::createLightSource(Value& lightsourceSpecs){
        // type
    if (!lightsourceSpecs.HasMember("type")){
		std::cerr<<"lightsource type not specified"<<std::endl;
		exit(-1);
	}
	std::string lightsourceType=lightsourceSpecs["type"].GetString();

	//return lightsource object based on lightsource specs
	if (lightsourceType.compare("pointlight")==0){
		return new PointLight(Vec3f(lightsourceSpecs["position"].GetArray()),
				Vec3f(lightsourceSpecs["intensity"].GetArray()));

	}else if (lightsourceType.compare("arealight")==0){
		return new AreaLight(Vec3f(lightsourceSpecs["intensity"].GetArray()));
	}
    std::cerr<<"lightsource creating failed.\n";
	return NULL;
}




} //namespace rt

