/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


namespace rt{

enum LightType {POINTLIGHT, SHAPELIGHT};
class LightSource{
public:
    LightType type;
    friend class RayTracer;
private:
    Vec3f color;
    Vec3f position;
};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
