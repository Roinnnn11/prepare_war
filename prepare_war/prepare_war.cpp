// prepare_war.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<vector>
#include"headquarter.h"
#include"weapon.h"
#include"warrior.h"
#include"city.h"
int dragon::HP = 0;
int ninja::HP = 0;
int iceman::HP = 0;
int lion::HP = 0;
int wolf::HP = 0;
int main() {
    std::string r = "RED";
    std::string b = "BLUE";
    int cnt;
    std::cin >> cnt;
    int M;
    for (int i = 0; i < cnt; i++) {
        std::cin >> M;
        HeadQuarter R(M, r);
        HeadQuarter B(M, b);
        
        std::cin >> dragon::HP>>ninja::HP>>iceman::HP>>lion::HP>>wolf::HP;

        R.set_order_for_HeadQuarter(0);//0\1是固定模式，也可以自己输入武士顺序；
        B.set_order_for_HeadQuarter(1);
        int t = 0;
        bool res1, res2;
        res1 = false, res2 = false;
        while (res1 == false || res2 == false) {
            if (res1 == false) {
                R.create_warrior(t);
            }
            if (res2 == false) {
                B.create_warrior(t);
            }
            res1 = R.get_is_stop_creating();
            res2 = B.get_is_stop_creating();
            t++;
        }
        city A(1);
        A.red_warrior = R.get_warrior();
        A.blue_warrior = B.get_warrior();
        std::cout << "种类" << A.blue_warrior->get_kind() << std::endl;
        std::cout << "种类" << A.red_warrior->get_kind() << std::endl;
        A.to_start_war();

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
