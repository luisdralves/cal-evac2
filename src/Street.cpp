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

bool Street::operator <(const Street s1) const {
	return ID < s1.getID();
}

int Street::getIntersection(Street that, set<pair<Street, pair<int, int>>> streets) {
	unsigned long long id1, id2, id3, id4;
	for(auto i = streets.begin(); i != streets.end(); i++) {
		if (i->first.getName() == this->getName()) {
			id1 = i->second.first;
			id2 = i->second.second;
			for(auto i = streets.begin(); i != streets.end(); i++) {
				if (i->first.getName() == that.getName()) {
					id3 = i->second.first;
					id4 = i->second.second;
					if (id1 == id3) {
						return id1;
					} else if (id1 == id4) {
						return id1;
					} else if (id2 == id3) {
						return id2;
					} else if (id2 == id4) {
						return id2;
					}
				}
			}
		}
	}
	return -1;
}