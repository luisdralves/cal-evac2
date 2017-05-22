#include "Street.h"

/**
* Street constructor
*/
Street::Street(unsigned long ID, string name, bool two_way) {
	this->ID = ID;
	this->name = name;
	this->two_way = two_way;
	this->acessible = true;
}

unsigned long Street::getID() const {
	return ID;
}

string Street::getName() const {
	return name;
}
void Street::block() {
	this->acessible = false;
}

bool Street::getState() const {
	return acessible;
}

bool Street::is_two_way() const {
	return two_way;
}

bool Street::operator ==(const Street s1) const {
	return ID == s1.getID();
}