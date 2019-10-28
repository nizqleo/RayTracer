/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "rapidjson/document.h"
#include "math/geometry.h"


using namespace rapidjson;

namespace rt{

enum LightType {POINTLIGHT, SHAPELIGHT};
class LightSource{
public:
    LightType type;

    LightSource(){}
    LightSource(Vec3f inten):intensity(inten){}

    static LightSource* createLightSource(Value& lightsourceSpecs);
    
    virtual Vec3f getPosition(){
        return Vec3f(0,0,0);
    }

    virtual bool isPointLight(){
        return false;
    }

    friend class RayTracer;


private:
    Vec3f intensity;
};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
