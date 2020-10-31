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
    /*
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
    
    */
    vec3 l;
    vec3 right;
    vec3 color = color_ambient*world.ambient_color*world.ambient_intensity;	
    for(size_t i = 0; i < world.lights.size(); i++){
 	l = world.lights.at(i)->position - intersection_point;
	if(world.enable_shadows){		
		Ray ray_1(intersection_point, l);
		Hit shadow_hit = {};
		if(world.Closest_Intersection(ray_1, shadow_hit)){
			if(shadow_hit.t < l.magnitude())
				continue;
		}
		   
	}
	right = (2*dot(l,normal) * normal - l).normalized();
	vec3 l_color = world.lights.at(i)->Emitted_Light(l.normalized())/(l.magnitude_squared());
	double diffuse_intensity = std::max(0.0, dot(l.normalized(),normal));
	double spec_intensity = pow(std::max(0.0,dot(right,(ray.endpoint - intersection_point).normalized())),specular_power);
	color = l_color * (color_diffuse * diffuse_intensity + color_specular * spec_intensity) + color;
	/* 
	vec3 diffuse = color_diffuse*world.lights[i]->Emitted_Light(l)*(std::max(dot(normal,l.normalized()),0.0));
	right = (2*(dot(l,normal))*normal - l).normalized();
	vec3 specular = color_specular*world.lights[i]->Emitted_Light(l)*(std::max(std::pow(dot(-ray.direction,right.normalized()),specular_power),0.0));
	if(dot(-ray.direction, right.normalized()) < 0){
		color += diffuse;
	}else{
		color += diffuse;
		color += specular;
	}
        */

    }
    
    /* 
    vec3 color = color_ambient*world.ambient_color*world.ambient_intensity; 
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
    */
     //determine the color
    
    
    return color;
}
