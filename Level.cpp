#include <iostream>	//std::cout, NULL
#include "Level.h"
#include "representation.h"

#define EXIT_MARKER_LENGTH 10
#define EXIT_MARKER_WIDTH  10
#define EXIT_MARKER_HEIGHT 50

Level::Level(){
	this->terrain = new Stage();
	this->exit = new vector();

	CHECK_NULLSTRING;
	this->sky = nullString;

	this->map = new heightMap();
	this->totalObstacles = 0;
	this->obs = new obstacle*[0];
	this->totalPlayers = 0;
	this->players = new player*[0];
	this->exitMarker = NULL;
};

Level::Level(Stage* terrain, vector* exit, char* sky, heightMap* map, int totalObstacles, obstacle** obs, int totalPlayers, player** players){
	this->terrain = terrain;
	this->exit = exit;
	this->sky = sky;
	this->map = map;
	this->totalObstacles = totalObstacles;
	this->obs = obs;
	this->totalPlayers = totalPlayers;
	this->players = players;
	this->exitMarker = NULL;
};

void Level::preview(){
	this->terrain->preview();
	this->exit->preview();
	std::cout<<"Sky: "<<this->sky<<std::endl;
	this->map->preview();
	std::cout<<totalObstacles<<" obstacles"<<std::endl;
	for(int i=0; i < this->totalObstacles; i++){
		std::cout<<(i+1)<<") ";	//no end line intentionally
		this->obs[i]->preview();
	}
	std::cout<<totalPlayers<<" players"<<std::endl;
	for(int i=0; i < this->totalPlayers; i++){
		std::cout<<(i+1)<<") ";	//no end line intentionally
		this->players[i]->preview();
	}
};

void Level::draw(){
	this->terrain->draw(0.3, 0.3, .5);
	drawExit();
	//this->sky;
	//this->map->draw();
				
	for(int i=0; i < this->totalObstacles; i++)
		this->obs[i]->draw();
	
	for(int i=0; i < this->totalPlayers; i++)
		this->players[i]->draw();
	
};

void Level::drawExit(){
	if(this->exitMarker == NULL){
		CHECK_NULLSTRING;
		exitMarker = new parallelepiped(EXIT_MARKER_LENGTH, EXIT_MARKER_WIDTH, EXIT_MARKER_HEIGHT, nullString);
		exitMarker->initPos(exit);
	}

	exitMarker->draw();
};

//move everything the distance corresponding to teh time elapsed
void Level::Advance(){
	for(int i=0; i < this->totalObstacles; i++)
		this->obs[i]->Advance();
	
	for(int i=0; i < this->totalPlayers; i++)
		this->players[i]->Advance();

}

//put everything back where it was at the start of the level
void Level::reset(){
	for(int i=0; i < this->totalObstacles; i++){
		this->obs[i]->alive = true;
		this->obs[i]->reset();
	}

	for(int i=0; i < this->totalPlayers; i++){
		this->players[i]->alive = true;
		this->players[i]->reset();
	}
}

//must be called when movement starts
void Level::inic(){
	for(int i=0; i < this->totalObstacles; i++){
		this->obs[i]->inic();
	}

	for(int i=0; i < this->totalPlayers; i++){
		this->players[i]->inic();
	}
}