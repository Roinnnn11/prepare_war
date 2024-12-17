#include"warrior.h"

void Warrior::set_id(int num) {
    ID = num;
    return;
};
void Warrior::set_kind(std::string k) {
    kind = k;
}

std::string Warrior::get_weapon() {
    return my_weapon->kind;
}

std::string Warrior::get_kind() {
    return kind;
}

int Warrior::get_id() {
    return ID;
}


double Warrior::start_war() {//进行主动攻击，返回值为造成的伤害
    double hurt = power;
    bool is_lost=false;
    if (my_weapon == nullptr) {
        return hurt;
    }
    if (my_weapon->kind == "sword") {
        hurt += my_weapon->power;
        sword* s = dynamic_cast<sword*>(my_weapon);
        is_lost = s->lost_weapon();
    }
    //std::cout << "[DEBUG]主动攻击测试"<<hurt << std::endl;
    //std::cout << "[DEBUG]武器类型" << my_weapon.kind <<my_weapon.power<< std::endl;
    if (is_lost) {
        delete my_weapon;
        my_weapon = nullptr;
    }
    return hurt;
}

bool Warrior::use_weapon() {
    if (my_weapon == nullptr) {
        return true;
    }
   /* bool is_lost;
    if (my_weapon->kind == "sword") {
        sword* s = dynamic_cast<sword*>(my_weapon);
        is_lost = s->lost_weapon();
    }
    else if (my_weapon->kind == "bomb") {
        bomb* b = dynamic_cast<bomb*>(my_weapon);
        is_lost = b->lost_weapon();
    }
    else if (my_weapon->kind == "arrow") {
        arrow* a = dynamic_cast<arrow*>(my_weapon);
        is_lost = a->lost_weapon();
    }
    is_lost = is_lost_weapon(&my_weapon);
    if (is_lost) {

        std::cout << "失去了武器" << std::endl;
        delete my_weapon;
        my_weapon = nullptr;
    }*/
}

bool Warrior::get_hurt(double hurt) {
    this->HP -= hurt;
    if (this->HP < 0) {
        std::cout << "[PROCESS]该武士死亡" << std::endl;
        return true;
    }
    return false;
}

double Warrior::fight_back() {//进行反击
    double hurt = int(power/2);
    if (my_weapon->kind == "sword") {
        hurt += my_weapon->power;
    }
    return hurt;
}

void dragon::set_weapon_forme() {
    int id = get_id();
    //std::cout << "[DEBUG]ID:" << id << std::endl;
    int choice = id % 3;
    my_weapon = create_weapon(choice,power);
    return;
}

dragon::dragon(int id) {
    power = 1;
    set_id(id);
    set_weapon_forme(); 
    //std::cout << "[DEBUG]WEAPON:" << this->my_weapon.kind << std::endl;
}

void dragon::set_morale(int res_life) {
    morale = (1.0 * res_life) / (1.0 * HP);
}
int dragon::get_morale() {
    return morale;
}

void dragon::yell(bool win) {
    if (win) {
        morale += 0.2;
    }
    else {
        morale -= 0.2;
    }
    if (morale > 0.8) {
        std::cout << "yelled at " << In_city << std::endl;
    }
}

void ninja::set_weapon() {
    int id = get_id();
    int choice1 = id % 3;
    int choice2 = (id + 1) % 3;
    my_weapon = create_weapon(choice1,power);
    my_weapon2 = create_weapon(choice2,power);

}
ninja::ninja(int id) {
    power = 20;
    set_id(id);
    set_weapon();
    //std::cout << "[DEBUG]NINJA_W1:" << this->my_weapon.kind << std::endl;
    //std::cout << "[DEBUG]NINJA_W1:" << this->my_weapon2.kind << std::endl;
}



void iceman::set_weapon() {
    int id = get_id();
    int choice = id % 3;
    my_weapon = create_weapon(choice,power);
    return;
}

iceman::iceman(int id) {
    power = 20;
    set_id(id);
    set_weapon();
}

void lion::set_loyality(int i) {
    loyality = i;
}

lion::lion(int id) {
    power = 20;
    set_id(id);
}

wolf::wolf(int id) {
    power = 20;
    set_id(id);
}
