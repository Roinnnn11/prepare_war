#include"city.h"
#include"warrior.h"
void city::create_HP() {
	HP += 10;
};

city::city(int i) {
	ID = i;
	red_warrior = nullptr;
	blue_warrior = nullptr;
	red_have_bomb = false;
	blue_have_bomb = false;
	red_have_arrow = false;
	blue_have_arrow = false;
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
		wolf* wf = dynamic_cast<wolf*>(w);
		if (wf->have_bomb) {
			if (wf->belong_headquater == "RED") {
				red_have_bomb = true;
			}
			else {
				blue_have_bomb = true;
			}
		}//have_bomb
		if (wf->have_arrow) {
			if (wf->belong_headquater == "RED") {
				red_have_arrow = true;
			}
			else {
				blue_have_arrow = true;
			}
		}
		return;
	}//wolf
	if (w->get_kind() == "ninja") {
		ninja* n = dynamic_cast<ninja*>(w);
		std::string kind1 = n->get_weapon();
		std::string kind2 = n->get_weapon2();
		if (kind1 == "bomb" || kind2 == "bomb") {
			if (n->belong_headquater == "RED") {
				red_have_bomb = true;
			}
			else {
				blue_have_bomb = true;
			}
		}//have_bomb
		if (kind1 == "arrow" || kind2 == "arrow") {
			if (n->belong_headquater == "RED") {
				red_have_arrow = true;
			}
			else {
				blue_have_arrow = true;
			}
		}
	}
	std::string kind = w->get_weapon();
	if (kind == "bomb") {
		if (w->belong_headquater == "RED") {
			red_have_bomb = true;
		}
		else {
			blue_have_bomb = true;
		}
	}//HAVE_BOMB
	if (kind == "arrow") {
		if(w->belong_headquater=="RED"){
			red_have_arrow = true;
		}
		else {
			blue_have_arrow = true;
		}
	}
}

int city::predict_bomb() {//*************需要完善************
	//0:不用，-1：红方用，1：蓝方用
	int use_bomb = 0;
	if (!red_have_bomb&&!blue_have_bomb) {
		return 0;
	}
	if (!red_warrior || !blue_warrior) {
		return 0;
	}
	double hurt1,hurt2;
	if (red_have_bomb && who_to_start) {//红方拥有炸弹&&发起进攻
		hurt1 = red_warrior->start_war();
		//**********加入特判
		if (red_warrior->get_kind() == "ninja") {
			ninja *n = dynamic_cast<ninja*>(red_warrior);
			hurt1 = n->start_war();
		}
		else if (red_warrior->get_kind() == "wolf") {
			wolf* w = dynamic_cast<wolf*>(red_warrior);
			hurt1 = w->start_war();
		}
		//********特判结束

		if (blue_warrior->get_HP() > hurt1) {//蓝方不死，发起反击
			hurt2 = blue_warrior->fight_back();
		//特判
			if (blue_warrior->get_kind() == "ninja") {
				ninja *n2 = dynamic_cast<ninja*>(blue_warrior);
				hurt2 = n2->fight_back();
			}
			else if(blue_warrior->get_kind()=="wolf"){
				wolf* w2 = dynamic_cast<wolf*>(blue_warrior);
				hurt2 = w2->fight_back();
			}
			//*******特判结束
			if (red_warrior->get_HP() <= hurt2) {//红方受反击而死
				use_bomb = -1;
			}
		}
	}//红方拥有炸弹&&发起进攻
	if (red_have_bomb && !who_to_start) {//红方拥有炸弹&&反击
		hurt1 = blue_warrior->start_war();
		//特判
		if (blue_warrior->get_kind() == "ninja") {
			ninja* n3 = dynamic_cast<ninja*>(blue_warrior);
			hurt1 = n3->start_war();
		}
		else if (blue_warrior->get_kind() == "wolf") {
			wolf* w3 = dynamic_cast<wolf*>(blue_warrior);
			hurt1 = w3->start_war();
		}
		//*******特判结束
		if (red_warrior->get_HP() <= hurt1) {
			use_bomb = -1;
		}
	}
	//红蓝交换
	if (blue_have_bomb && !who_to_start) {//blue方拥有炸弹&&发起进攻
		hurt1 = blue_warrior->start_war();
		//特判
		if (blue_warrior->get_kind() == "ninja") {
			ninja* n4 = dynamic_cast<ninja*>(blue_warrior);
			hurt1 = n4->start_war();
		}
		else if (blue_warrior->get_kind() == "wolf") {
			wolf* w4 = dynamic_cast<wolf*>(blue_warrior);
			hurt1 = w4->start_war();
		}
		//*******特判结束
		if (red_warrior->get_HP() >hurt1) {//red反击
			hurt2 = red_warrior->fight_back();
			//**********加入特判
			if (red_warrior->get_kind() == "ninja") {
				ninja* n5 = dynamic_cast<ninja*>(red_warrior);
				hurt2 = n5->fight_back();
			}
			else if (red_warrior->get_kind() == "wolf") {
				wolf* w5 = dynamic_cast<wolf*>(red_warrior);
				hurt2 = w5->fight_back();
			}
			//********特判结束
			if (blue_warrior->get_HP() <= hurt2) {//blue方受反击而死
				use_bomb = 1;//蓝方使用炸弹
			}
		}
	}
	if (blue_have_bomb && who_to_start) {//blue方拥有炸弹&&反击
		hurt1 = red_warrior->start_war();
		//**********加入特判
		if (red_warrior->get_kind() == "ninja") {
			ninja* n6 = dynamic_cast<ninja*>(red_warrior);
			hurt1 = n6->start_war();
		}
		else if (red_warrior->get_kind() == "wolf") {
			wolf* w6 = dynamic_cast<wolf*>(red_warrior);
			hurt1 = w6->start_war();
		}
		//********特判结束
		if (blue_warrior->get_HP() <= hurt1) {
			use_bomb = 1;
		}
	}
	return use_bomb;
}

void city::use_bomb(int t,int min,int choice) {
	std::cout << t << ":" << min << " ";
	if (choice==-1) {
		red_warrior->print_name();
		std::cout <<  "used a bomb and killed ";
		blue_warrior->print_name();	
	}
	if (choice==1) {
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

bool city::war(int t,int min) {
	bool res = true;
	double hurt1, hurt2;//两者产生的伤害
	bool win1, win2;
	if (who_to_start) {//红方发起进攻
		hurt1 = red_warrior->start_war();//发起战争，hurt1是造成的伤害
		//对ninja\wolf特判，可能改变hurt的值
		if(red_warrior->get_kind()=="ninja"){
			ninja* n = dynamic_cast<ninja*>(red_warrior);
			hurt1 = n->start_war();
		}
		else if (red_warrior->get_kind() == "wolf") {
			wolf *w = dynamic_cast<wolf*>(red_warrior);
			hurt1 = w->start_war();
		}

		//输出发起战争的信息
		std::cout << t << ":" << min << " ";
		red_warrior->print_name();
		std::cout << "attacked ";
		blue_warrior->print_name();
		std::cout << "in city " << ID << " with " << red_warrior->get_HP() << " elements and force " << red_warrior->get_power() << std::endl;
		//
		win1 = blue_warrior->get_hurt(hurt1);//蓝方受伤，并判断是否死亡
		if (win1) {
			std::cout << "[PROCESS]红方胜利" << std::endl;
			//输出死亡信息
			std::cout << t << ":" << min << " ";
			blue_warrior->print_name();
			std::cout<< "was killed in city " << ID << std::endl;
			//
			red_warrior->is_winner = true;//标记红方胜利，蓝方死亡
			blue_warrior->is_dead = true;
		}
		else {
			//输出反击信息
			std::cout << t << ":" << min << " ";
			blue_warrior->print_name();
			std::cout << "fought back against ";
			red_warrior->print_name();
			std::cout << "In city " << ID << std::endl;
			//
			hurt2 = blue_warrior->fight_back();//蓝方发起反击
			//特判ninja&wolf
			if (blue_warrior->get_kind() == "ninja")  {
				ninja *n2 = dynamic_cast<ninja*>(blue_warrior);
				hurt2 = n2->fight_back();
			}
			else if (blue_warrior->get_kind() == "wolf") {
				wolf* w2 = dynamic_cast<wolf*>(blue_warrior);
				hurt2 = w2->fight_back();
			}

			win2 = red_warrior->get_hurt(hurt2);//红方受伤，并判断是否死亡
			if (win2) {
				std::cout << "[PROCESS]Blue方胜利" << std::endl;
				//输出死亡信息
				std::cout << t << ":" << min << " ";
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
		std::cout << t << ":" << min << " ";
		blue_warrior->print_name();
		std::cout << "attacked ";
		red_warrior->print_name();
		std::cout << "in city " << ID << " with " << blue_warrior->get_HP() << " elements and force " << blue_warrior->get_power() << std::endl;
		//
		win1 = red_warrior->get_hurt(hurt1);
		if (win1) {
			std::cout << "[PROCESS]blue方胜利" << std::endl;
			//输出死亡信息
			std::cout << t << ":" << min << " ";
			red_warrior->print_name();
			std::cout << "was killed in city " << ID << std::endl;
			//
			blue_warrior->is_winner = true;
			red_warrior->is_dead = true;
		}
		else {
			hurt2 = red_warrior->fight_back();
			//输出反击信息
			std::cout << t << ":" << min << " ";
			red_warrior->print_name();
			std::cout << "fought back against ";
			blue_warrior->print_name();
			std::cout << "In city " << ID << std::endl;
			//
			win2 = blue_warrior->get_hurt(hurt2);
			if (win2) {
				std::cout << "[PROCESS]红方胜利" << std::endl;
				//输出死亡信息
				std::cout << t << ":" << min << " ";
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

void city::judge_yell(int t,int min) {
	//对dragon欢呼的判定
	if (red_warrior->get_kind() == "dragon" && !red_warrior->is_dead) {
		dragon* d = dynamic_cast<dragon*> (red_warrior);
		if (red_warrior->is_winner) {
			d->yell(1,t,min);
		}
		else {
			d->yell(0,t,min);
		}
	}
	if (blue_warrior->get_kind() == "dragon" && !blue_warrior->is_dead) {
		dragon* d2 = dynamic_cast<dragon*> (blue_warrior);
		if (blue_warrior->is_winner) {
			d2->yell(1,t,min);
		}
		else {
			d2->yell(0,t,min);
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

void city::to_flag(int t,int min) {
	if (red_win ) {
		if (red_warrior->is_winner) {
			is_flag = true;
			flag = "RED";
			std::cout << t << ":" << min << " ";
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
			std::cout << t << ":" << min << " ";
			std::cout << "BLUE flag raised in city " << ID << std::endl;
		}
		else {
			blue_win = false;
		}
	}
}

void city::to_start_war(int t,int min) {
	if (red_warrior == nullptr || blue_warrior == nullptr) {
		return;
	}
	have_war = true;
	bool res = this->war(t,min);
	if (res) {
		judge_yell(t,min);
		judge_transfer();
		judge_pick();
		to_flag(t,min);
	}
	else {
		judge_loyality();
		return;
	}
}


void city::warrior_leave() {
	red_warrior = nullptr;
	blue_warrior = nullptr;
	red_have_bomb = false;
	blue_have_bomb = false;
	red_have_arrow = false;
	blue_have_arrow = false;
	who_to_start = false;
	have_war = false;
}

int city::took_HP() {
	int res = HP;
	HP = 0;
	return res;
}

cities::cities(int n) {
	N = n;
	for (int i = 0; i <= n+1; i++) {
		city* c= new city(i);
		city_list.push_back(c);
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
		city* c = city_list[i];
		if(c->red_warrior)
		if (c->red_have_arrow) {//如果存在红方武士
			
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
						std::cout << "shot ";
						
					}
					std::cout << std::endl;
				}//c1->blue_warrior
			}//i<s
		}//red_arrow
		//red_warrior.exist
		if(c->blue_warrior)
		if (c->blue_have_arrow) {
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
		}//for
	
}


void cities::use_bomb(int t, int min) {
	for (int i = 1; i < city_list.size(); i++) {
		city* c = city_list[i];
		c->who_start();//判断谁先进攻
		int choice = c->predict_bomb();
			if (choice!=0) {
				c->use_bomb(t, min,choice);
			}
		
	}
}

void cities::OneWarrior_took_hp(HeadQuarter* red, HeadQuarter* blue,int t,int min) {
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
			 std::cout << t << ":" << min << " ";
			c->red_warrior->print_name();
			std::cout<<"earned "<<gain_hp<<" elements for his headquarter"<<std::endl;
			red->add_HP(gain_hp);
		}
		if (!c->red_warrior && c->blue_warrior) {
			gain_hp = c->took_HP();
			std::cout << t << ":" << min << " ";
			c->blue_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			blue->add_HP(gain_hp);
		}
		 
	}
	return;
}

void cities::all_war(int t, int min) {
	for (int i = 1; i < city_list.size(); i++) {
		city *c = city_list[i];
		c->to_start_war(t,min);
	}
}

void cities::AfterWar_took_hp(HeadQuarter* red, HeadQuarter* blue,int t,int min) {
	for (int i = 1; i < city_list.size(); i++) {
		city* c = city_list[i];
		if (!c->have_war) {//没有发生战争
			continue;
		}
		int gain_hp;
		if (c->red_warrior->is_winner) {
			gain_hp = c->took_HP();
			std::cout << t << ":" << min << " ";
			c->red_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			red->add_HP(gain_hp);
			c->red_warrior->is_winner = false;//重置武士信息
		}
		else if (c->blue_warrior->is_winner) {
			gain_hp = c->took_HP();
			std::cout << t << ":" << min << " ";
			c->blue_warrior->print_name();
			std::cout << "earned " << gain_hp << " elements for his headquarter" << std::endl;
			blue->add_HP(gain_hp);
			c->blue_warrior->is_winner = false;//重置武士信息
		}
		else {
			continue;
		}
	}
}

void cities::warrior_leave_city() {
	for (int i = 1; i < city_list.size(); i++) {
		city_list[i]->warrior_leave();
	}
}