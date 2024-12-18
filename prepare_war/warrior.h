#pragma once
#ifndef WARRIOR_H
#define WARRIOR_H
#include<iostream>
#include<string>
#include"weapon.h"

class Warrior {
private:
    int ID;
    std::string kind;

protected:
    weapon* my_weapon;
    double power;

public:
    std::string belong_headquater; //所属方
    int In_city;//所在的城市编号
    bool is_winner = false;//标记胜利的武士
    bool is_dead = false;//标记死亡的武士
    int my_hp;
    
    void set_id(int num);
    void set_kind(std::string k);
    int get_id(); 
    std::string get_weapon();
    std::string get_kind();
    void add_HP(double a);
    void step_on(int n);//前进
    weapon* lost_weapon();//掉落weapon（专门针对wolf）
    virtual bool use_weapon();//计算对武器的使用
    virtual double start_war();//主动攻击
    virtual bool get_hurt(double hurt);//受伤，并判断是否死亡
    virtual double fight_back();//发起反击
    virtual int get_HP() const = 0;
    virtual  void print_info() const= 0;
};

void Add_hp_to_warrior(Warrior* w, double hp);

class dragon : public Warrior {
private:
    float morale;//士气
public:
    
    dragon(int id);
    void set_morale(int res_life);//传入参数:剩余生命元
    void set_weapon_forme();//为其创建武器
    int get_HP() const override {
        return HP;
    };
    int get_morale();
    static int HP;
    void print_info()const override {
        std::cout << "It has a " << this->my_weapon->kind << ",and it's morale is " << this->morale << std::endl;
    };
    void yell(bool win);//三种情况：赢了欢呼加士气，没死欢呼减士气
};


class ninja : public Warrior {
private:
    weapon* my_weapon2;
public:
    ninja(int id);
    static int HP;
    void set_weapon();
    int get_HP() const override {
        return HP;
    };
    void print_info()const override {
        std::cout << "It has a " << this->my_weapon->kind << " and a " << this->my_weapon2->kind << std::endl;
    };
};

class iceman : public Warrior {
private:
public:
    int step;//记录雪人前进步数
    iceman(int id);
    void set_weapon();
    static int HP;
    int get_HP() const override {
        return HP;
    };
    void print_info()const override {
        std::cout << "It has a " << this->my_weapon->kind << std::endl;
    };
    void decrease_life();//根据前进步数，对雪人状态更新
};

class lion : public Warrior {
private:
    int loyality;
public:
    bool to_run = false;//一旦为true，则触发逃跑
    double K;//忠诚度下降的值
    static int HP;
    double life_to_transfer;//战败后保存的生命

    lion(int id);
    void set_loyality(int i);
    int get_HP() const override {
        return HP;
    };
    void print_info()const override {
        std::cout << "It's loyalty is" << this->loyality << std::endl;
    };
    void decrease_loyality();
};

class wolf : public Warrior {
public:
    wolf(int id);
    static int HP;
    int get_HP() const override {
        return HP;
    };
    void print_info()const override {

    };
    void pick_weapon(weapon* w);//捡起武器
};


#endif