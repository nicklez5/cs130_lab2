#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    if(debug_pixel){
	std::cout << "call Shade_Surface with: location = " << intersection_point << "; normal = " << normal << std::endl;
    }
    vec3 reflected_ray_vec = (ray.direction - (2 * dot(ray.direction, normal) * normal));
    Ray reflect_ray(intersection_point, reflected_ray_vec);
    vec3 reflect_color = world.Cast_Ray(reflect_ray, ++recursion_depth);
    vec3 shade_color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth); 
    vec3 color = (reflectivity* reflect_color + (1-reflectivity)*shade_color);
     // determine the color
    return color;
}
