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

Vec3f RayTracer::TracePath(Scene* scene, Ray ray, int nbounces_left){
	if(nbounces_left < 0) return Vec3f(0,0,0);
	std::pair<Shape*, Hit> hitEvent = scene->find_first_hit(ray);

	if(hitEvent.first == NULL)// didn't hit any thing.
		return scene->bgcolor;
	
	std::cout<<"hit"<<std::endl;
	Material* material = hitEvent.first->getMaterial();
	
	// emittance
	Vec3f color;

	for(std::vector<LightSource*>::iterator p = scene->lightSources.begin(); p != scene->lightSources.end(); p++){
		// point light processing 
		if((*p)->isPointLight() ){
			color += material->computeBPReflection((*p)->intensity, (*p)->getPosition()-hitEvent.second.point, hitEvent.second.normVector, -ray.direction);
		}
	}

	const double p = 1/(2*M_PI);
	for(int sample_num = 0; sample_num < RayTracer::path_sample_num; sample_num++){
		Ray newray(hitEvent.second.point);

		Vec3f enviromentIncoming = RayTracer::TracePath(scene, newray, nbounces_left-1);
		
		color += material->computeBPReflection(enviromentIncoming, newray.direction, hitEvent.second.normVector, -ray.direction);
	}

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

	// std::cout<<"0 0"<<camera->generate_ray(0, 0).direction<<std::endl;
	// std::cout<<"0 400"<<camera->generate_ray(0, 400).direction<<std::endl;
	
	// std::cout<<"400 0"<<camera->generate_ray(400, 0).direction<<std::endl;
	
	// std::cout<<"400 400"<<camera->generate_ray(400, 400).direction<<std::endl;
	
	
	for(int i = 0; i < camera->getHeight(); i++){
		for(int j = 0; j < camera->getWidth(); j++){
			// for every pixel in the image, do.
			Vec3f pixel_color;
			for(int round = 0; round < RayTracer::pixel_sample_num; round++){
				Ray ray = camera->generate_ray(i, j);
				pixel_color= RayTracer::TracePath(scene, ray, nbounces-1);
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

	for(int i = 0; i < size; i++){
		pixelbuffer[i] *= 255;
	}
	return pixelbuffer;
}

} //namespace rt


