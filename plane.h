#pragma once

#include <stdio.h>
#include "colour.h"
#include "ray.h"
#include "object.h"
#include "light.h"
#include "hit.h"

class Plane : public Object {
public:

	Vertex point1;
	Vertex point2;
	Vertex point3;
	Vector normal;
	float d;

	bool constantx;
	bool constanty;
	bool constantz;
	float minx;
	float maxx;
	float miny;
	float maxy;
	float minz;
	float maxz;

	Plane(Vertex p1, Vertex p2, Vertex p3);
	Plane(Vertex p1, Vertex p2, Vertex p3, bool const_x, bool const_y, bool const_z, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
	void intersection(Ray ray, Hit &hit);
};

