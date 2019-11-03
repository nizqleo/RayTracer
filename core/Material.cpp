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
    
    float diffuseValue =L.dotProduct(N);
    float specularValue = N.dotProduct((L+V).normalize());
    if(diffuseValue < 0) diffuseValue = 0;
    if(specularValue < 0) specularValue = 0;

    //diffuse factor
    Vec3f color = (diffusecolor*intensity)*(kd*diffuseValue);
    //std::cout<<color<<' ';
    //specular factor
    color += ks*pow(specularValue, specularexponent)*intensity;
    //std::cout<<color<<std::endl;


    return color;
}

} //namespace rt


