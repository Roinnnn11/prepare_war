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
	bool war();//战争,为false说明平局
	void judge_yell();//判断是否有dragon以及是否发生yell
	void judge_transfer();//对是否存在lion以及发生转移生命值
	void judge_pick();//对wolf是否捡起武器
	void judge_loyality();//对lion忠诚度下降
};

#endif // !CITY_H
