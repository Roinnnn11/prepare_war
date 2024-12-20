#pragma once
#ifndef CITY_H
#define CITY_H
#include<iostream>
#include"warrior.h"
#include<vector>
#include<string>
class city {
private: 
	int HP;
	int ID;
	bool is_flag;
	std::string flag;
	bool have_bomb;//判断武士是否有bomb
	bool have_arrow;//判断是否有arrow
	bool who_to_start;//为true则红方开始

	bool red_win;//判断红方是否胜利
	bool blue_win;//判断蓝方是否胜利
public:
	city(int i);
	Warrior* red_warrior;
	Warrior* blue_warrior;
	void create_HP();
	void enter_city(Warrior* w);//武士进入城市，记录其信息
	void to_start_war();//战争的整个过程
	bool predict_bomb();//持有炸弹的进行预判
	void use_bomb();//使用炸弹，双方死亡
	void use_arrow();//使用箭
	void who_start();//判断红方进攻/蓝方进攻,true为红
	bool war();//战争,为false说明平局

	//战争后的判定
	void judge_yell();//判断是否有dragon以及是否发生yell
	void judge_transfer();//对是否存在lion以及发生转移生命值
	void judge_pick();//对wolf是否捡起武器
	void judge_loyality();//对lion忠诚度下降
	void to_flag();//判断是否插旗
	int took_HP();//胜利一方获得的生命元
};


class cities {
private:
	std::vector<city> city_list;
public:
	cities(int n);
};
#endif // !CITY_H
