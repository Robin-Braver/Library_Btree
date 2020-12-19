#pragma once
#include <cfloat>
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const int MaxValue = INT_MAX;

struct BookNode//������
{
	BookNode();
	int BookNum;//���
	string Name;//����
	string Author;//����
	int currentNum;//�ִ���
	int totalNum;//����
};

ostream& operator<<(ostream& out, BookNode& Book)//�������������
{
	out << "*��ţ�" << Book.BookNum << "  ";
	out << "������"<< setw(42) << Book.Name << '\t';
	out << "���ߣ�" << setw(10) << Book.Author << '\t';
	out << "�ִ�����" << setw(2) << Book.currentNum << '\t';
	out << "������" << setw(2) << Book.totalNum <<"*"<< endl;
	return out;
}

istream& operator>>(istream&in, BookNode& Book)//�������������
{
	int n;
	cout << "���Ϊ��";
	in>> Book.BookNum;
	cout << "����Ϊ��";
	in >> Book.Name;
	cout << "��������Ϊ��";
	in >> Book.Author;
	cout << "��Ӹ�������Ϊ��";
	in >>n;
	Book.currentNum = Book.currentNum + n;
	Book.totalNum = Book.totalNum + n;
	return in;
}

BookNode::BookNode()
{
	BookNum = MaxValue;
	currentNum = 0;
	totalNum = 0;
	Name = " ";
	Author = " ";
}

struct BtreeNode//����㶨��
{
	BtreeNode();
	int n;//�ؼ������
	BtreeNode* parent;//���ڵ�ָ��
	BookNode key[5];//key[4]Ϊ����ڣ�key[0]��ʹ��
	BtreeNode* ptr[5];//������ָ������,ptr[m]�ڲ������ʱʹ��
};

BtreeNode::BtreeNode()
{
	parent = NULL;
	n = 0;
	ptr[0] = NULL;
	ptr[1] = NULL;
	ptr[2] = NULL;
	ptr[3] = NULL;
	ptr[4] = NULL;
}

struct Triple//���������Ԫ��
{
	BtreeNode* r;//����ַָ��
	int i;//����йؼ������i
	int tag;//tag=0�������ɹ���Ϊ1ʧ��
};

class Btree
{
protected:
	const int m = 4;//·���������������	
public:
	BtreeNode* root;//��ָ��
	Btree();//���캯��
	Triple Search(const int&x, Btree& Btree);//����
	bool Insert(BookNode *booknode,Btree&Btree);//
	bool Remove(int& x,Btree& Btree);//ɾ���ؼ���x
	void insertkey(BtreeNode* p, int j, BookNode& booknode, BtreeNode* ap);//�����㷨��ڽڵ������ڲ�����
	void move(BtreeNode* p, BtreeNode* q, int s, int m);//�����㷨�������ƶ�����
	void compress(BtreeNode* p, int j);//ɾ���㷨�����ǰ�Ʋ���
	void LeftAdjust(BtreeNode* p, BtreeNode* q, int d, int j);//ɾ���㷨�������
	void RightAdjust(BtreeNode* p, BtreeNode* q, int d, int j);//ɾ���㷨���ҵ���
	void merge(BtreeNode* p, BtreeNode* q, BtreeNode* p1, int j);//ɾ���㷨���ϲ�
};

Btree::Btree()
{
	root = new BtreeNode;
}


Triple Btree::Search(const int& x, Btree& Btree)//�����㷨
//�ùؼ���x���������ڵ��ʽΪn��p[0],(k[1],p[1]),......,(k[n],p[n]),n<m.��������Triple���ͣ�����ʧ��ʱ�����Բ���ᣬ�����k[i]��[i+1]֮
{
	Triple result;//�����Ԫ��
	BtreeNode* p =root;//��ȡ���ڵ�
	BtreeNode* q=NULL;//p��ɨ��ָ�룬q��p���ڵ�ָ��
	int j=1;
	while (p != NULL)//�Ӹ���ʼ���
	{
		int i = 0; p->key[(p->n) + 1].BookNum= MaxValue;
		while (p->key[i + 1].BookNum < x)i++;//���������
		if (p->key[i + 1] .BookNum== x)
		{
			result.r = p; result.i = i + 1; result.tag = 0;
			return result;//���ؽ��
		}
		q = p; p = p->ptr[i];//���ڵ���x,��������
		j = i;
	}
	result.r = q; result.i = j; result.tag = 1;
	return result;//����ʧ�ܣ����ز���λ��
};

void Btree::insertkey(BtreeNode* p, int j, BookNode& booknode, BtreeNode* ap)//p�ǲ����㣬j�ǽ�������ڲ�λ�ã�K�ǲ����ֵ��ap�ǲ���ؼ���x������ָ��
{
	for (int i = p->n; i > j; i--)//jλ�ú��Ԫ�����κ���
		p->key[i + 1] = p->key[i];
	p->key[j+1] = booknode;//����ؼ���
	for (int i = p->n;i > j; i--)//jλ�ú������ָ�����κ���
		p->ptr[i + 1] = p->ptr[i];
	p->ptr[j+1] = ap;
	(p->n)  ++;//����+1
}

void Btree::move(BtreeNode* p, BtreeNode* q, int s, int m)//p�ǲ����㣬q�ǽ������½�㼴���ѵĽ�㣬s�Ƿ��ѵ���ԭ������λ�ã�m�ǽ���
{
	int i, j;
	for (i = 1, j = s + 1; j < m + 1; i++, j++)//��p��key[s+1...m]�ƶ�q��ptr[1..s-1]
	{
		q->key[i] = p->key[j];
		//p->key[j].BookNum = MaxValue;
	}
	for (i = 0, j = s; j < m + 1; i++, j++)//��ptr[s..m]�ƶ���q��ptr[0..s-1]
	{
		q->ptr[i] = p->ptr[j];
		if (p->ptr[j] != NULL)q->ptr[i]->parent = q;
		//p->ptr[j] = NULL;
	}
	p->n = s - 1;//ԭ����������
	q->n = m - s;//���ѽڵ����
}

bool Btree::Insert(BookNode*booknode, Btree& Btree)
{
	int x = booknode->BookNum;//��ȡĿ���鼮�����
	Triple loc = Search(x,Btree);//����������x�Ĳ���λ��
	BtreeNode* p = loc.r, * q;//r�ǹؼ���Ҫ�����λ��
	BtreeNode* ap = NULL, * t;//ap�ǲ���ؼ��������ָ��
	BookNode K=*booknode;
	int j = loc.i;//��k��ap���γɲ����Ԫ��
	if (K.BookNum < 0)return false;
	if (loc.tag==0)//x�Ѿ������У�������
	{
		(p->key[j].currentNum)+=booknode->currentNum;//���ִ�����
		(p->key[j].totalNum)+=booknode->totalNum;//��������
		return true;
	}
	
	while (1)
	{
		if (p->n < m - 1)//�ؼ������δ����
		{
			insertkey(p, j, K, ap);//K,ap���뵽jλ�ã���p->n��1
			return true;//������
		}
		int s = (m + 1) / 2;//׼�����ѽڵ㣬s��m/2ȡ����
		insertkey(p, j,K, ap);//�Ȳ��룬���p->n�ﵽm
		q = new BtreeNode;//�����½��q
		move(p, q, s, m);//��p��key[s+1..m]��ptr[s..m]�ƶ���q��key[1..s-1]��ptr[0..s-1],p->n��Ϊs-1,q->n��Ϊm-s
		K = p->key[s]; ap = q;//(K,ap)�γ����ϲ����Ԫ��
		if (p->parent != NULL)//���ϵ�����ԭ��p��Ϊ��
		{
			t = p->parent;//��ȡp���ڵ�t
			j = 0;
			t->key[(t->n) + 1].BookNum= MaxValue;//���ڵ���˳����������λ��
			while (t->key[j + 1] .BookNum< K.BookNum)j++;//�ҵ�����K�Ĺؼ���λ��
			q->parent = p->parent;//�½�㸸ָ�븳ֵ
			p = t;//p���������ڵ㣬���ϵ���
		}
		else
		{
			root = new BtreeNode;
			root->n = 1; root->parent = NULL;//�����¸�
			root->key[1] = K;
			root->ptr[0] = p; root->ptr[1] = ap;
			q->parent = p->parent = root;
			return true;
		}
	}
};

bool Btree::Remove(int& x,Btree& Btree)
{
	Triple loc = Search(x,Btree);//����x
	if (loc.tag == 1)return false;//��㲻���ڣ���ɾ��
	BtreeNode* p = loc.r;
	BtreeNode* q;
	BtreeNode* s;
	int j = loc.i;
	if (p->ptr[j] != NULL)//��Ҷ���
	{
		s = p->ptr[j]; q = p;
		while (s != NULL) { q = s; s = s->ptr[0]; }
		p->key[j] = q->key[1];//��Ҷ����油
		compress(q, 1);//��Ҷ���ɾ��
		p = q;//ת��ΪҶ���ɾ��
	}//compress(q,k)��ʾ�ɽ��q��k�Ժ�ָ��͹ؼ���ǰ�ƣ�ɾ��key[k]
	else compress(p, j);//Ҷ���ֱ��ɾ��
	int d = (m + 1) / 2;
	while (1)//�������ߺϲ�
	{
		if (p->n < d - 1)//С����С����
		{
			j = 0; q = p->parent;//�ҵ����ڵ�
			while (j <= q->n && q->ptr[j] != p)//�ڸ��ڵ��ҵ���λ��
				j++;
			if (j == 0)LeftAdjust(p, q, d, j);//����븸�ڵ�q��p�����ֵ����ϵ�����j��q����е�����λ��
			else RightAdjust(p, q, d, j);//���p�븸�ڵ�q��p�����ֵ����ϵ�����j��q����е���λ��
			p = q;
			if (p == root)break;
		}
		else break;//������
	}
	if (root->n == 0)//���������nΪ0
	{
		p = root->ptr[0];
		delete root;
		root = p;//ɾ����
		root->parent = NULL;//�¸�
	}
	return true;
};

void Btree::LeftAdjust(BtreeNode* p, BtreeNode* q, int d, int j)
//���p���丸�ڵ�qһ�������d�ǽ�����ٱ��ֽ�����j�Ǹ��ڵ����λ��
{
	BtreeNode* p1 = q->ptr[j + 1];//p�����ֵ�
	if (p1->n > d - 1)//���ֵܿռ仹������������
	{
		p->n++;
		p->key[p->n] = q->key[j + 1];//���ڵ���Ӧ�ؼ�������
		q->key[j + 1] = p1->key[1];//���ֵ���С�ؼ������Ƹ��ڵ�
		p->ptr[p->n] = p1->ptr[0];//���ֵ�����ָ������
		p1->ptr[0] = p1->ptr[1];//���ֵ�ʣ��ؼ�����ָ��ǰ��
		compress(p1, 1);
	}
	else merge(p, q, p1, j + 1);//p��p1�ϲ�������p���
}

void Btree::RightAdjust(BtreeNode* p, BtreeNode* q, int d, int j)
//���p���丸�ڵ�qһ�������d�ǽ�����ٱ��ֽ�����j�Ǹ��ڵ����λ��
{
	BtreeNode* p1 = q->ptr[j -1];//p�����ֵ�
	if (p1->n > d - 1)//���ֵܿռ仹������������
	{
		p->n++;
		p->key[p->n] = q->key[j - 1];//���ڵ���Ӧ�ؼ�������
		q->key[j -1] = p1->key[1];//���ֵ���С�ؼ������Ƹ��ڵ�
		p->ptr[p->n] = p1->ptr[0];//���ֵ�����ָ������
		p1->ptr[0] = p1->ptr[1];//���ֵ�ʣ��ؼ�����ָ��ǰ��
		compress(p1, 1);
	}
	else merge(p, q, p1, j -1);//p��p1�ϲ�������p���
}


void Btree::compress(BtreeNode* p,int j)
{
	for (int i = j; i < p->n; i++)//����
	{
		p->key[i] = p->key[i + 1]; p->ptr[i] = p->ptr[i + 1];
	}
	p->n--;//���Ԫ�ظ�����1
}

void Btree::merge(BtreeNode* p, BtreeNode* q, BtreeNode* p1, int j)//�ϲ�
{
	p->key[(p->n) + 1] = q->key[j];//�Ӹ��ڵ��½�һ���ؼ���
	p->ptr[(p->n) + 1] = p1->ptr[0];//�����ֵܽ������һ��ָ��
	for (int i = 1; i <= p1->n; i++)//�����ֵܽ��
	{
		p->key[(p->n) + 1 + i] = p1->key[i];//�ؼ����p1��p����
		p->ptr[(p->n) + i + 1] = p1->ptr[i];//ָ���p1��p����
	}
	compress(q, j);//���ڵ�q��ֵ��ָ������
	p->n = p->n + p1->n + 1;
	delete p1;
}


void createLibrary(Btree& btree)
{
	ifstream fin;
	fin.open("ͼ���.txt");//����ǰ¼�����Ϣ���ļ�
	if (fin.fail())//�ļ���ʧ��
	{
		cout << "�ļ���ʧ��,ͼ��ݳ�ʼ��ʧ�ܣ�" << endl;
		exit(1);
	}

	while (!fin.eof())//�ж�ȡ
	{
		BookNode* node = new BookNode;
		char* str = new char[200];
		fin.getline(str, 200, '\n');//��ȡһ������
		int i = 0;//��¼�������λ��
		int x = 0;//���
		int d = 0;//�ִ�
		int c = 0;//�ܴ�
		string k;
		for (; str[i] != ' '; i++)//��ȡ���
		{
			x = x * 10 + (int(str[i]) -int('0'));
			node->BookNum = x;
		}
		i++;//�ָ����� ��

		for (int j = 0; str[i] != ' '; j++, i++)//��������
		{
			node->Name += str[i];
		}
		i++;//�ָ����� ��

		for (int j = 0; str[i] != ' '; j++, i++)//��������
		{
			node->Author += str[i];
		}
		i++;//�ָ�����-��

		for (; str[i] != ' '; i++)//��ȡ���ִ���
		{
			
			d = (int(str[i]) - int('0'));
			node->currentNum =d;
		}
		i++;

		for (; str[i] != ' '; i++)//��ȡ������
		{
			
			c = (int(str[i]) - int('0'));
			node->totalNum= c;
		}

		btree.Insert(node,btree);//������
		delete[]str;
		delete node;
	}
	fin.close();
}
