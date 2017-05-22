#pragma once

//Vertices
#ifndef Position_H_
#define Position_H_

#include <vector>
#include <string>
#include <iostream>

class Position {
	unsigned long ID;
	double lat_deg;
	double lon_deg;
	double lat_rad;
	double lon_rad;

public:
	Position(unsigned long ID, double lat_deg, double lon_deg, double lat_rad, double lon_rad);
	unsigned long getId() const;
	double getLatDeg() const;
	double getLatRad() const;
	double getLonDeg() const;
	double getLonRad() const;
	bool operator ==(const Position &p1) const;
	bool operator !=(const Position &p1) const;
};

#endif