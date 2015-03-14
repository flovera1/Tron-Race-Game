#include <iostream>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>
#include <math.h>
#include <assert.h>

#include "camera.h"
#include "Stage.h"
#include "player.h"
#include "Game.h"
#include "glm.h"
#include "loadFile.h"

using namespace std;

//defaults
#define RADIUS  5
#define D      50
#define H      50


double tamX = 0.2;
double tamY = 0.1;
bool start = false;

Game* g;
int currentLevel = 0;

//testing variables -- MUST BE EVENTUALLY DELETED!
parallelepiped* o;

//################################################### LUCES ###########################################
GLfloat ambiente[] = { 0.01*tamX, 0.02*tamY, 0.0, 1.0 };
GLfloat difusa[] = { 0.05*tamX, 0.05*tamY, 0.0, 1.0 };
GLfloat especular[] = { 0.08*tamX, 0.08*tamY, 0.0, 1.0 };
GLfloat posicion[] = { 0.5*tamX,0.5*tamY,0.0, 1.0};


// texturas
static GLuint texPiso;
int iheight, iwidth;
unsigned char* imagePiso = NULL;

using namespace std;

camera *stageCam,	//camera orbiting the stage
       *playerCam,	//camera following player
	   *skyCam,	//camera floating above stage
	   *currentCam;	//points to whichever of the previous cameras is in use at the time

void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	glViewport(0,0,x,y);  //Use the whole window for rendering
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(x>y)
		currentCam->aspectratio = (GLdouble)x / (GLdouble)y;
	else
		currentCam->aspectratio = (GLdouble)y/ (GLdouble)x;
	
	//update screen
	glutPostRedisplay();
	
	
//################################################### LUCES ###########################################
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	
	currentCam->focus();
	
	glClearColor(0.0f, 0.0f, 0.0f ,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//activar la textura
	//glEnable(GL_TEXTURE_2D);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glBindTexture(GL_TEXTURE_2D, texPiso);

		//dibjar todo usando esa textura
		g->levels[currentLevel]->draw();
	//glDisable(GL_TEXTURE_2D);
	
	//Esferas marcadoras de posición

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glPushMatrix();
		glTranslatef(-D, 0, -D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(D, 0, -D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(D, H, -D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-D, H, -D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-D, 0, D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(D, 0, D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(D, H, D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-D, H, D);
		glutWireSphere(RADIUS, 8, 8);
	glPopMatrix();
	
	glLoadIdentity();
	
	glutSwapBuffers();
	
	
	//##########################################LUCES######################################
	//  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	
}

void handleKeypress(int key, int x, int y) {  
	
	switch (key) {
		case GLUT_KEY_LEFT: 
			currentCam->Rotate( (GLfloat) -5.0 );
			break;
		case GLUT_KEY_RIGHT:
			currentCam->Rotate( (GLfloat) 5.0 );
			break;			
		case GLUT_KEY_UP:
			currentCam->MoveUpward( (GLfloat) 2.0 );
			break;
		case GLUT_KEY_DOWN:
			currentCam->MoveUpward( (GLfloat) -2.0 );
			break;
		default:
			return ;
			
	}
	glutPostRedisplay();
}

void  startPlaying(unsigned char key, int x, int y)
{
	player* play = g->levels[currentLevel]->players[0];
	assert(play->human);
	
	play->preview();

	double speedUpInterval = fabs( play->speed() );
	if(speedUpInterval > play->topSpeed/2)
		speedUpInterval = play->topSpeed-speedUpInterval;	//distance from upper limit
	//else distance from lower limit, which is zero

	//speedUpInterval /= play->topSpeed;	//make it a ratio

	cerr<<play->speed()<<" u/s (with possibility of increasing "<<speedUpInterval<<" u/s to reach "<<play->topSpeed<<")"<<endl;
	switch(key){
		case ' ':
			g->levels[currentLevel]->inic();
			//empezar timers correspondientes
			start = true;
			break;
		case 'a':
			if(play->velocity->direction->_z != 0){
				//aumentar velocidad en -z
				play->velocity->direction->_z -= speedUpInterval;
			}else if(play->velocity->direction->_x != 0 || play->velocity->direction->_y != 0){
				//cambiar la velocidad hacia -z
				play->velocity->direction->_z = (-1)*fabs(play->speed());
				play->velocity->direction->_x = 0.0;
				play->velocity->direction->_y = 0.0;
			}else{
				//iniciar movimiento en dirección especificada
				play->velocity->direction->_z = -0.001;
			}
			break;
		case 'w':
			if(play->velocity->direction->_y != 0){
				//aumentar velocidad en +y
				play->velocity->direction->_y += speedUpInterval;
			}else if(play->velocity->direction->_x != 0 || play->velocity->direction->_z != 0){
				//cambiar la velocidad hacia +y
				play->velocity->direction->_y = fabs(play->speed());
				play->velocity->direction->_x = 0.0;
				play->velocity->direction->_z = 0.0;
			}else{
				//iniciar movimiento en dirección especificada
				play->velocity->direction->_y = 0.001;
			}
			break;
		case 'd':
			if(play->velocity->direction->_z != 0){
				//aumentar velocidad en +z
				play->velocity->direction->_z += speedUpInterval;
			}else if(play->velocity->direction->_x != 0 || play->velocity->direction->_y != 0){
				//cambiar la velocidad hacia +z
				play->velocity->direction->_z = fabs(play->speed());
				play->velocity->direction->_x = 0.0;
				play->velocity->direction->_y = 0.0;
			}else{
				//iniciar movimiento en dirección especificada
				play->velocity->direction->_z = 0.001;
			}
			break;
		case 's':
			if(play->velocity->direction->_y != 0){
				//aumentar velocidad en -y
				play->velocity->direction->_y -= speedUpInterval;
			}else if(play->velocity->direction->_x != 0 || play->velocity->direction->_z != 0){
				//cambiar la velocidad hacia -y
				play->velocity->direction->_y= (-1)*fabs(play->speed());
				play->velocity->direction->_x=0.0;
				play->velocity->direction->_z=0.0;
			}else{
				//iniciar movimiento en dirección especificada
				play->velocity->direction->_y = -0.001;
			}
			break;
		default:
			break;
	}
}


void Advance() {
	if(start){
		g->levels[currentLevel]->Advance();
		glutPostRedisplay();
	}
	player* play = g->levels[currentLevel]->players[0];
	assert(play->human);
	if(play->detectarColisionPelotaLadrillo(o, play) != 0){	//WARNING: test variable in use
		#pragma message ("USER-DEFINED WARNING: \"parallelepiped o\" (used by Advance() in main.cpp) is a test variable and must, eventually, be deleted")
		std::cerr<<"std"<<std::endl;
	}
	
}

//####################################INICIALIZACION DE TEXTURAS################################

GLint Xsize=500;
GLint Ysize=500;


GLvoid Transform(GLfloat Width, GLfloat Height) {
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,Width/Height,1.0,1000.0);
  	glMatrixMode(GL_MODELVIEW);
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLfloat Width, GLfloat Height) {
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);	
	glShadeModel(GL_SMOOTH);
  	//glEnable(GL_LIGHTING);
	Transform( Width, Height );

	// Texturas
	glGenTextures(1, &texPiso);
	glBindTexture(GL_TEXTURE_2D, texPiso);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	imagePiso = glmReadPPM("imagen1.ppm", &iwidth, &iheight);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidth, iheight,
		     0, GL_RGB, GL_UNSIGNED_BYTE, imagePiso);

	glEnable(GL_DEPTH_TEST);
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


int main(int argc, char **argv)
{
/*
 * para terminar con el movimiento del player hay que hacer que 
 * al presionar una tecla, entonces se cambie el vector velocidad
 * */
	if(argc>=2){
		g = loadGame(argv[1]);
	}else{
		cerr<<"No file was provided. Loading default game"<<endl;
		g = new Game(3, 1);

		obstacle** obs = new obstacle*[1];
		obs[0] = new obstacle();
		
		player** plys  = new player*[1];
		plys[0] = new player(3.5, new ray());
		plys[0]->human = true;
		plys[0]->rep->position->_x = -6.0;
		plys[0]->rep->position->_y =  3.5;
		
		CHECK_NULLSTRING;
		g->levels[0] = new Level(new Stage(2*D, 2*D, H), \
		                         new vector(-0.75*D, 0, -0.75*D, false), \
								 nullString, \
								 new heightMap(),
								 1,
								 obs,
								 1,
								 plys
								);
	}

	if(g){
		cerr<<"Loaded successfully the following game:"<<endl;
		g->preview();
	}else{
		cerr<<"could not load game"<<endl;
		return 1;
	}

	o = new parallelepiped(g->levels[currentLevel]->terrain);
	
	stageCam = new camera();

	currentCam = stageCam;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("TRoN legacy");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(handleKeypress);	
	glutKeyboardFunc(startPlaying);
	glutIdleFunc(Advance);

	cerr<<endl<<"* * * * * * * * * * * * * * * * *"<<endl\
	          <<"* Presione la barra espaciadora *"<<endl\
	          <<"* * * * * * * * * * * * * * * * *"<<endl;

	//ceder control a openGL
	glutMainLoop();

	return 0;             
}
