#include"city.h"
#include"warrior.h"
//void city::create_HP() {
//	HP += 10;
//};
//  
bool city::war() {
	bool res = true;
	double hurt1, hurt2;//两者产生的伤害
	bool win1, win2;
	if ((is_flag&&flag == "RED")||(!is_flag&&ID%2!=0)) {//红方发起进攻
		hurt1 = red_warrior->start_war();//发起战争，hurt1是造成的伤害
		red_warrior->use_weapon();//武器损耗
		win1 = blue_warrior->get_hurt(hurt1);//蓝方受伤，并判断是否死亡
		if (win1) {
			std::cout << "[PROCESS]红方胜利" << std::endl;
			red_warrior->is_winner = true;//标记红方胜利，蓝方死亡
			blue_warrior->is_dead = true;
		}
		else {
			hurt2 = blue_warrior->fight_back();//蓝方发起反击
			win2 = red_warrior->get_hurt(hurt2);//红方受伤，并判断是否死亡
			if (win2) {
				std::cout << "[PROCESS]Blue方胜利" << std::endl;
				blue_warrior->is_winner = true;
				red_warrior->is_dead = true;
			}
		}
		
	}
	else {//蓝方先发起进攻
		hurt1 = blue_warrior->start_war();
		win1 = red_warrior->get_hurt(hurt1);
		if (win1) {
			std::cout << "[PROCESS]blue方胜利" << std::endl;
			blue_warrior->is_winner = true;
			red_warrior->is_dead = true;
		}
		else {
			hurt2 = red_warrior->fight_back();
			win2 = blue_warrior->get_hurt(hurt2);
			if (win2) {
				std::cout << "[PROCESS]红方胜利" << std::endl;
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
	////对dragon欢呼的判定
	//if (red_warrior->get_kind() == "dragon"&&!red_warrior->is_dead) {
	//	dragon* d = dynamic_cast<dragon*> (red_warrior);
	//	if (red_warrior->is_winner) {
	//		d->yell(1);
	//	}
	//	else {
	//		d->yell(0);
	//	}
	//}
	//if (blue_warrior->get_kind() == "dragon" && !blue_warrior->is_dead) {
	//	dragon* d2 = dynamic_cast<dragon*> (blue_warrior);
	//	if (blue_warrior->is_winner) {
	//		d2->yell(1);
	//	}
	//	else {
	//		d2->yell(0);
	//	}
	//}

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

void city::to_start_war() {
	if (red_warrior == nullptr || blue_warrior == nullptr) {
		return;
	}
	bool res = this->war();
	if (res) {
		judge_yell();
		judge_transfer();
		judge_pick();
	}
	else {
		judge_loyality();
		return;
	}
}
