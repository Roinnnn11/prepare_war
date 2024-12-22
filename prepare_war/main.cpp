// prepare_war.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<vector>
#include"headquarter.h"
#include"weapon.h"
#include"warrior.h"
#include"city.h"
#include"OneRound.h"
int dragon::HP = 0;
int ninja::HP = 0;
int iceman::HP = 0;
int lion::HP = 0;
int wolf::HP = 0;
int dragon::d_power = 0;
int ninja::n_power = 0;
int iceman::i_power = 0;
int lion::l_power = 0;
int wolf::w_power = 0;
double lion::K = 0;
int main() {
    std::string r = "RED";
    std::string b = "BLUE";
    int cnt;
    std::cin >> cnt;
    int M,N,r_arrow,K,T;
    for (int i = 0; i < cnt; i++) {
        std::cin >> M>>N>>r_arrow>>lion::K>>T;
        HeadQuarter R(M, r);
        HeadQuarter B(M, b);
        cities C(N);
        C.R = r_arrow;
        R.des = N + 1, B.des = 0;
        R.base = 0,B.base = N + 1;
        std::cin >> dragon::HP>>ninja::HP>>iceman::HP>>lion::HP>>wolf::HP;
        std::cin >> dragon::d_power >> ninja::n_power >> iceman::i_power >> lion::l_power >> wolf::w_power;
        R.set_order_for_HeadQuarter(0);//0\1是固定模式，也可以自己输入武士顺序；
        B.set_order_for_HeadQuarter(1);
        int t = 0;
        int res;

        std::cout<<"Case:"<<i+1<<std::endl;
        while (t<T) {
                R.create_warrior(t);
                B.create_warrior(t);
            res = Round(&R, &B, &C, t);
            if (res == 0) {
                t++;
                continue;
            }
            if (res == 1) {
                std::cout << t << ":10 ";
                std::cout<<"red headquarter was taken"<<std::endl;
                break;
            }
            else if (res == -1) {
                std::cout << t << ":10 ";
                std::cout<<"blue headquarter was taken"<<std::endl;
                break;
            }
       
        }

        std::cout << std::endl << "**********第" << i << "轮测试结束**********" << std::endl;
         //R.~HeadQuarter();
         //B.~HeadQuarter();
    }
    
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
