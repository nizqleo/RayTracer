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

    /** The Blinn-Phong reflection model
     * 
     *  L:from point to light
     *  N:norm at the point
     *  V:from point to eye 
     **/
    Vec3f computeBPReflection(Vec3f intensity, Vec3f L, Vec3f N, Vec3f V);

    /** The Blinn-Phong reflection model with texture
     * 
     **/
    Vec3f computeBPTReflection(Vec3f intensity, Vec3f L, Vec3f N, Vec3f V, float u, float v);

    bool isTexture;

//private:
    float ks;
    float kd;
    int specularexponent;
    Vec3f diffusecolor;
    Vec3f* textureImage;
    int width;
    int height;
    Vec2f uv[4];
};


} //namespace rt



#endif /* MATERIAL_H_ */
