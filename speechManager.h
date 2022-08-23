#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speech.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>

class speechManager
{
public:
	speechManager();

	void showMenu();

	void exitSystem();

	void initspeech();

	void drawspeech();

	void stratspeech();

	//��һ�ֱ�����12��
	vector<int> v1;

	//�ڶ��ֱ�����6��
	vector<int> v2;

	//�����ֱ�����3��
	vector<int> v3;

	//����ѡ�ֵı�ţ��Լ�ѡ�־������Ϣ
	map<int, speech> m;

	int index;

	void createspeech();

	void contestspeech();

	void showspeech();

	void savespeech();

	bool fileIsEmpty;

	map<int, vector<string>>m_Record;

	void loadspeech();

	void showrecord();

	void clear();

	~speechManager();
};