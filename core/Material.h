/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "rapidjson/document.h"
#include "math/geometry.h"

using namespace rapidjson;

namespace rt{

class Material{
public:

    Material(){}
    Material(Value& materialSpecs);
    Material(Material& m){
        ks = m.ks;
        kd = m.kd;
        specularexponent = m.specularexponent;
        diffusecolor = m.diffusecolor;
    }
    Vec3f getBRDF(){
        return Vec3f(1,1,1);
    }

private:
    float ks;
    float kd;
    int specularexponent;
    Vec3f diffusecolor;
};


} //namespace rt



#endif /* MATERIAL_H_ */
