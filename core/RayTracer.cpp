/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"


namespace rt{

Vec3f RayTracer::TracePath(Scene* scene, Ray ray, int nbounces_left){
	std::pair<Shape*, Hit> hitEvent = scene->find_first_hit(ray);

	Material* material = hitEvent.first->getMaterial();

	// emittance

	Vec3f color;

	for(std::vector<LightSource*>::iterator p = scene->lightSources.begin(); p != scene->lightSources.end(); p++){
		// point light processing 
		if((*p)->type == POINTLIGHT){

			float cos_theta = ((*p)->position-hitEvent.second.point).dotProduct(ray.direction);

			color += (material->getBRDF() *(*p)->color * cos_theta);
		}
	}

	const float p = 1/(2*3.14);
	for(int sample_num = 0; sample_num < RayTracer::Max_sample_num; sample_num++){
		Ray newray(hitEvent.second.point);

		Vec3f incoming = RayTracer::TracePath(scene, newray, nbounces_left-1);
		float cos_theta = newray.direction.dotProduct(ray.direction);
		color += (material->getBRDF() * incoming * cos_theta / p);
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
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces, int pixel_sample_num = 1){
	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

	//----------main rendering function to be filled------

	for(int i = 0; i < camera->getWidth(); i++){
		for(int j = 0; j < camera->getWidth(); j++){
			// for every pixel in the image, do.
			Vec3f pixel_color;
			for(int round = 0; round < pixel_sample_num; round++){
				Ray ray = camera->generate_ray(i, j);
				pixel_color= RayTracer::TracePath(scene, ray, nbounces-1);
			}

			pixelbuffer[i*camera->getWidth() + j] = pixel_color/pixel_sample_num;
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
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------


	return pixelbuffer;

}

} //namespace rt


