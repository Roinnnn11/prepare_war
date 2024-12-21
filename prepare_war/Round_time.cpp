#include "headquarter.h"
#include"warrior.h"
#include"weapon.h"
#include"city.h"
//t代表整点
void Round(HeadQuarter *red,HeadQuarter *blue,cities *c,int t) {
	int min = 0;
	//0分，创造武士*******************不完善******************
	red->create_warrior(t);
	blue->create_warrior(t);
	//5分，狮子逃跑
	min = 5;
	red->lion_run(t,min);
	blue->lion_run(t,min);
	//10分，武士前进
	min = 10;
	red->march(t,min);
	blue->march(t,min);
	c->warrior_enter_city(red, blue);//对城市而言，使其对武士指针，指向进入的武士
	//20分，生成HP
	c->cities_create_hp();
	//30分，只有一个武士的城市失去生命元
	min = 30;
	c->OneWarrior_took_hp(red, blue);
	//35分，放箭
	min = 35;
	c->use_arrow();//从城市群对放箭分析.对城市删除了武士指针（指向nullptr）
	//red->clear_dead();//清理死亡武士
	//blue->clear_dead();
	//38分，评估炸弹的使用
	for (int i = 1; i < c->city_list.size(); i++) {
		if (c->city_list[i]->predict_bomb()) {//预测炸弹使用************不完善********************
			c->city_list[i]->use_bomb(t,min);
		}
	}
	//40分，战争
	min = 40;

}