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

public:
	Position(unsigned long ID, double lat_deg, double lon_deg);
	unsigned long getId() const;
	double getLatDeg() const;
	double getLonDeg() const;
	bool operator ==(const Position &p1) const;
	bool operator !=(const Position &p1) const;
};

#endif