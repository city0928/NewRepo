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

		cout << "���������ѡ��" << endl;
		
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			sp.stratspeech();
			break;
		case 2:// �鿴��¼
			sp.showrecord();
			break;
		case 3://��ռ�¼
			sp.clear();
			break;
		case 0://�˳�ϵͳ
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


