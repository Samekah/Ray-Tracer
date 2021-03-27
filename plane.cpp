#include "plane.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "vector.h"
#include "vertex.h"

// Normal plane made up of 3 points, from which two of three possible vectors are found, from which the plane normal is found
Plane::Plane(Vertex p1, Vertex p2, Vertex p3) {
	point1 = p1;
	point2 = p2;
	point3 = p3;

	Vector p1_to_p2;
	Vector p1_to_p3;

	// vector from p1 to p2
	p1_to_p2.x = point2.x - point1.x;
	p1_to_p2.y = point2.y - point1.y;
	p1_to_p2.z = point2.z - point1.z;
	p1_to_p2.normalise();

	// vector from p1 to p3
	p1_to_p3.x = point3.x - point1.x;
	p1_to_p3.y = point3.y - point1.y;
	p1_to_p3.z = point3.z - point1.z;
	p1_to_p3.normalise();

	// cross product to get plane normal
	p1_to_p3.cross(p1_to_p2, normal);
	normal.normalise();

	// calculate constant d in the equation p.n + d = 0
	d = normal.dot(point1);

	//if up to one of these consts are true that means all the z/y/z values are constant for all point on plane
	//if constant in z it means that we will only see plane in x and y axis
	constantx = false;
	constanty = false;
	constantz = false;
}

// Plane > Surface (bound by minimum and maximum x, y and z values)
Plane::Plane(Vertex p1, Vertex p2, Vertex p3, bool const_x, bool const_y, bool const_z, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) {
	point1 = p1;
	point2 = p2;
	point3 = p3;

	Vector p1_to_p2;
	Vector p1_to_p3;

	// vector from p1 to p2
	p1_to_p2.x = point2.x - point1.x;
	p1_to_p2.y = point2.y - point1.y;
	p1_to_p2.z = point2.z - point1.z;
	p1_to_p2.normalise();

	// vector from p1 to p3
	p1_to_p3.x = point3.x - point1.x;
	p1_to_p3.y = point3.y - point1.y;
	p1_to_p3.z = point3.z - point1.z;
	p1_to_p3.normalise();

	// cross product to get plane normal
	p1_to_p3.cross(p1_to_p2, normal);
	normal.normalise();

	// calculate constant d in the equation p.n + d = 0
	d = normal.dot(point1);

	//if up to one of these consts are true that means all the z/y/z values are constant for all point on plane
	//for example if constant in z it means that we will only see plane in x and y axis
	//this also means that minz and maxz would have to be the same and the points z value would also need to be the same
	constantx = const_x;
	constanty = const_y;
	constantz = const_z;

	// bounding coordinate values
	minx = x_min;
	maxx = x_max;
	miny = y_min;
	maxy = y_max;
	minz = z_min;
	maxz = z_max;
	
}

void Plane::intersection(Ray ray, Hit &hit) {
	hit.flag = false;

	float t;
	Vertex q;
	Vector v;

	q = ray.position;
	v = ray.direction;

	// t = -(n.q + d)/ n.v
	float numer = (normal.dot(q) + d) * -1.0f;
	float denom = normal.dot(v);

	//if denominator is zero, ray does not intersect (or is contained in the plane)
	// and so we cannot do the calculation
	if (denom == 0.0) {
		return;
	}

	//calculate the point of intersection
	t = numer / denom;

	if (t > 0.0) {
		//update the positions at which the ray intersects
		hit.t = t;
		hit.position.x = ray.position.x + t * ray.direction.x;
		hit.position.y = ray.position.y + t * ray.direction.y;
		hit.position.z = ray.position.z + t * ray.direction.z;
		hit.normal = normal;

		// if enclosed
		if (constantx) {
			if (hit.position.y >= miny && hit.position.y <= maxy && hit.position.z >= minz && hit.position.z <= maxz) {
				hit.flag = true;
			}
		} else if (constanty) {

			if (hit.position.z >= minz && hit.position.z <= maxz && hit.position.x >= minx && hit.position.x <= maxx) {
				hit.flag = true;
			}
		} else if (constantz) {

			if (hit.position.x >= minx && hit.position.x <= maxx && hit.position.y >= miny && hit.position.y <= maxy) {
				hit.flag = true;
			}
		} else {
			hit.flag = true;
		}
	}


	hit.what = this;

	return;
}
