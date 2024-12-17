#pragma once
#ifndef CITY_H
#define CITY_H
#include"warrior.h"
#include<string>
class city {
private:
	int HP;
	int ID;
	bool is_flag;
	std::string flag;

public:
	Warrior* red_warrior;
	Warrior* blue_warrior;
	void to_start_war();
	void war();
};

#endif // !CITY_H
