#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
void Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    double gradient = pow(dot(ray.direction,ray.endpoint - center),2.00);
    vec3 random_v = ray.endpoint - center;
    double normalized_v = gradient - random_v.magnitude_squared() - pow(radius,2.00);
    if(normalized_v < 0){
	std::vector<Hit> _empty;
	hits = _empty;
    }else if(normalized_v == 0){
	double first_distance = -(dot(ray.direction, ray.endpoint - center));
	vec3 t_0 = ray.endpoint + first_distance*ray.direction;
	Hit _hit; 
	_hit.t = first_distance;
	_hit.location = t_0;
	hits.push_back(_hit); 	
    }else if(normalized_v > 0){
	double second_d = -(dot(ray.direction, ray.endpoint - center)) + sqrt(normalized_v);
	double third_d =  -(dot(ray.direction, ray.endpoint - center)) - sqrt(normalized_v);
	vec3 t_1 = ray.endpoint + second_d*ray.direction;
	Hit _hit2;
	_hit2.t = second_d;
	_hit2.location = t_1;
	hits.push_back(_hit2);
	vec3 t_2 = ray.endpoint + third_d*ray.direction;
	Hit _hit3;
	_hit3.t = third_d;
	_hit3.location = t_2;
	hits.push_back(_hit3); 
    }
     
	 
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal = point - center;
    return normal.normalized();
}

// set this->bounding_box so that it contains the sphere as tightly as possible.
void Sphere::Update_Bounding_Box()
{
   bounding_box.hi = center + radius;
   bounding_box.lo = center - radius; 
   infinite_box=false;
}

