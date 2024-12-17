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

void Warrior::add_HP(double a) {
    my_hp += a;
    return;
}

void Add_hp_to_warrior(Warrior* w, double hp) {
    w->my_hp += hp;
    return;
}

weapon* Warrior::lost_weapon() {
    return my_weapon;
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

    if (this->my_hp-hurt<= 0) {
        if (this->get_kind() == "lion") {
            lion* l = dynamic_cast<lion*>(this);
            l->life_to_transfer = l->my_hp;
        }
        std::cout << "[PROCESS]该武士死亡" << std::endl;
        this->my_hp = 0;
        return true;
    }
    this->my_hp -= hurt;
    return false;
}

double Warrior::fight_back() {//进行反击
    //加入ninja不反击的判断
    if (kind == "ninja") {
        return 0;
    }
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
    my_hp = HP;
    power = 1;
    set_id(id);
    set_weapon_forme(); 
    this->set_kind("dragon");
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
    my_hp = HP;
    power = 20;
    set_id(id);
    set_weapon();
    this->set_kind("ninja");
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
    my_hp = HP;
    power = 20;
    set_id(id);
    set_weapon();
    this->set_kind("iceman");
}

void iceman::decrease_life() {//在前进后调用
    if (step % 2 == 0) {
        if (HP > 9) {
            HP -= 9;
            power += 20;
        }
        else {
            HP = 1;
            power += 20;
        }
    }
    else {
        return;
    }
    
}

void lion::set_loyality(int i) {
    loyality = i;
}

void lion::decrease_loyality() {
    loyality -= K;
    if (loyality <= 0) {
        to_run = true;
    }
    return;
}

lion::lion(int id) {
    my_hp = HP;
    power = 20;
    set_id(id);
    set_kind("lion");
}

wolf::wolf(int id) {
    my_hp = HP;
    power = 20;
    set_id(id);
    set_kind("wolf");
}

void wolf::pick_weapon(weapon* w) {
    this->my_weapon = w;
    return;
}