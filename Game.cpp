#include <iostream>	//cout

#include "Game.h"

bool isNatural(int i){
	return(i>0);
}

Game::Game(){
	this->totalLives = 0;
	this->totalLevels = 0;
	this->levels = new Level*[0];
	this->badBit = false;
}

Game::Game(int lives, int levels){
	if(!isNatural(lives)){
		std::cerr<<"Number of lives must be a natural number"<<std::endl;
		this->badBit = true;
	}
	this->totalLives = lives;

	if(!isNatural(levels)){
		std::cerr<<"Number of levels must be a natural number"<<std::endl;
		this->badBit = true;
	}
	this->totalLevels = levels;
	this->levels = new Level*[totalLevels];
	this->badBit = false;
}

void Game::preview(){
	std::cout<<this->totalLives<<" lives"<<std::endl;
	std::cout<<this->totalLevels<<" levels"<<std::endl;
	for(int i=0; i < this->totalLevels; i++){
		std::cout<<"-~LEVEL "<<(i+1)<<"~-"<<std::endl;
		levels[i]->preview();
	}
}
