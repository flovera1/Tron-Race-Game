#ifndef __PLAYER
#define __PLAYER

	
	#include <iostream>
	#include <stack>
	#import <OpenGL/gl.h>
	#import <OpenGL/glu.h>
	#import <GLUT/glut.h>
	
	#include "ray.h"
	#include "representation.h"
	#include "Plano.h"
	#include "parallelepiped.h"
	#include "onStageElement.h"
	
	using namespace std;

	#define DEFAULT_SPEED  1

	class player: public onStageElement{
		public:
			vector* startingPoint;
			float topSpeed,	//maximum speed by regular acceleration
			      boostSpeed,	//speed at which the player moves during a boost
				  boostDuration,	//how long the boost lasts
				  boostCooling;	//time before the player can do another boost
			bool human;


			stack<parallelepiped*> estela;

			//############################### constructors ###########################
			//constructors
			player();
			
			player(representation* rep, vector* startingPoint, float topSpeed, float boostSpeed, float boostDuration, float boostCooling);

			player(GLdouble radius, ray* initialVelocity);
		
			//############################### methods ####################################
			void Advance();	//moves this element the distance corresponding to the elapsed time, if need be
			int colision_plano_rayo(Plano* x, vector* p, vector* drt, double lambda, vector* pNormal);
			void inic(double a, double b, double c);
			void inic();
			void reset();
			
			//metodo que calcula la colision de una pelota con un plano
			
			/*	Firma: int colision_plano(struct pelota* p, struct plano* x)
			 *	Parámetros de entrada:
			 *		p	la esfera para la cual se debe revisar si colisionó contra el plano
			 *		x	plano contra el cual puede haber colisionado p
			 *	Parámetros de salida: int
			 *		0	si no hay colisión
			 *		1	si la colisión ocurrió en el centro del plano
			 *		2	si la colssión ocurrió en la esquina superior del plano
			 *		-2	si la colisión ocurrió en la esquina inferior del plano
			 *	Funcionalidad:
			 *		verifica si la pelota dada ha entrado en colisión con el plano dado
			 */
			int colision_plano(player* p, Plano* x);
			
			int rebotar_pelota(player* p, double r);
			
			int detectarColisionPelotaLadrillo(parallelepiped* p, player* s);
			
			double speed();

			void preview();
			
			void draw();
	};
	
#endif
