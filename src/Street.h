#pragma once

//Edges
#ifndef STREET_H_
#define  STREET_H_

#include <string>

using namespace std;

class Street {
	unsigned long ID;
	string name;
	bool two_way;
	bool acessible;
public:
	Street(unsigned long ID, string name, bool two_way);
	unsigned long getID() const;
	bool is_two_way() const;
	string getName() const;
	void block();
	bool getState() const;
	bool operator ==(const Street s1) const;
};


#endif