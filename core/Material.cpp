/*
 * Material.cpp
 *
 */
#include "Material.h"


namespace rt{

Material::Material(Value& materialSpecs){
    ks = materialSpecs["kd"].GetFloat();
    kd = materialSpecs["ks"].GetFloat();
    specularexponent = materialSpecs["specularexponent"].GetInt();
    diffusecolor = Vec3f(materialSpecs["diffusecolor"].GetArray());
}



} //namespace rt


