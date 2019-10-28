/*
 * Material.cpp
 *
 */
#include "Material.h"


namespace rt{

Material::Material(Value& materialSpecs){
    ks = materialSpecs["ks"].GetFloat();
    kd = materialSpecs["kd"].GetFloat();
    specularexponent = materialSpecs["specularexponent"].GetInt();
    diffusecolor = Vec3f(materialSpecs["diffusecolor"].GetArray());
}

Vec3f Material::computeBPReflection(Vec3f intensity, Vec3f L, Vec3f N, Vec3f V){
    //diffuse factor
    Vec3f color = (diffusecolor*intensity)*(kd*L.dotProduct(N));
    //specular factor
    color += ks*pow(N.dotProduct((L+V)/(L+V).length()), specularexponent)*intensity;
    return color;
}

} //namespace rt


