#include "Character.h"


Character::Character(DWORD memLocation) {
	this->memLocation = memLocation;
}

Character::~Character() {
	free(&(this->memLocation));
	free(&(this->position));
	free(&(this->altitude));
}


DWORD Character::getAltitude() {
	return this->altitude;
}

DWORD Character::getPosition() {
	return this->position;
}

DWORD Character::getMemLocation() {
	return this->memLocation;
}

void Character::setAltitude(DWORD altitude) {

	this->altitude = altitude;

}

void Character::setPosition(DWORD position) {

	this->position = position;

}

void Character::setMemLocation(DWORD memLocation) {

	this->memLocation = memLocation;

}