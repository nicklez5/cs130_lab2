#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
void Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    Hit hit1, hit2;
    //double gradient = pow(dot(ray.direction,ray.endpoint - center),2.00);
    vec3 random_v = ray.endpoint - center;
    double a, b , c, t2, t1, root;
    a = ray.direction.magnitude_squared();
    b = 2*dot(ray.direction, random_v);
    c = random_v.magnitude_squared() - (radius * radius);
    root = (b*b) - (4*a*c);
    if(root < 0){
	    std::vector<Hit> _empty;
	    hits = _empty;
    }else if(root == 0){
	    t1 = ((-1)*b + sqrt(root))/(2*a);
	    t2 = ((-1)*b - sqrt(root))/(2*a);
	    vec3 distance_0 = ray.endpoint + ray.direction * t1;
	    hit1.t = t1;
	    hit1.location = distance_0;
	    hit1.object = this;
	    hit1.ray_exiting = true;
	    hits.push_back(hit1);
    }else{
	    t1 = ((-1)*b + sqrt(root))/(2*a);
	    t2 = ((-1)*b - sqrt(root))/(2*a);
	    vec3 distance_1 = ray.endpoint + ray.direction * t1;
	    vec3 distance_2 = ray.endpoint + ray.direction * t2;
	    if((t1 > 0) && (t2 > 0)){
		hit1.t = t1;
		hit1.location = distance_1;
		hit1.object = this;
		hit2.t = t2;
		hit2.location = distance_2;
		hit2.object = this;
		if(t1 < t2){
			hit2.ray_exiting = true;
			hit1.ray_exiting = false;
		}else{
			hit1.ray_exiting = true;
			hit2.ray_exiting = false;
		}
		hits.push_back(hit1);
		hits.push_back(hit2);
            }else if((t1 < 0) && (t2 > 0)){
		hit2.t = t2;
		hit2.location = distance_2;
		hit2.object = this;
		hit2.ray_exiting = true;
		hits.push_back(hit2);
  	    }else if((t1 > 0) && (t2 < 0)){
		hit1.t = t1;
		hit1.location = distance_1;
		hit1.object = this;
		hit1.ray_exiting = true;
		hits.push_back(hit1);
	    }
	
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

