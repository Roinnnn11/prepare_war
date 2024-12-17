#include"weapon.h"
void weapon::operator=(const weapon& w) {
    this->power = w.power;
    this->kind = w.kind;
}

weapon* create_weapon(int choice,int p) {
    weapon* w_forme = nullptr;
    switch (choice)
    {
    case 0:
        w_forme = new sword();
        w_forme->power = p / 5;
        break;
    case 1:
        w_forme = new bomb();
        break;
    case 2:
        w_forme = new arrow();
        break;
    default:
        std::cout << "´íÎó£¬Ìø¹ý" << std::endl;
        return w_forme;

    }
   
    return w_forme;
}

//bool is_lost_weapon(weapon* w) {
//    bool is_lost;
//    if (w->kind == "sword") {
//        sword* s = dynamic_cast<sword*>(w);
//        is_lost = s->lost_weapon();
//        
//    }
//    else if (w->kind == "bomb") {
//        std::cout << "[DEBUG]Actual type: " << typeid(*w).name() << std::endl;
//        bomb* b = dynamic_cast<bomb*>(w);
//        is_lost = b->lost_weapon();
//    }
//    else {
//        arrow* a = dynamic_cast<arrow*>(w);
//        is_lost = a->lost_weapon();
//    }
//    return is_lost;
//}