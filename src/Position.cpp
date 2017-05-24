#include "Position.h"

using namespace std;

/**
* Position constructor
*/
Position::Position(unsigned long ID, double lat_deg, double lon_deg) {
	this->ID = ID;
	this->lat_deg = lat_deg;
	this->lon_deg = lon_deg;
}

unsigned long Position::getId() const {
	return ID;
}

double Position::getLatDeg() const {
	return lat_deg;
}

double Position::getLonDeg() const {
	return lon_deg;
}

bool Position::operator ==(const Position &n1) const {
	return (ID == n1.getId());
}

bool Position::operator !=(const Position &n1) const {
	return (ID != n1.getId());
}