#include "boolean.h"

/* 
 * type_index = 0 -> type intersection
 *              1 -> type difference
 *              2 -> type union
 */
// Determine if the ray intersects with the boolean of A and B.
void Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    int type_index = 0;	
    switch(type){
	    case type_intersection:
		//std::cout << "Type intersection" << std::endl;
		type_index = 0;
		break;
	    case type_difference:
		//std::cout << "Type Difference" << std::endl;
		type_index = 1;
		break;
 	    case type_union:
		//std::cout << "Type Union" << std::endl;
		type_index = 2;
		break;
	    default:
		//std::cout << "Nothing is happening" << std::endl;
		break;
   }

    std::vector<Hit> hits_A;
    A->Intersection(ray,hits_A);
    std::vector<Hit> hits_B;
    B->Intersection(ray,hits_B);
    std::set<Hit> sorted_A;
    std::set<Hit> sorted_B;
    std::set<Hit> total_AB;
    std::set<Hit> intersecting_AB;
    std::set<Hit> union_AB;
    std::set<Hit> diff_AB;
    bool inside_A = false;
    bool inside_B = false;
    for(size_t i = 0; i < hits_A.size(); i++){
	sorted_A.insert(hits_A.at(i));
	total_AB.insert(hits_A.at(i));
    }  
    for(size_t j = 0; j < hits_B.size(); j++){
	sorted_B.insert(hits_B.at(j));
	total_AB.insert(hits_B.at(j));
    }
    // Intersecting A B 
    std::set<Hit>::iterator itr = total_AB.begin();
    std::set<Hit>::iterator set_A_itr;
    std::set<Hit>::iterator set_B_itr;
    while(itr != total_AB.end()){
	Hit xyz3 = (*itr);

	set_A_itr = sorted_A.find(xyz3);
	if(set_A_itr != sorted_A.end()){
		if(xyz3.ray_exiting){
			inside_A = false;
			if(inside_B){
				intersecting_AB.insert(xyz3);
			}else{
				union_AB.insert(xyz3);
				diff_AB.insert(xyz3);	
			}
		}else{
			inside_A = true;
			if(!inside_B){
				union_AB.insert(xyz3);
			}
		}
	}
	set_B_itr = sorted_B.find(xyz3);
	if(set_B_itr != sorted_B.end()){
		if(xyz3.ray_exiting){
			inside_B = false;
			if(inside_A){
				intersecting_AB.insert(xyz3);
				diff_AB.insert(xyz3);
			}else{
				union_AB.insert(xyz3);
			}
		}else{
			inside_B = true;
			if(!inside_A){
				union_AB.insert(xyz3);
			}
		}
	}
	if(inside_A && inside_B){
		intersecting_AB.insert(xyz3);
	
	}
	itr++;
    }
    
    if(type_index == 0){
	std::vector<Hit> v(intersecting_AB.begin(), intersecting_AB.end());
	hits = v;
    }else if(type_index == 1){
	std::vector<Hit> v(diff_AB.begin(), diff_AB.end());
	hits = v;
 
    }else if(type_index == 2){
        std::vector<Hit> v(union_AB.begin(), union_AB.end());
	hits = v;
    }
    if(debug_pixel){
	
    	int index_B = 0;
   	std::set<Hit>::iterator it = sorted_B.begin();
	std::cout << "Intersect test with obj[" << index_B << "]->B: hits = {";
    	while(it != sorted_B.end()){
		Hit xyz = (*it);
		std::cout << " {obj[" << index_B << "]->B, " << xyz.t  << ", " << xyz.ray_exiting << "}";	
		it++;
		if(it == sorted_B.end()){
			std::cout << " }" << std::endl;
		}else{
			std::cout << ", ";
		}	
    	}
    	int index_A = 0;
    	std::set<Hit>::iterator it2 = sorted_A.begin();
	std::cout << "Intersect test with obj[" << index_A << "]->A: hits = {";
    	while(it2 != sorted_A.end()){
		Hit xyz2 = (*it2);
		std::cout << " {obj[" << index_A << "]->A, " << xyz2.t << ", " << xyz2.ray_exiting <<  "}";
		it2++;
		if(it2 == sorted_A.end()){
			std::cout << " }" << std::endl;
		}else{
			std::cout << ", ";
		}
    	}
	int index_b4_AB = 0;
	std::set<Hit>::iterator itzel = union_AB.begin();
	std::cout << "Intersect test with union obj[" << index_b4_AB << "]: hits = {";
	while(itzel != union_AB.end()){
		Hit random_hit = (*itzel);
		set_A_itr = sorted_A.find(random_hit);
	        if(set_A_itr != sorted_A.end()){
			std::cout << " {obj[" << index_b4_AB << "]->A, " << random_hit.t << ", " << random_hit.ray_exiting << "}";
		}
		set_B_itr = sorted_B.find(random_hit);
		if(set_B_itr != sorted_B.end()){
			std::cout << " {obj[" << index_b4_AB << "]->B, " << random_hit.t << ", " << random_hit.ray_exiting << "}";
		}
		itzel++;
		if(itzel == union_AB.end()){
			std::cout << " }" << std::endl;
		}else{
			std::cout << ", ";
		}	
	}
	int index_AB = 0;
	std::set<Hit>::iterator itr3 = intersecting_AB.begin();
	std::cout << "Intersect test with intersect obj[" << index_AB << "]: hits = {"; 
	while(itr3 != intersecting_AB.end()){
		Hit xyz_3 = (*itr3);
		set_A_itr = sorted_A.find(xyz_3);
		if(set_A_itr != sorted_A.end()){
			std::cout << " {obj[" << index_AB << "]->A, " << xyz_3.t << ", " << xyz_3.ray_exiting << "}";
		}
		set_B_itr = sorted_B.find(xyz_3);
		if(set_B_itr != sorted_B.end()){
			std::cout << " {obj[" << index_AB << "]->B, " << xyz_3.t << ", " << xyz_3.ray_exiting << "}";
		}
		itr3++;
		if(itr3 == intersecting_AB.end()){
			std::cout << " }" << std::endl;
		}else{
			std::cout << ", ";
		}
	        
			
	}
	int index_diff_AB = 0;
	std::set<Hit>::iterator itr4 = diff_AB.begin();
	std::cout << "Intersect test with diff obj[" << index_diff_AB << "]: hits = {";
	while(itr4 != diff_AB.end()){
		Hit xyz_4 = (*itr4);
		set_A_itr = sorted_A.find(xyz_4);
		if(set_A_itr != sorted_A.end()){
			std::cout << " {obj[" << index_diff_AB << "]->A, " << xyz_4.t << ", " << xyz_4.ray_exiting << "}";
		}
		set_B_itr = sorted_B.find(xyz_4);
		if(set_B_itr != sorted_B.end()){
			std::cout << " {obj[" << index_diff_AB << "]->B, " << xyz_4.t << ", " << xyz_4.ray_exiting << "}";
		}
		itr4++;
		if(itr4 == diff_AB.end()){
			std::cout << " }" << std::endl;
		}else{
			std::cout << ", ";
		}
	}

    }
    
        
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

void Boolean::Update_Bounding_Box()
{
    A->Update_Bounding_Box();
    B->Update_Bounding_Box();
    //std::cout << "was i here" << std::endl;
    // Compute bounding_box from A->bounding_box and B->bounding_box.
    // Note that this should depend on the type of boolean being performed.
    TODO;
}

