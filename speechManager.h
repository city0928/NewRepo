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

	//第一轮比赛，12人
	vector<int> v1;

	//第二轮比赛，6人
	vector<int> v2;

	//第三轮比赛，3人
	vector<int> v3;

	//创建选手的编号，以及选手具体的信息
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