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

void HeadQuarter::add_HP(int hp) {
	HP_sum += hp;
	return;
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
                //设置初始位置和目的地
                A->destination = des;
                A->In_city = base;
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
                //设置初始位置和目的地
                A->destination = des;
                A->In_city = base;
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
                //设置初始位置和目的地
                A->destination = des;
                A->In_city = base;
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
                //设置初始位置和目的地
                A->destination = des;
                A->In_city = base;
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
                A->destination = des;
                A->In_city = base;
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
    std::cout <<"[DEBUG]" << name << " headquarter fail making warriors" << std::endl;
    return -1;
};

void HeadQuarter::create_warrior(int t) {
    int order;
    std::cout <<"00"<<t << "   ";
    if(is_stop_creating) {
        order = stop_creating_at;
	}
    else {
        order = stop_creating_at++;
        order = order % 5;
    }
    int res = follow_order_to_create(order);
    if (res != -1) {
        is_stop_creating = false;
        Warrior* p = list_of_warriors.back();
        std::cout << name << " ";
        show_kind_of_warrior(res);
        std::cout << " " << sum_cnt_warriors;
        std::cout << " born with HP " << p->get_HP() << ",";
        std::cout << cnt_of_different_warriors[res] << " ";
        show_kind_of_warrior(res);
        
        std::cout << " in " << name << " headquarter" << std::endl;
        p->print_info();
    }
        
    else {
        is_stop_creating = true;
        stop_creating_at = order;
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

std::vector<Warrior*> HeadQuarter::get_list_of_warriors() {
	return list_of_warriors;
};

void HeadQuarter::lion_run(int t,int min) {//t代表时间
    for (int i = 0; i < list_of_warriors.size(); i++) {
        if (list_of_warriors[i]->get_kind() == "lion") {
            lion* l = dynamic_cast<lion*>(list_of_warriors[i]);
            if (l->to_run) {
                std::cout << t << ":"<<min <<" ";
                l->print_name();
                std::cout<<" ran away"<<std::endl;
                list_of_warriors.erase(list_of_warriors.begin() + i);
            }
        }
    }
};

void HeadQuarter::march(int t,int min) {
    for (int i = 0; i < list_of_warriors.size(); i++) {
        if (list_of_warriors[i]->arrive_destination == false) {
            std::cout<<t<<":"<<min<<" ";
            if (list_of_warriors[i]->arrive_destination) {
                continue;
            }
            bool res =list_of_warriors[i]->step_on();
            if (res) {
                TakeDown++;
            }
        }
    }

}



void HeadQuarter::reward() {//由近至远奖励，应该倒序遍历vector数组
    for (int i = list_of_warriors.size()-1; i>=0; i--) {
        if (list_of_warriors[i]->is_winner == true) {
            if (HP_sum >= 8) {
                list_of_warriors[i]->add_HP(8);
                HP_sum -= 8;
            }
            else {//剩余HP不足奖励，退出
                return;
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

void HeadQuarter::report_hp() {
	std::cout << HP_sum << " elements in " << name << " headquarter" << std::endl;
	return;
};

void HeadQuarter::report_warrior(int t,int min) {
    for (int i = 0; i < list_of_warriors.size(); i++) {
        std::cout << t << ":" << min << " ";
		list_of_warriors[i]->report_weapon(); 
	}
};
