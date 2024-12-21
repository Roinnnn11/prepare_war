#include"city.h"
#include"warrior.h"
void city::create_HP() {
	HP += 10;
};

city::city(int i) {
	ID = i;
	red_warrior = nullptr;
	blue_warrior = nullptr;
	have_bomb = false;
	have_arrow = false;
	who_to_start = false;
	red_win = false;
	blue_win = false;
}
	


void city::enter_city(Warrior* w) {
	if (w->belong_headquater == "RED") {
		red_warrior = w;
	}
	if (w->belong_headquater == "BLUE") {
		blue_warrior = w;
	}

	if (w->get_kind() == "wolf") {//如果是狼，对其特判，具有什么武器
		wolf* wf = dynamic_cast<wolf*>(w);;
		if (wf->have_bomb) {
			have_bomb = true;
		}
		if (wf->have_arrow) {
			have_arrow = true;
		}
		return;
	}

	if (w->get_weapon() == "bomb") {
		have_bomb = true;
	}
	if (w->get_weapon() == "arrow") {
		have_arrow = true;
	}
}

bool city::predict_bomb() {
	if (blue_warrior->get_weapon() != "bomb" && red_warrior->get_weapon() != "bomb") {//没有炸弹
		return false;//返回不使用
	}
	double hurt1,hurt2;
	if (red_warrior->get_weapon() == "bomb" && who_to_start) {//红方拥有炸弹&&发起进攻
		hurt1 = red_warrior->start_war();
		if (blue_warrior->get_HP() <= hurt1) {//蓝方必死
			return false;
		}
		else {
			hurt2 = blue_warrior->fight_back();
			if (red_warrior->get_HP() <= hurt2) {//红方受反击而死
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (red_warrior->get_weapon() == "bomb" && !who_to_start) {//红方拥有炸弹&&反击
		hurt1 = blue_warrior->start_war();
		if (red_warrior->get_HP() <= hurt1) {
			return true;
		}
		else {
			return false;
		}
	}
	//红蓝交换
	if (blue_warrior->get_weapon() == "bomb" && !who_to_start) {//blue方拥有炸弹&&发起进攻
		hurt1 = blue_warrior->start_war();
		if (red_warrior->get_HP() <= hurt1) {//red方必死
			return false;
		}
		else {
			hurt2 = red_warrior->fight_back();
			if (blue_warrior->get_HP() <= hurt2) {//blue方受反击而死
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (blue_warrior->get_weapon() == "bomb" && who_to_start) {//blue方拥有炸弹&&反击
		hurt1 = red_warrior->start_war();
		if (blue_warrior->get_HP() <= hurt1) {
			return true;
		}
		else {
			return false;
		}
	}
}

void city::use_bomb(int t,int min) {
	std::cout << t << ":" << min << " ";
	if (red_warrior->get_weapon() == "bomb") {
		red_warrior->print_name();
		std::cout <<  "used a bomb and killed ";
		blue_warrior->print_name();	
	}
	if (blue_warrior->get_weapon() == "bomb") {
		blue_warrior->print_name();
		std::cout << "used a bomb and killed ";
		red_warrior->print_name();
	}
	std::cout << std::endl;
	red_warrior->is_dead = true;
	blue_warrior->is_dead = true;
	red_warrior = nullptr;
	blue_warrior = nullptr;
}

void city::use_arrow() {
	if (red_warrior->get_weapon() == "arrow"&&(red_warrior->destination-red_warrior->In_city)>1) {

	}
}

void city::who_start() {
	if ((is_flag && flag == "RED") || (!is_flag && ID % 2 != 0)) {
		who_to_start = true;
	}
	else {
		who_to_start = false;
	}
}

bool city::war() {
	bool res = true;
	double hurt1, hurt2;//两者产生的伤害
	bool win1, win2;
	if (who_to_start) {//红方发起进攻
		hurt1 = red_warrior->start_war();//发起战争，hurt1是造成的伤害
		//输出发起战争的信息
		red_warrior->print_name();
		std::cout << "attacked ";
		blue_warrior->print_name();
		std::cout << "in city " << ID << " with " << red_warrior->get_HP() << " elements and force " << red_warrior->get_power() << std::endl;
		//
		win1 = blue_warrior->get_hurt(hurt1);//蓝方受伤，并判断是否死亡
		if (win1) {
			std::cout << "[PROCESS]红方胜利" << std::endl;
			//输出死亡信息
			blue_warrior->print_name();
			std::cout<< "was killed in city " << ID << std::endl;
			//
			red_warrior->is_winner = true;//标记红方胜利，蓝方死亡
			blue_warrior->is_dead = true;
		}
		else {
			//输出反击信息
			blue_warrior->print_name();
			std::cout << "fought back against ";
			red_warrior->print_name();
			std::cout << "In city " << ID << std::endl;
			//
			hurt2 = blue_warrior->fight_back();//蓝方发起反击
			win2 = red_warrior->get_hurt(hurt2);//红方受伤，并判断是否死亡
			if (win2) {
				std::cout << "[PROCESS]Blue方胜利" << std::endl;
				//输出死亡信息
				red_warrior->print_name();
				std::cout << "was killed in city " << ID << std::endl;
				//
				blue_warrior->is_winner = true;
				red_warrior->is_dead = true;
			}
		}
		
	}
	else {//蓝方先发起进攻
		hurt1 = blue_warrior->start_war();
		//输出发起战争的信息
		blue_warrior->print_name();
		std::cout << "attacked ";
		red_warrior->print_name();
		std::cout << "in city " << ID << " with " << blue_warrior->get_HP() << " elements and force " << blue_warrior->get_power() << std::endl;
		//
		win1 = red_warrior->get_hurt(hurt1);
		if (win1) {
			std::cout << "[PROCESS]blue方胜利" << std::endl;
			//输出死亡信息
			red_warrior->print_name();
			std::cout << "was killed in city " << ID << std::endl;
			//
			blue_warrior->is_winner = true;
			red_warrior->is_dead = true;
		}
		else {
			hurt2 = red_warrior->fight_back();
			//输出反击信息
			red_warrior->print_name();
			std::cout << "fought back against ";
			blue_warrior->print_name();
			std::cout << "In city " << ID << std::endl;
			//
			win2 = blue_warrior->get_hurt(hurt2);
			if (win2) {
				std::cout << "[PROCESS]红方胜利" << std::endl;
				//输出死亡信息
				blue_warrior->print_name();
				std::cout << "was killed in city " << ID << std::endl;
				//
				red_warrior->is_winner = true;//标记红方胜利，蓝方死亡
				blue_warrior->is_dead = true;
			}
		}
	}
	if (!win1 && !win2) {
		res = false;
		std::cout << "[PROCESS]平局" << std::endl;
	}
	return res;

}

void city::judge_yell() {
	//对dragon欢呼的判定
	if (red_warrior->get_kind() == "dragon" && !red_warrior->is_dead) {
		dragon* d = dynamic_cast<dragon*> (red_warrior);
		if (red_warrior->is_winner) {
			d->yell(1);
		}
		else {
			d->yell(0);
		}
	}
	if (blue_warrior->get_kind() == "dragon" && !blue_warrior->is_dead) {
		dragon* d2 = dynamic_cast<dragon*> (blue_warrior);
		if (blue_warrior->is_winner) {
			d2->yell(1);
		}
		else {
			d2->yell(0);
		}
	}
}

void city::judge_transfer() {
	//对lion转移生命值
	if (red_warrior->get_kind() == "lion" && red_warrior->is_dead ) {
		lion* l = dynamic_cast<lion*>(red_warrior);
		blue_warrior->add_HP(l->life_to_transfer);
		return;
	}
	else if (blue_warrior->get_kind() == "lion"  && blue_warrior->is_dead) {
		lion* l2 = dynamic_cast<lion*>(blue_warrior);
		red_warrior->add_HP(l2->life_to_transfer);
	}
	return;
}

void city::judge_pick() {
	//对wolf判断是否捡起武器
	if (red_warrior->get_kind() == "wolf" && red_warrior->is_winner) {
		wolf* w = dynamic_cast<wolf*>(red_warrior);
		w->pick_weapon(blue_warrior->lost_weapon());
		return;
	}
	if (blue_warrior->get_kind() == "wolf" && blue_warrior->is_winner) {
		wolf* w2 = dynamic_cast<wolf*>(blue_warrior);
		w2->pick_weapon(red_warrior->lost_weapon());
		return;
	}
	return;
}

void city::judge_loyality() {
	if (red_warrior->get_kind() == "lion") {
		lion* l = dynamic_cast<lion*>(red_warrior);
		l->decrease_loyality();
	}
	if (blue_warrior->get_kind() == "lion") {
		lion* l2 = dynamic_cast<lion*>(blue_warrior);
		l2->decrease_loyality();
	}
	return;
}

void city::to_flag() {
	if (red_win ) {
		if (red_warrior->is_winner) {
			is_flag = true;
			flag = "RED";
			std::cout<<"RED flag raised in city "<<ID<<std::endl;
		}
		else {
			red_win = false;
		}
	}
	else if (blue_win) {
		if(blue_warrior->is_winner){
			is_flag = true;
			flag = "BLUE";
			std::cout << "BLUE flag raised in city " << ID << std::endl;
		}
		else {
			blue_win = false;
		}
	}
}

void city::to_start_war() {
	if (red_warrior == nullptr || blue_warrior == nullptr) {
		return;
	}
	if (have_bomb) {
		bool pred = predict_bomb();
		if (pred) {
			use_bomb();
			return;
		}
	}
	bool res = this->war();
	if (res) {
		judge_yell();
		judge_transfer();
		judge_pick();
		to_flag();
	}
	else {
		judge_loyality();
		return;
	}
}


int city::took_HP() {
	int res = HP;
	HP = 0;
	return res;
}

cities::cities() {
	for (int i = 1; i <= N; i++) {
		city c(i);
		city_list.push_back(&c);
	}
}

void cities::cities_create_hp() {
	for (int i = 1; i < city_list.size(); i++) {
		city_list[i]->create_HP();
	}
}

void cities::warrior_enter_city(HeadQuarter* red, HeadQuarter* blue) {
	std::vector<Warrior*> red_list = red->get_list_of_warriors();
	std::vector<Warrior*> blue_list = blue->get_list_of_warriors();
	for (int i = 0; i < red_list.size(); i++) {
		Warrior* w = red_list[i];
		if(!w->arrive_destination)
		city_list[w->In_city]->enter_city(w);//“进入城市”
	}
	for (int i = 0; i < blue_list.size(); i++) {
		Warrior* w2 = blue_list[i];
		if(!w2->arrive_destination)
		city_list[w2->In_city]->enter_city(w2);
	}
	return;
}

void cities::use_arrow() {
	for (int i = 1; i < city_list.size(); i++) {
		city *c = city_list[i];
		if (city_list[i]->have_arrow) {//找到有arrow的城市，再根据下一个城市是否有敌人，判断是否使用
			if (c->red_warrior->get_weapon() == "arrow") {
				if (i < city_list.size() - 2) {
					city* c1 = city_list[i + 1];
					if (c1->blue_warrior) {
						c->red_warrior->use_arrow();
						c1->blue_warrior->get_hurt(R);
						if (c1->blue_warrior->is_dead) {//如果射杀，输出信息
							c->red_warrior->print_name();
							std::cout << "shot and killed ";
							c1->blue_warrior->print_name();
							
							c1->blue_warrior = nullptr;
						}
						else {//输出相应信息
							c->red_warrior->print_name();
							std::cout<< "shot ";
							
						}
						std::cout << std::endl;
					}//c1->blue_warrior
				}//i<s
			}//red_arrow
			if (c->blue_warrior->get_weapon() == "arrow") {//同理
				if (i > 1) {
					city* c2 = city_list[i - 1];
					if (c2->red_warrior) {
						c->blue_warrior->use_arrow();
						c2->red_warrior->get_hurt(R);
						if (c2->red_warrior->is_dead) {
							c->blue_warrior->print_name();
							std::cout << "shot and killed ";
							c2->red_warrior->print_name();
							
							c2->red_warrior = nullptr;
						}//is_dead
						else {
							c->blue_warrior->print_name();
							std::cout << "shot";
						}
						std::cout << std::endl;
					}//c2.red_warrior
				}//i>
			}//blue_arrow
		}//have_arrow
	}
}

void cities::OneWarrior_took_hp(HeadQuarter* red, HeadQuarter* blue) {
	for (int i = 1; i < city_list.size(); i++) {
		city *c = city_list[i];
		if (c->red_warrior && c->blue_warrior) {
			continue;
		}
		if (!c->red_warrior && !c->blue_warrior) {
			continue;
		}
		int gain_hp;
		if (c->red_warrior && !c->blue_warrior) {
			 gain_hp = c->took_HP();
			c->red_warrior->print_name();
			std::cout<<"earned "<<gain_hp<<" elements for his headquarter"<<std::endl;
			red->add_HP(gain_hp);
		}
		if (!c->red_warrior && c->blue_warrior) {
			gain_hp = c->took_HP();
			c->blue_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			blue->add_HP(gain_hp);
		}
		 
	}
	return;
}

void cities::AfterWar_took_hp(HeadQuarter* red, HeadQuarter* blue) {
	for (int i = 1; i < city_list.size(); i++) {
		city* c = city_list[i];
		int gain_hp;
		if (c->red_warrior->is_winner) {
			gain_hp = c->took_HP();
			c->red_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			red->add_HP(gain_hp);
		}
		else if (c->blue_warrior->is_winner) {
			gain_hp = c->took_HP();
			c->blue_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			blue->add_HP(gain_hp);
		}
		else {
			continue;
		}
	}
}