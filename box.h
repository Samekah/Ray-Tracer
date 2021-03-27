#pragma once

#include <stdio.h>
#include "colour.h"
#include "ray.h"
#include "object.h"
#include "light.h"
#include "hit.h"

class Box : public Object{
public:

    Vertex min_point;
    Vertex max_point;
    
    float t_xmin;
    float t_xmax;
    float t_ymin;
    float t_ymax;
    float t_zmin;
    float t_zmax;

    Box(Vertex mi_point, Vertex ma_point);
    void intersection(Ray ray, Hit &hit);
};