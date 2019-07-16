#pragma once
#include <windows.h>


#ifndef CHARACTER_INFO
#define CHHARACTER_INFO

class Character {
private:
	DWORD memLocation;

	DWORD position;
	DWORD altitude;
public:
	Character(DWORD memLocation);
	~Character();

	DWORD getMemLocation();
	DWORD getPosition();
	DWORD getAltitude();

	void setMemLocation(DWORD pointer);
	void setAltitude(DWORD altitude);
	void setPosition(DWORD position);
};

#endif // !CHARACTER_INFO
