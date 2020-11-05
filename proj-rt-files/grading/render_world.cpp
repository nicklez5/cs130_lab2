#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
   
    Object *return_me = NULL;
    double min_t = std::numeric_limits<double>::max();
    size_t i = 0;
    size_t closest_i = 0;
    int random_string = 0;    
    for(; i < objects.size(); i++){
	Object* o = objects[i];
	if(o == NULL){
		//std::cout << "Empty object\n";
	}
	std::vector<Hit> empty_hit_vec;
	o->Intersection(ray, empty_hit_vec);
	
	if(empty_hit_vec.empty()){
		//std::cout << "Empty vector\n";
		return NULL;
	}
 	if(debug_pixel){
		random_string = static_cast<int>(i);
		std::cout << "intersect test with obj[" << random_string << "]: hits = { ";
	}	
	for(size_t j = 0; j < empty_hit_vec.size(); j++){
		Hit abc = empty_hit_vec[j];
		if(debug_pixel){
			std::cout << " { obj[" << random_string << "], "  << abc.t << ", " << abc.ray_exiting << "}";
			if(j+1 != empty_hit_vec.size()){
				std::cout << ",";
			}else{
				std::cout << " }" << std::endl;
			} 
				
		}
		if(abc.t < min_t && abc.t > small_t){
			min_t = abc.t;
			closest_i = i; 
			return_me = const_cast<Object*>(abc.object);
			hit = abc;
			
		} 
	}			
    }
    if(debug_pixel){
		random_string = static_cast<int>(closest_i);
		std::cout << "closest intersection: return = obj[" << random_string << "]; hit = {obj[" << random_string << "], "  << hit.t << ", " << hit.ray_exiting << "}" << std::endl;
    }
    return return_me;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
   
    vec3 result_vec = this->camera.World_Position(pixel_index);
    result_vec = result_vec - this->camera.position;
     
    Ray ray(this->camera.position, result_vec.normalized());
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    Hit empty_hit;
    if(debug_pixel){ 	
	std::cout << "cast ray: end = " << ray.endpoint << "; dir = " << ray.direction << std::endl;
 		
    } 
    Object* closest_obj = Closest_Intersection(ray, empty_hit);
    if(closest_obj != NULL){
		vec3 intersect_pt = ray.Point(empty_hit.t);	
		vec3 normal_1 = closest_obj->Normal(intersect_pt);
									
		color = closest_obj->material_shader->Shade_Surface(ray, intersect_pt, normal_1, recursion_depth);
    }else{
		vec3 empty_vec = vec3();			
		color = background_shader->Shade_Surface(ray, empty_vec, empty_vec.normalized() , recursion_depth);
			 
    }
     // determine the color here
    return color;
}
