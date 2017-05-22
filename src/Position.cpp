#include "Position.h"

using namespace std;

/**
* Position constructor
*/
Position::Position(unsigned long ID, double lat_deg, double lon_deg, double lat_rad, double lon_rad) {
	this->ID = ID;
	this->lat_deg = lat_deg;
	this->lon_deg = lon_deg;
	this->lat_rad = lat_rad;
	this->lon_rad = lon_rad;
}

unsigned long Position::getId() const {
	return ID;
}

double Position::getLatDeg() const {
	return lat_deg;
}

double Position::getLatRad() const {
	return lat_rad;
}

double Position::getLonDeg() const {
	return lon_deg;
}

double Position::getLonRad() const {
	return lon_rad;
}

bool Position::operator ==(const Position &n1) const {
	return (ID == n1.getId());
}

bool Position::operator !=(const Position &n1) const {
	return (ID != n1.getId());
}