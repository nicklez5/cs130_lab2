#include "flat_shader.h"

vec3 Flat_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    if(debug_pixel){
    	std::cout << "call Shade_Surface with: location = " << intersection_point << "; normal = " << normal << std::endl;
	std::cout << "flat shader; color = " << color << std::endl;
    }
    return this->color;
}
