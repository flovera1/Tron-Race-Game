#include <stdlib.h> //atoi, atof
#include <string.h> //strlen
#include <iostream>	//cout, cerr, perror
#include <fstream>	//ifstream
using namespace std;

#include "vector.h"
#include "representation.h"
#include "parallelepiped.h"
#include "obstacle.h"
#include "player.h"
#include "heightMap.h"
#include "Level.h"
#include "Game.h"
#include "loadFile.h"

//Atajo para mostrar en pantalla el valor de una variable entera
#define	REVEAL(var)  	printf(#var " = %d\n", var)
//Atajo para mostrar en pantalla el valor de una variable con decimales
#define	REVEAL_F(var)	printf(#var " = %f\n", var)
//Atajo para mostrar en pantalla el valor de una variable con caracteres
#define	REVEAL_C(var)	printf(#var " = %s\n", var)

#define BUFF_SIZE	256

//crea un char* con el nombre dado en donde almacena la siguiente línea del archivo
#define READ(from, into)	\
	char* into = new char[BUFF_SIZE];\
	from->getline(into, BUFF_SIZE)

static int readInt(istream* f){
	READ(f, buff);
	return atoi(buff);
}

static float readFloat(istream* f){
	READ(f, buff);
	return atof(buff);
}

static char* readChars(istream* f){
	READ(f, buff);
	return buff;
}

static Level* loadLevel(istream* f, int id);

Game* loadGame(char* filename){
	ifstream* f = new ifstream();
	Game* out;
	int lives, levels;

	f->open(filename, ios::in);

	if( !f || !f->is_open() ){
		perror("could not open file");
		return NULL;
	}

	lives = readInt(f);
	levels = readInt(f);
	out = new Game(lives, levels);
	if(out->badBit){
		cerr<<"Error loading game"<<endl;
		return NULL;
	}
	for(int i=0; i < out->totalLevels; i++){
		out->levels[i] = loadLevel(f, i+1);
		if(out->levels[i] == NULL){
			cerr<<"Error loading level "<<i<<endl;
			return NULL;
		}
	}

	return out;
}

#define CHECK_PARAM(var, name, min, max, lvl) if(var<min || var>max)\
	cerr<<"WARNING IN LEVEL "<<lvl<<": "<<name<<" is "<<var<<"; should be between "<<min<<" and "<<max<<endl

static Stage* loadStage(istream* f, int id);	//id used for warning notification purposes
static vector* loadXZvector(istream* f);	//does not check for warnings
static heightMap* loadHeightMap(istream* f);	//does not check for warnings
static obstacle* loadObstacle(istream* f);
static player* loadHuman(istream* f);
static player* loadOpponent(istream* f);

static Level* loadLevel(istream* f, int id){	//id is used for warning notification purposes
	Stage* terrain = loadStage(f, id);

	vector* exit = loadXZvector(f);
	CHECK_PARAM(exit->X(), "Exit X coordinate", terrain->westWall->coord, terrain->eastWall->coord, id);
	CHECK_PARAM(exit->Z(), "Exit Z coordinate", terrain->southWall->coord, terrain->northWall->coord, id);

	char* sky = readChars(f);

	heightMap* map = loadHeightMap(f);
	CHECK_PARAM(map->length, "height map length", 0, terrain->length(), id);
	CHECK_PARAM(map->width, "height map width", 0, terrain->width(), id);
	CHECK_PARAM((map->height + map->position->Y()), "height map maximum height", 0, terrain->height(), id);
	CHECK_PARAM((map->position->X() - map->length/2), "left border of the height map (as given by X coordinate)", terrain->westWall->coord, terrain->eastWall->coord, id);
	CHECK_PARAM((map->position->X() + map->length/2), "right border of the height map (as given by X coordinate)", terrain->westWall->coord, terrain->eastWall->coord, id);
	CHECK_PARAM((map->position->Z() - map->width/2), "top border of the height map (as given by X coordinate)", terrain->southWall->coord, terrain->northWall->coord, id);
	CHECK_PARAM((map->position->Z() + map->width/2), "bottom border of the height map (as given by X coordinate)", terrain->southWall->coord, terrain->northWall->coord, id);

	//read obstacles
	int totalObstacles = readInt(f);
	obstacle** obs = new obstacle*[totalObstacles];
	for(int i=0; i<totalObstacles; i++){
		obs[i] = loadObstacle(f);
	}

	//read players
	player* p = loadHuman(f);
	p->human = true;

	int totalPlayers = readInt(f)+1;
	player** players = new player*[totalPlayers];
	players[0] = p;
	for(int i=1; i<totalPlayers; i++){
		p = loadOpponent(f);
		players[i] = p;
	}

	return new Level(terrain, exit, sky, map, totalObstacles, obs, totalPlayers, players);
}

static Stage* loadStage(istream* f, int id){
	float length = readFloat(f),
	      width  = readFloat(f),
		  height = readFloat(f);
	CHECK_PARAM(length, "terrain length", 50, 200, id);
	CHECK_PARAM(width,  "terrain width",  50, 200, id);
	CHECK_PARAM(height, "terrain height",  5, 200, id);
	return new Stage(length, width, height);
}

static vector* loadXZvector(istream* f){
	float x = readFloat(f),
	      z = readFloat(f);
	return new vector(x, 0.0, z, false);
}

heightMap* loadHeightMap(istream* f){
	cout<<"entered loadHeightMap"<<endl;
	char* file = readChars(f);
	float length = readFloat(f),
	      width  = readFloat(f),
	      maxHeight = readFloat(f),
		  minHeight = readFloat(f),
		  x = readFloat(f),
		  z = readFloat(f);

	return new heightMap(file, length, width, maxHeight, minHeight, x, z);
}

static vector* loadXYZvector(istream* f);
representation* loadRepresentation(istream* f);

static obstacle* loadObstacle(istream* f){
	representation* repr = loadRepresentation(f);

	int pathLength = readInt(f);
	vector** path = new vector*[pathLength];
	for(int i=0; i<pathLength; i++)
		path[i] = loadXYZvector(f);

	float speed = readFloat(f);

	return new obstacle(repr, pathLength, path, speed);
}

vector* loadXYZvector(istream* f){
	float x = readFloat(f),
	      y = readFloat(f),
		  z = readFloat(f);
	return new vector(x, y, z, false);
}

static parallelepiped* loadParallelepiped(istream* f);
static cylinder* loadCylinder(istream* f);
static sphere* loadSphere(istream* f);
static disk* loadDisk(istream* f);
static torus* loadTorus(istream* f);
static teapot* loadTeapot(istream* f);

representation* loadRepresentation(istream* f){
	char* typeLine = readChars(f);
	if(strlen(typeLine) > 1)
		cerr<<"WARNING: \""<<typeLine<<"\" was found in the representation type; only the first character will be processed."<<endl;
	else if(strlen(typeLine) < 1){
		cerr<<"FATAL ERROR: No data was found on the line expected to contain the representation type "<<endl;
		exit(EXIT_FAILURE);
	}
	char type = typeLine[0];
		
	switch(type){
		case 'p':
			return loadParallelepiped(f);
		case 'y':
			return loadCylinder(f);
		case 's':
			return loadSphere(f);
		case 'd':
			return loadDisk(f);
		case 't':
			return loadTorus(f);
		case 'u':
			return loadTeapot(f);
		default:
			cerr<<"FATAL ERROR: Representation type "<<type<<" is not recognized. Please check the file specification."; 
			exit(EXIT_FAILURE);
	}
}

static parallelepiped* loadParallelepiped(istream* f){
	float length = readFloat(f),
	      width  = readFloat(f),
		  height = readFloat(f);

	char* texture = readChars(f);

	return new parallelepiped(length, width, height, texture);
}

static cylinder* loadCylinder(istream* f){
	float baseRadius = readFloat(f),
	      topRadius = readFloat(f),
	      height = readFloat(f);

	char* texture = readChars(f);
	return new cylinder(baseRadius, topRadius, height, texture);
}

static sphere* loadSphere(istream* f){
	float radius = readFloat(f);

	char* texture = readChars(f);
	return new sphere(radius,texture);
}

static disk* loadDisk(istream* f){
	float radius = readFloat(f);

	char* texture = readChars(f);
	return new disk(radius,texture);
}

static torus* loadTorus(istream* f){
	float innerRadius = readFloat(f),
	      outerRadius = readFloat(f);

	char* texture = readChars(f);
	return new torus(innerRadius, outerRadius, texture);
}

static teapot* loadTeapot(istream* f){
	float size = readFloat(f);

	char* texture = readChars(f);
	return new teapot(size, texture);
}

static player* loadHuman(istream* f){
	representation* rep = loadRepresentation(f);
	vector* startingPoint = loadXZvector(f);
	
	float topSpeed = readFloat(f),
	      boostSpeed = readFloat(f),
		  boostDuration = readFloat(f),
		  boostCooling = readFloat(f);

	return new player(rep, startingPoint, topSpeed, boostSpeed, boostDuration, boostCooling);
}

static player* loadOpponent(istream* f){
	representation* rep = loadRepresentation(f);
	vector* startingPoint = loadXZvector(f);
	
	float topSpeed = readFloat(f);

	return new player(rep, startingPoint, topSpeed, topSpeed, 0, 0);
}

/*int main(int argc, char* argv[]){
	Game* g;
	if(argc<2){
		cerr<<"Error: a file is required"<<endl;
		exit(EXIT_FAILURE);
	}

	g = loadGame(argv[1]);
	if(g)
		g->preview();

	exit(EXIT_SUCCESS);
}
*/