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
    int stop_creating_at=0;
public:
    int des;//目的地，红方为n+1，蓝方为0
    int base;//基地位置，红方为0，蓝方为n+1
    int TakeDown;//进入对方基地的武士个数
    HeadQuarter(int m, std::string new_name);
    ~HeadQuarter();
    void show_kind_of_warrior(int order);

    void set_order_for_HeadQuarter(int n);

    int follow_order_to_create(int order);

    void create_warrior(int t);

    bool get_is_stop_creating();

    int get_HPSUM();
    std::vector<Warrior*> get_list_of_warriors();
    Warrior* get_warrior();
    void add_HP(int hp);
    //按照时间点的一系列操作
    void lion_run(int t,int min);//狮子逃跑
    void march(int t,int min);//武士前进
    
    void reward();//战斗之后发放奖励（对赢了的）
    void clear_dead();//清除死亡的武士
    void report_hp();//汇报生命元
    void report_warrior(int t,int min);//让武士汇报武器情况
};


#endif