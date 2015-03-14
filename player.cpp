#include "timer.h"
#include "MATH.h"
#include "player.h"

using namespace std;

SMTKU lastWall;

player::player(){
	rep = new teapot();
	velocity = new ray();
				
	this->topSpeed = DEFAULT_SPEED;
	this->boostSpeed = DEFAULT_SPEED;
	this->boostDuration = 0;
	this->boostCooling = 0;

	human = false;
	alive = true;
};
			
player::player(representation* representation, vector* startPoint, float topSpeed, float boostSpeed, float boostDuration, float boostCooling){
	rep = representation;
	startingPoint = startPoint;
	velocity = new ray();
	this->reset();
				
	this->topSpeed = topSpeed;
	this->boostSpeed = boostSpeed;
	this->boostDuration = boostDuration;
	this->boostCooling = boostCooling;

	human = false;
	alive = true;
}

player::player(GLdouble radius, ray* initialVelocity){
	CHECK_NULLSTRING;
	rep = new disk(radius, nullString);
	startingPoint = new vector();
	velocity = initialVelocity;
	this->reset();
				
	this->topSpeed = DEFAULT_SPEED;
	this->boostSpeed = DEFAULT_SPEED;
	this->boostDuration = 0;
	this->boostCooling = 0;
				
	human = false;
	alive = true;
};

//moves this element the distance corresponding to the elapsed time
void player :: Advance(){
	//if(!human){
	//	free(velocity->direction);
	//	velocity->direction = headTo(target, speed);
	//}

	movement(rep->position, velocity);
	if( secondsElapsed(lastWall) > 1){
		CURR_TIME(lastWall);

		CHECK_NULLSTRING;
		parallelepiped* p = new parallelepiped(1, 1, 1, nullString);

		p->position->_x = rep->position->_x;
		p->position->_y = rep->position->_y;
		p->position->_z = rep->position->_z;
		this->estela.push(p);

		std::cerr<<"Le meti otro ";
		p->preview();
	}
	
}

int player:: colision_plano_rayo(Plano* x, vector* start_point, vector* drt, double lamda, vector* pNormal){

		double dotproduct, l2, h;
		//_x, _y,_z define a position of the plane
		vector* v;//position
		h = (x->h_sup + x->h_inf) / 2;//kind of constant
		//the vector normal of the point
		vector* norm;
		vector* resta;
		switch(x->coordAxis()){
			case 'x':
				v = new vector(0.0, h, x->coord, false);
				norm = new vector(1.0, 0.0, 0.0, true);
				break;
			case 'y':
				v = new vector(h, 0.0, x->coord, false);
				norm = new vector(0.0, 1.0, 0.0, true);
				break;
			case 'z':
				v = new vector(x->coord, h, 0.0, false);
				norm = new vector(0.0, 0.0, 1.0, true);
				break;
		}


		//dot product between the plane normal and the ray direction
		 dotproduct = norm->dot(norm, drt);

		// Determine If Ray Parallel To Plane
		//if the dot product its equal to ZERO then the vectors are parallel

		    if ((dotproduct == ZERO) && ( dotproduct > - ZERO))
			return 0;
		     
		//find the distance to collision point
			resta = new vector();
			resta->_x = v->_x - start_point->_x; 
			resta->_y = v->_y - start_point->_y;
			resta->_z = v->_z - start_point->_z;
			l2 = norm->dot(norm, resta) / dotproduct;
			 
		//test if collision is behind start
		    	if (l2<=ZERO)                            // Test If Collision Behind Start
		       		 return 0;
		 
		    pNormal->_x = norm->_x;
		    pNormal->_y = norm->_y;
		    pNormal->_z = norm->_z;
		    lamda=l2;
		    return 1;
}

void player::inic(double a, double b, double c){

		CURR_TIME(lastTranslation);
		CURR_TIME(lastWall);
		velocity->point->_x += c*sin(a);
		velocity->point->_y += c*sin(b);
		velocity->point->_z += c*sin(c);
		
	
	
	}

void player::inic(){
	this->inic(1.0, 1.0, 1.0);
}

void player::reset(){
	rep->initPos( new vector(startingPoint) );
	rep->position->_y += rep->verticalOffset();
	velocity->point = rep->position;
}

/*	verifica si el jugador ha entrado en colisión con el plano dado
 *	devuelve 0 si no lo ha hecho, 1 si lo ha hecho en el centro del plano, 
 *	2 si lo ha hecho chocando contra la esquina superior, y -2 si lo ha hecho 
 *	chocando contra la esquina inferior 
 */
int player :: colision_plano(player* p, Plano* x){
	double plane_line;	//coordenada de p que debe coincidir con x->coord
	double plane_perpend;	//coordenada de p que debe estar entre x->inf y x->sup
	
	if(x->parallel == XY ){
		plane_line = p->rep->position->_x + p->velocity->direction->_x;	//anticipar colisiones a ocurrir entre esta llamada y la próxima
		plane_perpend = p->rep->position->_y;
	}else{
		plane_line =p->rep->position->_y+ p->velocity->direction->_y/2;
		plane_perpend = p->rep->position->_x;
	}
	//no me importa si el plano es paralelo a XZ porque no me interesa ese caso(no se cubre)
		
	if(fabs( (plane_line - x->coord)*1 ) - EPSILON <= 0.5){
		//está en línea con el plano
		if(plane_perpend + EPSILON > x->h_inf && plane_perpend-EPSILON < x->h_sup){
			//está en contacto con el plano
			if(plane_perpend-EPSILON < x->h_inf){
				//está en contacto con la esquina inferior del plano
				return -2;
			}else if(plane_perpend+EPSILON > x->h_sup){
				//está en contacto con la esquina superior
				return 2;
			}else{
				return 1;
			}
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

/*	Cambia la dirección de la pelota, suponiendo que acaba de
 *	colisionar contra una superficie a "r" radianes anti-horario
 *	del eje x.
 *	"r" debe estar en el intervalo [0, PI)
 *	Devuelve 0 si ocurrió un error de calculo (el cual se guarda en errno), 1 en cualquier otro caso
 */
int player :: rebotar_pelota(player* p, double r){
	
	double rapidez, anguloAct, anguloChoque, anguloNew;
	if(r+EPSILON < 0 || r-EPSILON > PI){
		
		return 0;
	}

	//short-circuiting por eficiencia
	if(r-EPSILON <= 0 || r + EPSILON > PI){
		//la superficie es horizontal
		p->velocity->direction->_y *= -1;
		return 1;
	}
	if(r-EPSILON <= PI/2 && r+EPSILON >= PI/2){
		//la superficie es vertical
		p->velocity->direction->_x *= -1;
		return 1;
	}
	
	//Si llegamos hasta aqui, la superficie tiene un ángulo no-notable
	
	//calcular magnitud del vector velocidad
	rapidez = sqrt( pow(p->velocity->direction->_x,2) + pow(p->velocity->direction->_y,2) + pow(p->velocity->direction->_z,2) );
	
	//calcular ángulo de la trayectoria actual con respecto al eje x
	if(p->velocity->direction->_x - EPSILON <= 0 && p->velocity->direction->_x + EPSILON >= 0)	//evitar división entre cero
		anguloAct = PI/2;
	else
		anguloAct = atan( p->velocity->direction->_y / p->velocity->direction->_x );	
	/*
	 * Dom(atan) entre -infinito y +infinito; no hay error EDOM. Resultado entre -PI/2 y PI/2; no puede haber error ERANG
	 * */


	//calcular ángulo de la trayectoria nueva con respecto al eje y
	if(r-EPSILON > PI/2){
		anguloNew = -(anguloAct - 2*r) + PI/2;
	}else{
		anguloChoque = PI/4 + r - anguloAct;
		anguloNew = PI/2 - (anguloChoque + anguloAct);
	}
	//AnguloNew entre -PI/2 y 4*PI, lo cual está en el dominio de sin y cos

	p->velocity->direction->_x = rapidez * sin(anguloNew);	//sin entre -1 y 1; no puede haber error ERANG
	p->velocity->direction->_y = rapidez * cos(anguloNew);	//cos entre -1 y 1; no puede haber error ERANG
	//printf("%3.1f grados ==> %3.1f grados, vel_x = %.3f, vel_y = %.3f", anguloAct*180/PI, anguloNew*180/PI, p->vel_x, p->vel_y);
	return 1;
}

int player::detectarColisionPelotaLadrillo(parallelepiped* p, player* s){

	Plano *abajo     = new Plano(XY, 0, 0, p->position->_x, p->position->_x + p->length, p->position->_y),
			*arriba    = new Plano(XY, 0, 0, p->position->_x, p->position->_x + p->length, p->position->_y + p->height),
			*derecha   = new Plano(YZ, p->position->_y, p->position->_y + p->height, 0, 0, p->position->_x + p->length),
			*izquierda = new Plano(YZ, p->position->_y, p->position->_y + p->height, 0, 0, p->position->_x);
				
				
	if(abajo == NULL || arriba == NULL || derecha == NULL || izquierda == NULL)
		cout<< "memoria insuficiente para crear los planos del ladrillo\n"<<endl;
				
	int a = colision_plano(s, abajo),
		b = colision_plano(s, arriba),
		c = colision_plano(s, derecha),
		d = colision_plano(s, izquierda);

	free(abajo);
	free(arriba);
	free(derecha);
	free(izquierda);

	if(a ==1 || b ==1) return 1;
	if(c ==1 || d ==1) return 2;
	if(b == -2 || d ==2 || a==2 ||c == -2) return 3;
	if(b==2 || c == 2 || a == -2 || d==-2) return 4;
	else return 0;
	};
			
double player::speed(){
	if(velocity->direction->_x != 0) return velocity->direction->_x;
	else if(velocity->direction->_y != 0) return velocity->direction->_y;
	else if(velocity->direction->_z != 0) return velocity->direction->_z;
	else
		return 0.0;

};

void player::preview(){
	std::cout<<"player represented by ";
	rep->preview();
	std:: cout<<"travelling at a velocity defined by ";
	velocity->preview();
}

void player::draw(){
	//dibujar al jugador
	if(alive)
		rep->draw();

	//dibjuar estela

	stack<parallelepiped*> copy;
	
	parallelepiped* u;
	//move everything to copy and draw it in the process
	while( !(this->estela.empty()) ){
		u = this->estela.top();
		this->estela.pop();
		u->draw();

		copy.push(u);
		}
	//move everything back
	while( !copy.empty() ){
		this->estela.push( copy.top() );
		copy.pop();
	}

}
