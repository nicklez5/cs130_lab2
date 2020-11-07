#include "boolean.h"

// Determine if the ray intersects with the boolean of A and B.
void Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    std::vector<Hit> hits_A;
    A->Intersection(ray,hits_A);
    std::vector<Hit> hits_B;
    B->Intersection(ray,hits_B);
    std::set<Hit> sorted_A;
    std::set<Hit> sorted_B;
    std::set<Hit> total_AB;
    std::set<Hit> intersecting_AB;
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
    std::set<Hit>::iterator itr = total_AB.begin();
    while(itr != total_AB.end()){
	Hit xyz3 = (*itr);
	std::set<Hit>::iterator set_A_itr = sorted_A.find(xyz3);
	if(set_A_itr != sorted_A.end()){
		if(xyz3.ray_exiting){
			inside_A = false;
		}else{
			inside_A = true;
		}
	}
	std::set<Hit>::iterator set_B_itr = sorted_B.find(xyz3);
	if(set_B_itr != sorted_B.end()){
		if(xyz3.ray_exiting){
			inside_B = false;
		}else{
			inside_B = true;
		}
	}
	if(inside_A && inside_B){
		intersecting_AB.insert(xyz3);
	}
	itr++;
    }
     
    if(debug_pixel){
	
    	int index_B = 0;
   	std::set<Hit>::iterator it = sorted_B.begin();
    	while(it != sorted_B.end()){
		Hit xyz = (*it);
		std::cout << "Hit in B[" << index_B << "] t = " << xyz.t  << " location = " << xyz.location << " ray_exiting: " << xyz.ray_exiting << std::endl;
		index_B++;
		it++;	
    	}
    	int index_A = 0;
    	std::set<Hit>::iterator it2 = sorted_A.begin();
    	while(it2 != sorted_A.end()){
		Hit xyz2 = (*it2);
		std::cout << "Hit in A[" << index_A << "] t = " << xyz2.t << " location = " << xyz2.location << " ray_exiting: " << xyz2.ray_exiting << std::endl;
		index_A++;
		it2++;
    	}
	int index_b4_AB = 0;
	std::set<Hit>::iterator itzel = total_AB.begin();
	while(itzel != total_AB.end()){
		Hit random_hit = (*itzel);
		std::cout << "Hit in B4 AB[" << index_b4_AB << "] t = " << random_hit.t << " location = " << random_hit.location << " ray_exiting: " << random_hit.ray_exiting << std::endl;
		index_b4_AB++;
		itzel++;
	}
	int index_AB = 0;
	std::set<Hit>::iterator itr3 = intersecting_AB.begin();
	while(itr3 != intersecting_AB.end()){
		Hit xyz_3 = (*itr3);
		std::cout << "Hit in AB[" << index_AB << "] t = " << xyz_3.t << " location = " << xyz_3.location << " ray_exiting: " << xyz_3.ray_exiting << std::endl;
	        index_AB++;
		itr3++;	
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
    // Compute bounding_box from A->bounding_box and B->bounding_box.
    // Note that this should depend on the type of boolean being performed.
    TODO;
}

