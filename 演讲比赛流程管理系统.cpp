#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
#include<ctime>

int main()
{
	srand((unsigned int)time(NULL));

	speechManager sp;

	int choice;

	while (true)
	{
		sp.showMenu();

		cout << "请输入你的选择" << endl;
		
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sp.stratspeech();
			break;
		case 2:// 查看记录
			sp.showrecord();
			break;
		case 3://清空记录
			sp.clear();
			break;
		case 0://退出系统
			sp.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("cls");

	return 0;
}


