/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include "lights/PointLight.h"
#include "lights/AreaLight.h"

namespace rt{
int RayTracer::path_sample_num;
int RayTracer::pixel_sample_num;
int RayTracer::useRandom;
int RayTracer::scale;


Vec3f RayTracer::TracePath(Scene* scene, Ray ray, int nbounces_left, Shape* startfrom){
	
	if(nbounces_left < 0)
		return Vec3f(0,0,0);

	std::pair<Shape*, Hit> hitEvent = scene->find_first_hit(ray, startfrom);

	if(hitEvent.first == NULL){// didn't hit any thing.
		//std::cout<<"escape "<<ray.OriginalPoint<<' '<<ray.direction<<' '<<nbounces_left<<' '<<startfrom<<std::endl;
		//return Vec3f(0,0,0);
		return scene->bgcolor;
	}
	
	Vec3f color= hitEvent.first->emittence;
	//std::cout<<hitEvent.second.point<<' '<<color<<std::endl;
	for(std::vector<LightSource*>::iterator p = scene->lightSources.begin(); p != scene->lightSources.end(); p++){
		// point light processing 
		if((*p)->isPointLight() && scene->shadowCheck(*p, hitEvent)){
			color += hitEvent.first->computeReflection((*p)->intensity, ((*p)->getPosition()-hitEvent.second.point).normalize(), -ray.direction, hitEvent.second);
			//color += material->computeBPReflection((*p)->intensity, ((*p)->getPosition()-hitEvent.second.point).normalize(), hitEvent.second.normVector, -ray.direction);
		}
	}
	//std::cout<<"pl"<<std::endl;
	if(nbounces_left==0)
		return color;

	Vec3f sampleColor;
	const double p = 1/(2*M_PI);
	if(RayTracer::useRandom == 1){
		for(int sample_num = 0; sample_num < RayTracer::path_sample_num; sample_num++){
			Ray newray(hitEvent.second);
			//std::cout<<"rand"<<newray.OriginalPoint<<' '<<newray.direction<<std::endl;
			Vec3f enviromentIncoming = RayTracer::TracePath(scene, newray, nbounces_left-1, hitEvent.first);
			sampleColor += hitEvent.first->computeReflection(enviromentIncoming, newray.direction, -ray.direction, hitEvent.second)/p;		
			//color += material->computeBPReflection(enviromentIncoming, newray.direction, hitEvent.second.normVector, -ray.direction) *p;
		}
		sampleColor/=RayTracer::path_sample_num;
	}
	else{
		int round = sqrt(RayTracer::path_sample_num);
		float alpha_unit = 2*M_PI/(round+1);
		float beta_unit = M_PI/(2*round-2);
		for(float alpha = 0; alpha < 2*M_PI; alpha+=alpha_unit){
			for(float beta = 0; beta < 2*M_PI; beta+=beta_unit){
				Vec3f dire(cos(beta)*sin(alpha), cos(beta)*cos(alpha), sin(beta));
				if(dire.dotProduct(hitEvent.second.normVector) < 0)
					dire = -dire;
				Ray newray(hitEvent.second.point, dire.normalize());
				//std::cout<<"rand"<<newray.OriginalPoint<<' '<<newray.direction<<std::endl;
				Vec3f enviromentIncoming = RayTracer::TracePath(scene, newray, nbounces_left-1, hitEvent.first);
				sampleColor += hitEvent.first->computeReflection(enviromentIncoming, newray.direction, -ray.direction, hitEvent.second)/p;		
			}
		}
	}

	//std::cout<<"tracepath"<<std::endl;
	color+=sampleColor;

	return color;// + emittence
}

/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){
	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

	for(int i = 0; i < camera->getHeight(); i++){
		for(int j = 0; j < camera->getWidth(); j++){
			// for every pixel in the image, do.
			//std::cout<<i<<' '<<j<<' ';
			Vec3f pixel_color;
			for(int round = 0; round < RayTracer::pixel_sample_num; round++){
				Ray ray = camera->generate_ray(i, j);
				pixel_color += RayTracer::TracePath(scene, ray, nbounces-1, NULL);
			}
			pixelbuffer[i*camera->getWidth() + j] = pixel_color/RayTracer::pixel_sample_num;
		}
	}
	return pixelbuffer;

}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, int size){
	std::cout<<"scale: "<<RayTracer::scale<<std::endl;
	for(int i = 0; i < size; i++){
		pixelbuffer[i] *= RayTracer::scale;
		pixelbuffer[i].clamp(255);
	}
	return pixelbuffer;
}

} //namespace rt


