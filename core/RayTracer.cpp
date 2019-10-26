/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"


namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces, int max_pixel_sample_num = 1){
	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

	//----------main rendering function to be filled------

	for(int i = 0; i < camera->getWidth(); i++){
		for(int j = 0; j < camera->getWidth(); j++){
			// for every pixel in the image, do..
			for(int num_pixel_sample = 0; num_pixel_sample < max_pixel_sample_num; num_pixel_sample++){
				Ray ray = camera->generate_ray(i, j);

				Vec3f pixel_color(0,0,0)= PayTracer::TracePath(newray, nbounces-1);
			}

			pixelbuffer[i][j] = pixel_color/max_pixel_sample_num;
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


Vec3f* TracePath(Scene* scene, int nbounces_left){
	Hit hit = scene->find_first_hit(ray);

	Shape* obj = hit.objHited;

	Material material = obj->material;
	// emittance

	Vec3f color;

	
	for(auto p = scene.lightSources.begin(); p!=scene.lightSources.begin(); p++){
		// point light processing 
		if(p->type){
			cos_theta = DotProduct(lightdirection, ray.normalWhereObjWasHit);

			color += (BRDF * lightcolor * cos_theta)
		}
	}

	const float p = 1/(2*3.14);
	for(int sample_num = 0; sample_num < Max_sample_num; sample_num++){
		Ray newray(hit->point);

		Vec3f incoming = PayTracer::TracePath(newray, nbounces-1);
		float cos_theta = DotProduct(newRay.direction, ray.normalWhereObjWasHit);
		Vec3f BRDF = material.reflectance / M_PI ;
		color += (BRDF * incoming * cos_theta / p)
	}

	return color;// + emittence
}


} //namespace rt


