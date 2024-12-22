#include"OneRound.h"
//t代表整点
int Round(HeadQuarter *red,HeadQuarter *blue,cities *c,int t) {
	int min = 0;
	//0分，创造武士*******************不完善******************
	//red->create_warrior(t);
	//blue->create_warrior(t);
	//5分，狮子逃跑
	min = 5;
	red->lion_run(t,min);
	blue->lion_run(t,min);
	//10分，武士前进
	min = 10;
	red->march(t,min);
	blue->march(t,min);
	if (red->TakeDown >= 2) {
		return -1;
	}
	if (blue->TakeDown >= 2) {
		return 1;
	}
	c->warrior_enter_city(red, blue);//对城市而言，使其对武士指针，指向进入的武士
	//20分，生成HP
	c->cities_create_hp();
	//30分，只有一个武士的城市失去生命元
	min = 30;
	c->OneWarrior_took_hp(red, blue,t,min);
	//35分，放箭
	min = 35;
	c->use_arrow();//从城市群对放箭分析.对城市删除了武士指针（指向nullptr）
	//red->clear_dead();//清理死亡武士
	//blue->clear_dead();
	//38分，评估炸弹的使用
	min = 38;
	c->use_bomb(t,min);
	//40分，战争
	min = 40;
	c->all_war(t, min);//包含进攻/反击/战死/欢呼/升旗
	red->clear_dead();//清理死亡武士，并对胜者奖励
	blue->clear_dead();
	red->reward();
	blue->reward();
	c->AfterWar_took_hp(red, blue,t,min);//指挥部收取生命元
	c->warrior_leave_city();//武士离开城市
	//50分，司令部报告生命元数量
	min = 50;
	std::cout << t << ":" << min << " ";
	red->report_hp();
	std::cout << t << ":" << min << " ";
	blue->report_hp();
	//55分，武士报告武器情况
	min = 55;
	red->report_warrior(t, min);
	blue->report_warrior(t, min);
	return 0;
}