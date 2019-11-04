/*
 * Material.cpp
 *
 */
#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "parsers/PPMWriter.h"
//#include "parsers/PPMWriter.h"
#include "Material.h"

namespace rt{

Material::Material(Value& materialSpecs){
    ks = materialSpecs["ks"].GetFloat();
    kd = materialSpecs["kd"].GetFloat();
    specularexponent = materialSpecs["specularexponent"].GetInt();
    if(materialSpecs.HasMember("texture")){
        isTexture = true;
        PPMWriter::PPMReader(width, height, textureImage, materialSpecs["texture"].GetString());
        if(materialSpecs.HasMember("uv1")){
            uv[0] = Vec2f(materialSpecs["uv1"].GetArray());
            uv[1] = Vec2f(materialSpecs["uv2"].GetArray());
            uv[2] = Vec2f(materialSpecs["uv3"].GetArray());
        }
        if(materialSpecs.HasMember("uv4"))
            uv[3] = Vec2f(materialSpecs["uv4"].GetArray());
        std::cout<<"finish loading texture file "<<materialSpecs["texture"].GetString()<<" with size: w:"<<width<<" h:"<<height<<std::endl;
    }
    else{
        diffusecolor = Vec3f(materialSpecs["diffusecolor"].GetArray());
    }
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


Vec3f Material::computeBPTReflection(Vec3f intensity, Vec3f L, Vec3f N, Vec3f V, float u, float v){
    int u_row, v_col;
    if(u < 1){
        u_row = int(u*height);
        v_col = int(v*width);
    }
    else{
        u_row = int(u);
        v_col = int(v);
    }
    //std::cout<<u_row<<' '<<v_col<<std::endl;
    float diffuseValue =L.dotProduct(N);
    float specularValue = N.dotProduct((L+V).normalize());
    if(diffuseValue < 0) diffuseValue = 0;
    if(specularValue < 0) specularValue = 0;

    //diffuse factor
    //Vec3f color = (Vec3f(textureImage.at<cv::Vec3b>(u,v))*intensity)*(kd*diffuseValue);
    Vec3f color = (textureImage[u_row*width+v_col]*intensity)*(kd*diffuseValue);
    
    //std::cout<<color<<' ';
    //specular factor
    color += ks*pow(specularValue, specularexponent)*intensity;
    //std::cout<<color<<std::endl;


    return color;
}
} //namespace rt


