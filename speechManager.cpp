#include"speechManager.h"

speechManager::speechManager()
{
	this->initspeech();

	this->createspeech();

	this->loadspeech();
	
	//cout << "记录存取成功" << endl;
}

void speechManager::showMenu()
{
	cout << "*************************************" << endl;
	cout << "**********欢迎参加演讲比赛***********" << endl;
	cout << "***********1、开始比赛***************" << endl;
	cout << "***********2、查看往届比赛记录*******" << endl;
	cout << "***********3、清空比赛记录***********" << endl;
	cout << "***********0、退出比赛程序***********" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

void speechManager::initspeech()
{
	this->index = 1;
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m.clear();
	this->m_Record.clear();
}

void speechManager::stratspeech()
{
	//初始化数据，创建比赛选手
	initspeech();
	createspeech();
	//一轮比赛
	//1、抽签
	drawspeech();
	//2、比赛
	contestspeech();
	//3、显示成绩
	showspeech();

	this->index++;
	//二轮比赛
	//1、抽签
	drawspeech();
	//2、比赛
	contestspeech();
	//3、显示成绩
	showspeech();
	//4、保存结果记录
	savespeech();

	//重置比赛
	this->initspeech();

	this->createspeech();

	this->loadspeech();
}

void speechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

void speechManager::createspeech()
{
	string namespeed = "ABCDEFGHIJKL";
	for (int i = 0; i < namespeed.size(); i++)
	{
		//创建每个选手的名字
		string name = "选手";
		name += namespeed[i];

		//创建选手,且初始化信息
		speech sp;
		sp.Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.score[i] = 0;
		}

		//创建选手编号10001~10012
		this->v1.push_back(i + 10001);

		this->m.insert(make_pair(i+10001,sp));
	}
}

void speechManager::drawspeech()
{
	cout << "第" << this->index << "轮比赛，选手抽签结果如下。" << endl;

	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	//system("pause");
	cout << endl;

}

void speechManager::contestspeech()
{
	cout << "第" << this->index << "轮比赛，比赛结果如下。" << endl;
	
	multimap<double, int, greater<double>> groupscore;

	//比赛人数
	int num = 0;

	//比赛人员临时容器
	vector<int>v_src;

	if (this->index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}

	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		//记录本轮参加的人数有多少
		num++;

		//评委打分，求平均分
		deque<double>d;
		for (int i = 0; i < 10 ; i++)
		{
			double socre = (rand() % 401 + 600) / 10.f;

			d.push_back(socre);
		}

		sort(d.begin(), d.end());
		
		//高低分都去除
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();

		//访问map容器中的选手成绩
		this->m[*it].score[this->index - 1] = avg;

		//存放成绩和选手信息
		groupscore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组的比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
			{
				cout << "编号：" << it->second << " " << "成绩：" << m[it->second].score[this->index - 1] << endl;
			}

			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin();
				it != groupscore.end() && count <3 ; it++,count++)
			{
				if (this->index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					v3.push_back(it->second);
				}
			}

			groupscore.clear();
			cout << endl;
		}
	}
	cout << "-----------第" << this->index << "轮比赛完毕-----------" << endl;
}

void speechManager::showspeech()
{
	cout << "-----------第" << this->index << "轮晋级的选手信息如下：------------" << endl;
	vector<int>v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	//sort(v.begin(), v.end());

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << m[*it].Name << " 得分：" << m[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	cout << "记录存储成功" << endl;

	system("pause");
	system("cls");

	//this->showMenu();
}

void speechManager::savespeech()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << "," << m[*it].Name << "," << m[*it].score[1] << ",";
	}
	ofs << endl;

	//cout << "记录存储成功" << endl;

	ofs.close();

	this->fileIsEmpty = false;
}

void speechManager::loadspeech()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;

		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;

	while (ifs>>data)
	{
		vector<string>v;
		//cout << data << " ";
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",",start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
		v.clear();
	}
	/*cout << endl << endl;*/
	ifs.close();
	
}

void speechManager::showrecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "-------------------第" << i + 1 << "届-------------------" << endl;
			cout << "冠军编号：" << this->m_Record[i][0] <<" 姓名："<<this->m_Record[i][1] << " 得分：" << this->m_Record[i][2]<<endl;
			cout << "亚军编号：" << this->m_Record[i][3] <<" 姓名："<<this->m_Record[i][4] << " 得分：" << this->m_Record[i][5]<<endl;
			cout << "季军编号：" << this->m_Record[i][6] <<" 姓名："<<this->m_Record[i][7] << " 得分：" << this->m_Record[i][8]<<endl;
		}
		cout << endl;
	}
	
	system("pause");
	system("cls");
}

void speechManager::clear()
{
	ofstream ofs("speech.csv", ios::trunc);
	ofs.close();

	this->initspeech();

	this->createspeech();

	this->loadspeech();

	cout << "清空完毕" << endl;

	system("pause");
	system("cls");
}

speechManager::~speechManager()
{

}