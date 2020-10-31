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
	

    }
    
    
     //determine the color
    
    
    return color;
}
