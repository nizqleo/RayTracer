/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

namespace rt{

class Material{
public:
    Vec3f getBRDF(){
        return Vec3f(1,1,1);
    }

private:
};


} //namespace rt



#endif /* MATERIAL_H_ */
