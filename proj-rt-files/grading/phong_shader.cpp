#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>
#include <cmath>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    
   
    vec3 color = color_ambient*world.ambient_color*world.ambient_intensity;
    vec3 l, right;
    vec3 direction_light;    
    for(size_t i = 0; i < world.lights.size(); i++){
 	l = world.lights.at(i)->position - intersection_point;
	if(world.enable_shadows){		
		Ray ray_1(intersection_point, l);
		Hit shadow_hit = {};
		Object* xyz = world.Closest_Intersection(ray_1, shadow_hit);
		if(xyz != NULL && shadow_hit.t < l.magnitude()){
			continue;
			
		}
		   
	}
	right = ((2*dot(l,normal) * normal) - l).normalized();
	vec3 l_color = world.lights.at(i)->Emitted_Light(l);
	
	vec3 diffuse_color = l_color * color_diffuse * std::max(dot(normal, l.normalized()),0.0);
	vec3 spec_color = l_color* color_specular * pow(std::max(dot(-ray.direction,right),0.0),specular_power);
	color += diffuse_color + spec_color;
	
	

    }
    
    
     //determine the color
    
    
    return color;
}
