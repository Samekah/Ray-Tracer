#include "box.h"
#include "vector.h"
#include "vertex.h"

Box::Box(Vertex mi_point, Vertex ma_point){
    
    min_point = mi_point;
    max_point = ma_point;
}

void Box::intersection(Ray ray, Hit &hit){

    hit.flag = true;

    // Vector ray_direction_inv;
    // ray.direction.inverse(ray_direction_inv);
       
    float temp_swap = 0.0f;
    float t = 0.0f;

    t_xmin = (min_point.x - ray.position.x)/ray.direction.x;
    t_xmax = (max_point.x - ray.position.x)/ray.direction.x;

    ////std::cout << "x t values calculated"<< //std::endl;

    if(t_xmin > t_xmax){
        //std::cout << "swapping x t values"<< //std::endl;
        temp_swap = t_xmax;
        t_xmax = t_xmin;
        t_xmin = temp_swap;
    }
    
    t_ymin = (min_point.y - ray.position.y)/ray.direction.y;
    t_ymax = (max_point.y - ray.position.y)/ray.direction.y;
    //std::cout << "y t values calculated"<< //std::endl;
    
    if(t_ymin > t_ymax){
        //std::cout << "swapping y t values"<< //std::endl;
        temp_swap = t_ymax;
        t_ymax = t_ymin;
        t_ymin = temp_swap;
    }

    if((t_xmin > t_ymax) || (t_ymin > t_xmax)){
        //std::cout << "does not hit box - check 1"<< //std::endl;
        hit.flag = false;
    }

    if(t_ymin > t_xmin){
        //std::cout << "t_ymin > t_xmin"<< //std::endl;
        t_xmin = t_ymin;
    }

    if(t_ymax < t_xmax){
        //std::cout << "t_ymax < t_xmax"<< //std::endl;
        t_xmax = t_ymax;
    }
    
    t_zmin = (min_point.z - ray.position.z)/ray.direction.z;
    t_zmax = (max_point.z - ray.position.z)/ray.direction.z;
    //std::cout << "y t values calculated"<< //std::endl;

    if(t_zmin > t_zmax){
        //std::cout << "swapping z t values"<< //std::endl;
        temp_swap = t_zmax;
        t_zmax = t_zmin;
        t_zmin = temp_swap;
    }

    if((t_xmin > t_zmax) || (t_zmin > t_xmax)){
        //std::cout << "does not hit box - check 2"<< //std::endl;
        hit.flag = false;
    }

    if(t_zmin > t_xmin){
        //std::cout << "t_zmin > t_xmin"<< //std::endl;
        t_xmin = t_zmin;
    }

    if(t_zmax < t_xmax){
        //std::cout << "t_zmax < t_xmax"<< //std::endl;
        t_xmax = t_zmax;
    }

    t = t_xmin;
    //std::cout << "t value is: "<< t << //std::endl;

    if(t < 0.0f){
        //std::cout << "t < 0, use max val"<< //std::endl;
        t = t_xmax;
        if(t < 0.0f){
            //std::cout << "t < 0, doesnt hit box"<< //std::endl;
            hit.flag = false;
        }
    }

    if(hit.flag != false){
        //std::cout << "if it hits box set hit t val"<< //std::endl;
        hit.t = t;
    }
    hit.what = this;
}