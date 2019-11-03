/*
 * PPMWriter.h
 *
 */
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PPMWRITER_H_
#define PPMWRITER_H_

#include <iostream>
#include <fstream>
#include "math/geometry.h"


namespace PPMWriter{

	template<typename T>
	void PPMWriter(const int width,const int height,Vec3<T>* framebuffer, const char* filename){

		std::ofstream ofs(filename, std::ios::out | std::ios::binary);
		ofs << "P6\n" << width << " " << height << "\n255\n";
		for (uint32_t i = 0; i < height * width; ++i) {
			char r = (char)(framebuffer[i].x);
			char g = (char)(framebuffer[i].y);
			char b = (char)(framebuffer[i].z);
			ofs << r << g << b;
		}
		ofs.close();
	}


	template<typename T>
	void PPMReader(int& width, int& height,Vec3<T>*& framebuffer, const char* filename){

		std::ifstream ifs(filename, std::ios::out | std::ios::binary);
		char s[100];
		ifs.getline(s,100);
		ifs >> width >> height;
        std::cout<<width<<' '<<height<<std::endl;

		float upbound;
		ifs >> upbound;

		framebuffer = new Vec3<T>[width * height];
		for (uint32_t i = 0; i < height * width; ++i) {
			int r,g,b;
			ifs >> r >> g >> b;
			framebuffer[i].x = (T)(r*1.0/upbound);
			framebuffer[i].y = (T)(g*1.0/upbound);
			framebuffer[i].z = (T)(b*1.0/upbound);
		}
		ifs.close();
	}
};



#endif /* PMMWRITER_H_ */
