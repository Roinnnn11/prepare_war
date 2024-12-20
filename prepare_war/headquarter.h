#pragma once
#ifndef MOSHOU_H
#define MOSHOU_H
#include<iostream>
#include<vector>
#include"warrior.h"
#include"weapon.h"

class HeadQuarter {
private:
    std::string name;
    int HP_sum;
    int make_warrior_order[5];//0:dragon,1:ninja,...
    int sum_cnt_warriors = 0;
    int cnt_of_different_warriors[5] = { 0 };//不妨设顺序为dragon、ninja、iceman、lion、wolf
    std::vector<Warrior*> list_of_warriors;
    bool is_stop_creating = false;
public:
    HeadQuarter(int m, std::string new_name);
    ~HeadQuarter();
    void show_kind_of_warrior(int order);

    void set_order_for_HeadQuarter(int n);

    int follow_order_to_create(int order);

    void create_warrior(int t);

    bool get_is_stop_creating();

    int get_HPSUM();

    Warrior* get_warrior();

    void reward();//战斗之后发放奖励（对赢了的）
    void clear_dead();//清除死亡的武士
};


#endif