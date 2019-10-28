/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"


using namespace rt;
using namespace rapidjson;

int main(int argc, char* argv[]){

	//parse commandline arguments
	char* inputFile=argv[1];    //first command line argument holds the path to the json input file
	char* outputFile=argv[2];   //second command line argument holds the path to the output image file

	std::printf("Input file: %s\n",inputFile);

	//parse json input file using rapidjson
	std::ifstream ifs(inputFile);
	IStreamWrapper is(ifs);
	Document d;     // d holds the complete json object
	d.ParseStream(is);

	//generate a camera according to the input file
	Camera* camera=Camera::createCamera(d["camera"]);
	
	//print camera data (based on the input file provided)
	camera->printCamera();

	//generate the scene according to the input file
	Scene* scene=new Scene();
	scene->createScene(d["scene"]);
	scene->printScene();

	// render parameters
	RayTracer::path_sample_num = d["path_sample_num"].GetInt();
	RayTracer::pixel_sample_num = d["pixel_sample_num"].GetInt();
	//
	// Main function, render scene
	//
	std::cout<<"rendering...\n";
	Vec3f* pixelbuffer=RayTracer::render(camera, scene, d["nbounces"].GetInt());
	std::cout<<"rendering finish.\n";


	//convert linear RGB pixel values [0-1] to range 0-255
	Vec3f* pixel_mapped_buffer = RayTracer::tonemap(pixelbuffer, camera->getWidth() * camera->getHeight());


	std::printf("Output file: %s\n",outputFile);

	//write rendered scene to file (pixels RGB values must be in range 0255)
	PPMWriter::PPMWriter(camera->getWidth(), camera->getHeight(), pixel_mapped_buffer, outputFile);


	//free resources when rendering is finished
	delete camera;
	delete scene;
	delete pixelbuffer;
}


