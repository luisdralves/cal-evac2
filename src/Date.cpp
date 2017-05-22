#include "Date.h"

Date::Date() {
	this->hour = 0;
	this->min = 0;
}

/**
* Date constructor
*/
Date::Date(int hour, int min) {
	this->hour = hour;
	this->min = min;
}

int Date::getHour() const {
	return hour;
}

int Date::getMin() const {
	return min;
}

bool Date::operator <(const Date d1) const {
	if (hour == d1.getHour())
		return (min < d1.getMin());
	else
		return hour < d1.getHour();
}

bool Date::operator ==(const Date d1) const {
	if (hour == d1.getHour() && min == d1.getMin())
		return true;
	return false;
}