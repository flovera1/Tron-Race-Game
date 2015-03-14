#include "ray.h"
#include "MATH.h"
#include <stdio.h>
#include <iostream>
using namespace std;

bool ray:: adjacentPoint(ray* ray1, vector* point1){

	double x2 =  point1->_x + ray1->direction->_x;
	double y2 = point1->_y + ray1->direction->_y;
	double z2 = point1->_z + ray1->direction->_z;
	
	double calc1= (point1->_x - ray1->point->_x) / (x2 - ray1->point->_x);
	double calc2= (point1->_y - ray1->point->_y) / (y2 - ray1->point->_y);
	double calc3= (point1->_z - ray1->point->_z) / (z2 - ray1->point->_z);
	
	if(calc1 == calc2 && calc2 == calc3){
		return true;
	}
	else{
		return false;
	}
		
}

ray* ray:: invert(ray* r, ray*result){
	result->point = r->point;
	result->direction->invert(r->direction, result->direction);
	return result;
}

double ray:: dist2(vector* point1, vector* point2){

		double x, y, z;
		x = (sqr(point2->_x - point1->_x));
		y = (sqr(point2->_y - point1->_y));
		z = (sqr(point2->_z - point1->_z));
		return sqrt( x+y+z);
		
}


double ray:: dist(ray* r, vector* point1, vector* point2){

	//si los puntos estan sobre la recta, entonces calculo la distancia entre ellos
	if (adjacentPoint(r, point1) && adjacentPoint(r, point2))
		return r->dist2(point1, point2);
	else
		return 0.0;
	
}

void ray::preview(){
	std::cout<<"ray point: ";
	point->preview();
	std::cout<<"ray direction: ";
	direction->preview();
}

/*
int main(){

	ray* r = new ray();
	r->point =new vector(0.0, 0.0, 0.0, false);
	r->direction = new vector(2.0, 2.0, 2.0, false);	
	
	vector* p = new vector(2.0, 2.0, 2.0, false);
	//cout<<"punto"<<r->point->_x<<endl;
	bool f = r->adjacentPoint(r, p);
	if(f) cout << "funciono!! :D"<<endl;
	
return 0;
}
*/
