#include<iostream>
#include<vector>
#include"headquarter.h"

HeadQuarter::HeadQuarter(int m, std::string new_name) {
    HP_sum = m;
    name = new_name;
};

HeadQuarter:: ~HeadQuarter() {
    HeadQuarter::list_of_warriors.clear();
};

void HeadQuarter::show_kind_of_warrior(int order) {
    if (order == 0)    std::cout << "dragon";
    if (order == 1)    std::cout << "ninja";
    if (order == 2)    std::cout << "iceman";
    if (order == 3)    std::cout << "lion";
    if (order == 4)    std::cout << "wolf";
    return;
};

void HeadQuarter::set_order_for_HeadQuarter(int n) {
    if (n == 0) {
        make_warrior_order[0] = 2; make_warrior_order[1] = 3;
        make_warrior_order[2] = 4; make_warrior_order[3] = 1;
        make_warrior_order[4] = 0;
        return;
    }
    if (n == 1) {
        make_warrior_order[0] = 3; make_warrior_order[1] = 0;
        make_warrior_order[2] = 1; make_warrior_order[3] = 2;
        make_warrior_order[4] = 4;
        return;
    }
    std::cout << "依次输入武士类型" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::string s;
        std::cin >> s;
        if (s == "dragon") {
            make_warrior_order[i] = 0;
            continue;
        }
        if (s == "ninja") {
            make_warrior_order[i] = 1;
            continue;
        }
        if (s == "iceman") {
            make_warrior_order[i] = 2;
            continue;
        }
        if (s == "lion") {
            make_warrior_order[i] = 3;
            continue;
        }
        if (s == "wolf") {
            make_warrior_order[i] = 4;
            continue;
        }
        std::cout << "上一个输入错误，请重试" << std::endl;
        i--;
    }
};

int HeadQuarter::follow_order_to_create(int order) {
    int cnt_fail_to_create = 0;
    while (cnt_fail_to_create < 4) {
        int kind_of_warrior = make_warrior_order[order];
        Warrior* A = nullptr;
        //不妨设顺序为dragon、ninja、iceman、lion、wolf
        switch (kind_of_warrior)
        {
        case 0:
            A = new dragon(++sum_cnt_warriors);
            
            if (HP_sum < A->get_HP()) {
                sum_cnt_warriors--;
                delete A;
                break;
            }
            else {
                A->belong_headquater = this->name;
                A->set_kind("dragon");
                HP_sum -= A->get_HP();
                dragon* d = dynamic_cast<dragon*>(A);
                    d->set_morale(HP_sum);  // 仅在 new_warrior 确实是 dragon 时调用
                    //std::cout << "[DEBUG]MORALE" << d->get_morale() << std::endl;
                list_of_warriors.push_back(A);
                //delete[]A;
                cnt_of_different_warriors[kind_of_warrior]++;
                return 0;
            }
            break;
        case 1:
            A = new ninja(++sum_cnt_warriors);
            if (HP_sum < A->get_HP()) {
                sum_cnt_warriors--;
                delete A;
                break;
            }
            else {
                A->belong_headquater = this->name;
                HP_sum -= A->get_HP();
                list_of_warriors.push_back(A);
                cnt_of_different_warriors[kind_of_warrior]++;
                return 1;
            }
            break;
        case 2:
            A = new iceman(++sum_cnt_warriors);
            if (HP_sum < A->get_HP()) {
                sum_cnt_warriors--;
                delete A;
                break;
            }
            else {
                A->belong_headquater = this->name;
                HP_sum -= A->get_HP();
                list_of_warriors.push_back(A);
                cnt_of_different_warriors[kind_of_warrior]++;
                return 2;
            }
            break;
        case 3:
            A = new lion(++sum_cnt_warriors);

            if (HP_sum < A->get_HP()) {
                sum_cnt_warriors--;
                 delete A;
                break;
            }
            else {
                A->belong_headquater = this->name;
                HP_sum -= A->get_HP();
                lion* l = dynamic_cast<lion*>(A);
                l->set_loyality(HP_sum);
                list_of_warriors.push_back(A);
                cnt_of_different_warriors[kind_of_warrior]++;
                return 3;
            }
            break;
        case 4:
            A = new wolf(++sum_cnt_warriors);
            if (HP_sum < A->get_HP()) {
                sum_cnt_warriors--;
                delete A;
                break;
            }
            else {
                A->belong_headquater = this->name;
                HP_sum -= A->get_HP();
                list_of_warriors.push_back(A);
                cnt_of_different_warriors[kind_of_warrior]++;
                return 4;
            }
            break;
        default:
            std::cout << "发生错误" << std::endl;
            return -1;
            break;
        }
        order++; cnt_fail_to_create++;
        order = order % 5;
    }

    std::cout << name << " headquarter stop making warriors" << std::endl;
    return -1;
};

void HeadQuarter::create_warrior(int t) {
    int order = t % 5;
    std::cout <<"00"<<t << "   ";
    int res = follow_order_to_create(order);
    if (res != -1) {
        Warrior* p = list_of_warriors.back();
        std::cout << name << " ";
        show_kind_of_warrior(res);
        std::cout << " " << sum_cnt_warriors;
        std::cout << " born with HP " << p->get_HP() << ",";
        std::cout << cnt_of_different_warriors[res] << " ";
        show_kind_of_warrior(res);
        
        std::cout << " in " << name << " headquarter" << std::endl;
        p->print_info();
        p->start_war();
 
    }
        
    else {
        is_stop_creating = true;
        return;
    }
};

bool HeadQuarter::get_is_stop_creating() {
    return is_stop_creating;
};

int HeadQuarter::get_HPSUM() {
    return HP_sum;
};

Warrior* HeadQuarter::get_warrior() {
    return list_of_warriors.front();
};

void HeadQuarter::reward() {
    for (int i = 0; i < list_of_warriors.size(); i++) {
        if (list_of_warriors[i]->is_winner == true) {
            if (HP_sum >= 8) {
                list_of_warriors[i]->add_HP(8);
                HP_sum -= 8;
            }
        }
	}
};

void HeadQuarter::clear_dead() {
    for (int i = 0; i < list_of_warriors.size(); i++) {
        if (list_of_warriors[i]->is_dead == true) {
			list_of_warriors.erase(list_of_warriors.begin() + i);
			i--;
		}
	}
};  