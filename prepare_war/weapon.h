#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include<iostream>
class weapon {

public:
    double power;
    std::string kind;
    void operator=(const weapon& w);
    virtual bool lost_weapon() {//如果为true，则视为武士不再拥有武器
        return true;
    };
    virtual ~weapon() {
        kind.clear();
        power = 0;
    }
};
class sword : public weapon {
private:
public:
    sword() {
        power = 0;
        kind.assign("sword");
    }
    ~sword() { }
    bool lost_weapon() override{//在每次使用武器之后，调用这个函数判断武器是否仍然存在
        power = int(power * 0.8);
        if (power <= 0) {
            return true;
        }
        return false;
    }

};
class bomb : public weapon {
private:

public:
    bomb() {
        power = 20;
        kind.assign("bomb");
    }
   
};
class arrow : public weapon {
private:
public:
    int used_cnt;//使用次数
    arrow() {
        power = 5;
        used_cnt = 0;
        kind.assign("arrow");
    }

    bool lost_weapon()override {//在每次使用武器之后，调用这个函数判断武器是否仍然存在
        used_cnt++;
        std::cout << "[DEBUG]我有被调用" << std::endl;
        if (used_cnt == 3) {
            return true;
        }
        return false;
    };
};
weapon* create_weapon(int choice, int p);
bool is_lost_weapon(weapon* w);
#endif