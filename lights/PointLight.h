/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"


namespace rt{

class PointLight: public LightSource{
public:
    PointLight(){}
    PointLight(Vec3f posi, Vec3f inten):LightSource(inten),position(posi){}
    Vec3f getPosition(){
        return position;
    }
private:
    Vec3f position;

};



} //namespace rt




#endif /* POINTLIGHT_H_ */
