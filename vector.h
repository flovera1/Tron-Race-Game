#ifndef __VECTOR
#define __VECTOR

	 class vector
	{
		public:
		//coordenates
			double _x, _y, _z;
			bool isUnit;// true si el vector es unitario, false si no
			
			vector(double x, double y, double z, bool _unit) : _x(x), _y(y), _z(z), isUnit(_unit){}
			vector() : _x(0.0), _y(0.0), _z(0.0) {}
			vector(vector* copyFrom): _x(copyFrom->_x), _y(copyFrom->_y), _z(copyFrom->_z), isUnit(copyFrom->isUnit){}
			
			//getters
			double X();
			double Y();
			double Z();
			
			//magnitudes
			double mag();
			double magSqr();
			
			//operations
			double dot(vector* v);
			double dot(vector* v1, vector* v2);
			double dist(vector* v);
			double distSqr(vector* v);
			static vector* add(vector* v1, vector* v2, vector* result);
			vector* add(double scalar);	//Warning: creates a new vector
			static vector* subtract(vector* v1, vector* v2, vector* result);
			vector* subtract(double scalar);	//Warning: creates a new vector
			static vector* cross(vector* v1, vector* v2, vector* result);
			static vector* invert(vector* v1, vector* result);
			static void unitary(vector* v);		
			bool check(vector*v);
			
			
			static vector* multiply(vector* v1, double scale, vector* result);
			vector* multiply(double scalar);	//Warning: creates a new vector

			void preview();
	};
#endif

