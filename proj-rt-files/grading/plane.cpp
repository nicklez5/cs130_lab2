#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
void Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{	
    
    if(dot(ray.direction, normal) == 0){
		vec3 lhs = x1 - ray.endpoint;
		if(dot(lhs,normal) == 0){
			Hit new_hit3;
			new_hit3.object = this; 
			new_hit3.t = 0;
			new_hit3.location = ray.endpoint;
			new_hit3.ray_exiting = false;
			hits.push_back(new_hit3);
		}
    }else{
	vec3 left_side = x1 - ray.endpoint;
	double top_dot = dot(left_side,normal);
	double bot_dot = dot(ray.direction, normal);
	double d = top_dot/bot_dot;
	//vec3 point_intersect = ray.endpoint + d*ray.direction;
	Hit new_hit4;
	new_hit4.object = this;
	new_hit4.t = d;
	new_hit4.location = ray.Point(d);
	new_hit4.ray_exiting = false;
	hits.push_back(new_hit4);
	// hits.push_back(new_hit4);	
    }
    /*		
	vec3 xyz = (x1 - ray.endpoint);
	double top = dot(normal,xyz);
	double bot = dot(normal, ray.direction);
	if(bot == 0){
		return;
	}else{
		double _t = top/bot;
		if(_t > small_t){
			Hit new_hit4;
			new_hit4.object = this;
			new_hit4.t = _t;
			new_hit4.location = ray.Point(_t);
			new_hit4.rotation = mat3::id();
			new_hit4.ray_exiting = false;
			hits.push_back(new_hit4);	
		}
	}     
    */
	
}

vec3 Plane::
Normal(const vec3& point) const
{
    
    return this->normal;
}

void Plane::Update_Bounding_Box()
{
    bounding_box.Make_Full();
    infinite_box=true;
}

