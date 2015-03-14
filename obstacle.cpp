#include "timer.h"	//SMTKU (under windows, this includes windows.h, which must be put before anything else)
#include <iostream>	//cout
#include "MATH.h"
#include "obstacle.h"

obstacle::obstacle(){
	//public variables
	rep = new sphere();

	this->pathLength = 1;
	this->path = new vector*[1];
	this->path[0] = new vector();

	this->speed = 0;

	//private variables not set by reset
	velocity = new ray();

	this->reset();	//initializes indexIncreasing, rep->position, nexPointIndex, lastReestimate and ETA
}

obstacle::obstacle(representation* representation, int pathLength, vector** path, double speed){
	//public variables
	rep = representation;
	this->pathLength = pathLength;
	this->path = path;
	this->speed = speed;

	//private variables
	velocity = new ray();
	this->reset();	//initializes indexIncreasing, rep->position, nexPointIndex, lastReestimate and ETA
}

void obstacle::draw(){
	rep->draw();
}

void obstacle::preview(){
	std::cout<<"Obstacle"<<std::endl;
	rep->preview();
	std::cout<<pathLength<<"-point path:"<<std::endl;
	for(int i=0; i<pathLength; i++){
		std::cout<<"\t"<<(i+1)<<") ";	//no end-of-line is intentional
		path[i]->preview();
	}
	std::cout<<"\tat "<<this->speed<<" units per second"<<std::endl;
}

//moves this element the distance corresponding to the elapsed time, if need be
void obstacle::Advance(){
	//std::cerr<<"entered Obstacle advance for ";
	//this->preview();

	if(this->pathLength == 0 || speed == 0)
		return;
	
	//if(colisión)
	//	reverseDirection();

	//std::cerr<<"Next point is "<<this->path[nextPointIndex]->dist(rep->position)<<" units away and I gotta get there in "<<ETA<<" seconds"<<std::endl;

	if( this->path[nextPointIndex]->dist(rep->position) < this->speed //will reach or pass next point within the next second
	    || secondsElapsed(lastReestimate) > ETA	//we must've miscalculated, as we've passed it.
	  )
		reestimateVelocity();

	this->movement(rep->position, velocity);
	//std::cerr<<"exited Obstacle Advance"<<std::endl;
}

//changes the direction on the path this obstacle is heading down
void obstacle::reverseDirection(){
	if(this->indexIncreasing){
		this->indexIncreasing = false;
		this->nextPointIndex -= 1;
	}else{
		this->indexIncreasing = true;
		this->nextPointIndex += 1;
	}
	this->nextPointIndex %= this->pathLength;
	reestimateVelocity();
}

//adjusts velocity vector to better fit the path, redirecting the object to the next point on it
void obstacle::reestimateVelocity(){
	std::cerr<<"reestimating velocity for ";
	preview();

	if(this->indexIncreasing){
		this->nextPointIndex++;
	}else{
		this->nextPointIndex--;
	}
	this->nextPointIndex %= this->pathLength;
	std::cerr<<"heading to point "<<nextPointIndex<<std::endl;

	this->path[nextPointIndex]->preview();
	//free(velocity->direction);
	velocity->direction = headTo(rep->position, this->path[nextPointIndex], speed);
	std::cerr<<"along ";
	velocity->direction->preview();
	
	CURR_TIME(lastReestimate);
	ETA = this->path[nextPointIndex]->dist(rep->position) / speed;
	std::cerr<<"which should take "<<ETA<<" seconds"<<std::endl;
}

void obstacle::reset(){
	this->indexIncreasing = true;
	rep->initPos( new vector(path[0]) );
	this->nextPointIndex = -1;	//incremented to 0 by reestimateVelocity
	this->reestimateVelocity();
}

//start movement timers
void obstacle::inic(){
	CURR_TIME(lastTranslation);
	CURR_TIME(lastReestimate);
}