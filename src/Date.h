#pragma once

#ifndef DATE_H_
#define DATE_H_
#include <iostream>

using namespace std;

class Date {
	int hour;
	int min;
public:
	Date();
	Date(int hour, int min);
	int getHour() const;
	int getMin() const;
	bool operator <(const Date d1) const;
	bool operator ==(const Date d1) const;
};

#endif /* DATE_H_ */