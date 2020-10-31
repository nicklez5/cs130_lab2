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
    vec3 light_dest;
    vec3 right_dest;
    vec3 shadow_dest;
    vec3 color = color_ambient * world.ambient_color * world.ambient_intensity;
    if(world.enable_shadows){
	for(Light* da_light: world.lights){
		light_dest = da_light->position - intersection_point;
		Ray shadow_ray(intersection_point, light_dest);
		Hit shadow_hit = {};
		 world.Closest_Intersection(shadow_ray,shadow_hit);
		if(shadow_hit.t > 0){
			shadow_dest = shadow_ray.Point(shadow_hit.t)- intersection_point;
		}	
		if(!shadow_hit.object || shadow_dest.magnitude() > light_dest.magnitude()){
			color += color_diffuse*da_light->Emitted_Light(light_dest)*(std::max(dot(normal,light_dest.normalized()),0.0));
			right_dest = -light_dest + 2*(dot(light_dest,normal))*normal;
			color += color_specular*da_light->Emitted_Light(light_dest)*std::pow(std::max(dot(-ray.direction, right_dest.normalized()),0.0),specular_power);
		}
	}
    }else{
	for(Light* da_light: world.lights){
		light_dest = da_light->position - intersection_point;
		color += color_diffuse*da_light->Emitted_Light(light_dest)*(std::max(dot(normal,light_dest.normalized()),0.0));
		right_dest = -light_dest + 2*(dot(light_dest,normal))*normal;
		color += color_specular*da_light->Emitted_Light(light_dest)*std::pow(std::max(dot(-ray.direction,right_dest.normalized()),0.0),specular_power); 
	}
    }
    
    /*
    for(size_t xyz = 0; xyz < world.lights.size(); xyz++){
	Ray ray_1(intersection_point, world.lights[xyz]->position.normalized());
	vec3 light;
	light = world.lights[xyz]->position - intersection_point;
	vec3 l_color = world.lights[xyz]->Emitted_Light(light.normalized()) / light.magnitude_squared();
	if(world.enable_shadows){
		Hit hit = {};
		world.Closest_Intersection(ray_1,hit);
		if(hit.object != NULL && hit.t < light.magnitude_squared()){
			continue;
		}
	}
	vec3 diffuse_me = color_diffuse*l_color*std::max(dot(normal,light.normalized()),0.0);
	vec3 r = (2*dot(light.normalized(), normal)*normal - light.normalized());
	vec3 spec = color_specular*l_color*std::pow(std::max(dot(r,-ray_1.direction.normalized()),0.0),specular_power);
	color += diffuse_me+spec;
    }
     //determine the color
    */
    return color;
}
