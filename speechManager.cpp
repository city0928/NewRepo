#include"speechManager.h"

speechManager::speechManager()
{
	this->initspeech();

	this->createspeech();

	this->loadspeech();
	
	//cout << "��¼��ȡ�ɹ�" << endl;
}

void speechManager::showMenu()
{
	cout << "*************************************" << endl;
	cout << "**********��ӭ�μ��ݽ�����***********" << endl;
	cout << "***********1����ʼ����***************" << endl;
	cout << "***********2���鿴���������¼*******" << endl;
	cout << "***********3����ձ�����¼***********" << endl;
	cout << "***********0���˳���������***********" << endl;
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
	//��ʼ�����ݣ���������ѡ��
	initspeech();
	createspeech();
	//һ�ֱ���
	//1����ǩ
	drawspeech();
	//2������
	contestspeech();
	//3����ʾ�ɼ�
	showspeech();

	this->index++;
	//���ֱ���
	//1����ǩ
	drawspeech();
	//2������
	contestspeech();
	//3����ʾ�ɼ�
	showspeech();
	//4����������¼
	savespeech();

	//���ñ���
	this->initspeech();

	this->createspeech();

	this->loadspeech();
}

void speechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

void speechManager::createspeech()
{
	string namespeed = "ABCDEFGHIJKL";
	for (int i = 0; i < namespeed.size(); i++)
	{
		//����ÿ��ѡ�ֵ�����
		string name = "ѡ��";
		name += namespeed[i];

		//����ѡ��,�ҳ�ʼ����Ϣ
		speech sp;
		sp.Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.score[i] = 0;
		}

		//����ѡ�ֱ��10001~10012
		this->v1.push_back(i + 10001);

		this->m.insert(make_pair(i+10001,sp));
	}
}

void speechManager::drawspeech()
{
	cout << "��" << this->index << "�ֱ�����ѡ�ֳ�ǩ������¡�" << endl;

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
	cout << "��" << this->index << "�ֱ���������������¡�" << endl;
	
	multimap<double, int, greater<double>> groupscore;

	//��������
	int num = 0;

	//������Ա��ʱ����
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
		//��¼���ֲμӵ������ж���
		num++;

		//��ί��֣���ƽ����
		deque<double>d;
		for (int i = 0; i < 10 ; i++)
		{
			double socre = (rand() % 401 + 600) / 10.f;

			d.push_back(socre);
		}

		sort(d.begin(), d.end());
		
		//�ߵͷֶ�ȥ��
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();

		//����map�����е�ѡ�ֳɼ�
		this->m[*it].score[this->index - 1] = avg;

		//��ųɼ���ѡ����Ϣ
		groupscore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "��ı�������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
			{
				cout << "��ţ�" << it->second << " " << "�ɼ���" << m[it->second].score[this->index - 1] << endl;
			}

			//ȡǰ����
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
	cout << "-----------��" << this->index << "�ֱ������-----------" << endl;
}

void speechManager::showspeech()
{
	cout << "-----------��" << this->index << "�ֽ�����ѡ����Ϣ���£�------------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << m[*it].Name << " �÷֣�" << m[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	cout << "��¼�洢�ɹ�" << endl;

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

	//cout << "��¼�洢�ɹ�" << endl;

	ofs.close();

	this->fileIsEmpty = false;
}

void speechManager::loadspeech()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;

		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
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
		cout << "�ļ�������" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "-------------------��" << i + 1 << "��-------------------" << endl;
			cout << "�ھ���ţ�" << this->m_Record[i][0] <<" ������"<<this->m_Record[i][1] << " �÷֣�" << this->m_Record[i][2]<<endl;
			cout << "�Ǿ���ţ�" << this->m_Record[i][3] <<" ������"<<this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5]<<endl;
			cout << "������ţ�" << this->m_Record[i][6] <<" ������"<<this->m_Record[i][7] << " �÷֣�" << this->m_Record[i][8]<<endl;
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

	cout << "������" << endl;

	system("pause");
	system("cls");
}

speechManager::~speechManager()
{

}