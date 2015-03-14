#include "vector.h"
#include "MATH.h"

using namespace std;

#define COMPONENT_BY_SCALAR(component, op, scalar)\
	this->component op scalar

//getters
double vector:: X()  { return _x; }
double vector:: Y()  { return _y; }
double vector:: Z()  { return _z; }

//magnitudes
double vector:: mag() { return (sqrt(magSqr())); }
double vector ::magSqr() { return (sqr(_x) + sqr(_y) + sqr(_z)); }

double vector::dist(vector* v){ return sqrt( this->distSqr(v) );}
double vector::distSqr(vector* v){
	return sqr( this->_x - v->_x) + sqr( this->_y - v->_x ) + sqr( this->_z - v->_z );
}

double vector:: dot(vector* v){return  (X()*v->X() + Y()*v->Y() + Z()*v->Z());}
double vector:: dot(vector* v1, vector *v2) { return v1->dot(v2); }
	
vector* vector:: invert(vector* v1,  vector* result) {

	result->_x = -v1->_x;
	result->_y = -v1->_y;
	result->_z = -v1->_z;
	return result;
}

vector* vector:: add(vector* v1, vector* v2, vector* result) {

	result->_x = v1->_x + v2->_x;
	result->_y = v1->_y + v2->_y;
	result->_z = v1->_z + v2->_z;
	return result;
}

vector* vector::add(double scalar){
	return new vector( COMPONENT_BY_SCALAR(_x, +, scalar), COMPONENT_BY_SCALAR(_y, +, scalar), COMPONENT_BY_SCALAR(_z, +, scalar), false );
}

vector* vector::subtract(vector* v1, vector* v2, vector* result) {
	result->_x = v1->_x - v2->_x;
	result->_y = v1->_y - v2->_y;
	result->_z = v1->_z - v2->_z;
	return result;
}

vector* vector::subtract(double scalar){
	return new vector( COMPONENT_BY_SCALAR(_x, -, scalar), COMPONENT_BY_SCALAR(_y, -, scalar), COMPONENT_BY_SCALAR(_z, -, scalar), false );
}

vector* vector :: cross(vector* v1, vector* v2, vector* result) {

	result->_x = v1->_y * v2->_z - v1->_z * v2->_y;
	result->_y = v1->_z * v2->_x - v1->_x * v2->_z;
	result->_z = v1->_x * v2->_y - v1->_y * v2->_x;
	return result;
}

vector* vector :: multiply(vector* v1, double scale, vector* result) {

	result->_x = v1->_x * scale;
	result->_y = v1->_y * scale;
	result->_z = v1->_z * scale;
	return result;
}

vector* vector::multiply(double scalar){
	return new vector( COMPONENT_BY_SCALAR(_x, +, scalar), COMPONENT_BY_SCALAR(_y, +, scalar), COMPONENT_BY_SCALAR(_z, +, scalar), false );
}

void vector:: unitary(vector* v){
	double magnitude = v->mag();
	if(magnitude == 0)
		return;

	v->_x = (v->_x)/magnitude;
	v->_y = (v->_y)/magnitude;
	v->_z = (v->_z)/magnitude;
	v->isUnit = true; //now the vector is unitary i must change this field
}

bool vector:: check( vector*v ){
	if(v->isUnit != false) return true;
	else return false;
}

#include <iostream>

void vector::preview(){
	std::cout<<"("<<this->_x<<", "<<this->_y<<", "<<this->_z<<")"<<std::endl;
}

/*
int main(){

	bool booleano = false;
	vector* result = new vector(0.0, 0.0, 0.0, false);
	vector* v = new vector(1.0, 1.0, 1.0, false);
	vector* v1 = new vector(2.0,2.0, 2.0, false);
	double resultado = 0.0;
	v1->unitary(v1);	

	if(v1->check(v)) {cout<<"el vector es unitario"<<endl;}
	else {cout <<"no es unitario"<<endl;}
	
	//vector* result = new vector(0.0, 2.0, 0.0);
	//cout<<result->mag()<<endl;
	//result = v->invert(v, v1); 
	//result = v->multiply(v, 2.0, result);
	//result = v->add(v, v1, result);
	//result = v->subtract(v, v1, result);
	//result = v->cross(v, v1, result);
	//resultado = v->dot(v);
	//cout << "valor: "<< resultado  << endl;
	//cout << "coordenadas: "<< result->_x  << result->_y  << result->_y<<endl;
	
	
	
	return 0;
}
*/
