#include"city.h"
#include"warrior.h"
//void city::create_HP() {
//	HP += 10;
//};
//  
void city::to_start_war() {
	if (red_warrior == nullptr || blue_warrior == nullptr) {
		return;
	}
	this->war();
}

void city::war() {
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
		std::cout << "[PROCESS]平局" << std::endl;
	}
	//对dragon欢呼的判定
	if (red_warrior->get_kind() == "dragon"&&!red_warrior->is_dead) {
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

