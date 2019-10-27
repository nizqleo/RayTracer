/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"

namespace rt{

class AreaLight:public LightSource{
public:
    AreaLight(){}
    AreaLight(Vec3f inten):LightSource(inten){}

private:

};



} //namespace rt




#endif /* AREALIGHT_H_ */
