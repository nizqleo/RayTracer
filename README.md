# RayTracer

---

The Ray Tracer can be divided into several part based on the set up UML structure: camera, light source, material, scene, shape, and ray tracer.

![final](/build/final.jpg)



### Camera

In ray tracing, we need to implement the camera as a ray generator for every pixel in the final image. There are two types of cameras: pinhole and thin-lens. Each Pixel of pinhole camera generate one ray from a fixed point towards pixel points on a close plane in front of it, while the thin-lens camera's pixels received multiple rays came through the aperture circle. To simulate thin-lens camera, I introduced randomness in ray generating to create the defocus blur.

![final](/build/pinhole_pointlight.jpg)
![final](/build/thinlens.jpg)



### Light Source

There are two types of light source, the point light and area light. In the idea of Path Tracing, it is impossible for a randomly generated ray to hit a certain point in the space. So I added a special step in sampling, going through all the point light source and check if their light cast on the goal point. As for the area light, I implemented it as "light emitting shapes", and rely on the random path tracing to light up the scene. The result is much darker than the one with pinhole, so I increased the scale in tone mapping to get images like \ref{Fig2.sub.2}.


![final](/build/pinhole_pointlight.jpg)
![final](/build/arealight.jpg)

### Material

The compute of reflection color is done in the material class. For every material object, it contains parameters of kd, ks, diffuse-color and specular-exponent, which is the parameters that are need to implementer a Blinn-Phong reflection model. 

Texture mapping is also done by material objects. The only difference between texture and single color diffusing is that for every point on a shape, we look for the corresponding pixel in the texture image. The mapping process is done based on the shape and we gonna talk about that in the shape section.


### Shape

Shapes are the main objects in a scene, and they provide the geometry result of intersect or texture mapping.
I implemented spheres, triangles and planer quad.

There are mainly two tasks that needs to be implemented in shapes, one is intersect computing, and the other is texture mapping.
For intersecting, I just implemented the geometry computing, specially, I used the Moller-Trumbore's algorithm to compute the ray-triangle intersecting.
As for texture mapping, I linearly mapped the points on spheres to the texture image based on their Euler angles. And as for triangles, I used the Barycentric Coordinates of a point as the weight when sum up the three UV coordinates of the vertices. 

And the planer quad is basically implemented as two triangles.

### Ray Tracer

For every pixel, the ray tracer use the camera model to generate a ray, and then call the TracePath function to get the color that will be seen by the ray. The TracePath function is a recursive function and when it hit a point it will generate a random ray from that point to a random direction, in order to get the environment information. The first hit of a ray is found by the scene object, who go through all its shapes and search for one with closed intersect point.




