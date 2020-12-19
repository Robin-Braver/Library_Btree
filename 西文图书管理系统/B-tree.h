#pragma once
#include <cfloat>
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const int MaxValue = INT_MAX;

struct BookNode//书结点类
{
	BookNode();
	int BookNum;//书号
	string Name;//书名
	string Author;//作者
	int currentNum;//现存量
	int totalNum;//总量
};

ostream& operator<<(ostream& out, BookNode& Book)//重载输出书结点类
{
	out << "*书号：" << Book.BookNum << "  ";
	out << "书名："<< setw(42) << Book.Name << '\t';
	out << "作者：" << setw(10) << Book.Author << '\t';
	out << "现存量：" << setw(2) << Book.currentNum << '\t';
	out << "总量：" << setw(2) << Book.totalNum <<"*"<< endl;
	return out;
}

istream& operator>>(istream&in, BookNode& Book)//重载输出书结点类
{
	int n;
	cout << "书号为：";
	in>> Book.BookNum;
	cout << "书名为：";
	in >> Book.Name;
	cout << "该书作者为：";
	in >> Book.Author;
	cout << "添加该书数量为：";
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

struct BtreeNode//树结点定义
{
	BtreeNode();
	int n;//关键码个数
	BtreeNode* parent;//父节点指针
	BookNode key[5];//key[4]为监察哨，key[0]不使用
	BtreeNode* ptr[5];//子树结指针数组,ptr[m]在插入溢出时使用
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

struct Triple//搜索结果三元组
{
	BtreeNode* r;//结点地址指针
	int i;//结点中关键码序号i
	int tag;//tag=0，搜索成功，为1失败
};

class Btree
{
protected:
	const int m = 4;//路数，最大子树棵树	
public:
	BtreeNode* root;//根指针
	Btree();//构造函数
	Triple Search(const int&x, Btree& Btree);//搜索
	bool Insert(BookNode *booknode,Btree&Btree);//
	bool Remove(int& x,Btree& Btree);//删除关键码x
	void insertkey(BtreeNode* p, int j, BookNode& booknode, BtreeNode* ap);//插入算法里：在节点数组内部插入
	void move(BtreeNode* p, BtreeNode* q, int s, int m);//插入算法：分裂移动操作
	void compress(BtreeNode* p, int j);//删除算法：结点前移操作
	void LeftAdjust(BtreeNode* p, BtreeNode* q, int d, int j);//删除算法：左调整
	void RightAdjust(BtreeNode* p, BtreeNode* q, int d, int j);//删除算法：右调整
	void merge(BtreeNode* p, BtreeNode* q, BtreeNode* p1, int j);//删除算法：合并
};

Btree::Btree()
{
	root = new BtreeNode;
}


Triple Btree::Search(const int& x, Btree& Btree)//搜索算法
//用关键字x搜索，各节点格式为n，p[0],(k[1],p[1]),......,(k[n],p[n]),n<m.函数返回Triple类型，搜索失败时，可以插入结，结点在k[i]与[i+1]之
{
	Triple result;//结果三元组
	BtreeNode* p =root;//获取根节点
	BtreeNode* q=NULL;//p是扫描指针，q是p父节点指针
	int j=1;
	while (p != NULL)//从根开始检测
	{
		int i = 0; p->key[(p->n) + 1].BookNum= MaxValue;
		while (p->key[i + 1].BookNum < x)i++;//结点内搜索
		if (p->key[i + 1] .BookNum== x)
		{
			result.r = p; result.i = i + 1; result.tag = 0;
			return result;//返回结果
		}
		q = p; p = p->ptr[i];//本节点无x,查找子树
		j = i;
	}
	result.r = q; result.i = j; result.tag = 1;
	return result;//搜索失败，返回插入位置
};

void Btree::insertkey(BtreeNode* p, int j, BookNode& booknode, BtreeNode* ap)//p是插入结点，j是结点数组内部位置，K是插入的值，ap是插入关键码x的右邻指针
{
	for (int i = p->n; i > j; i--)//j位置后的元素依次后移
		p->key[i + 1] = p->key[i];
	p->key[j+1] = booknode;//插入关键码
	for (int i = p->n;i > j; i--)//j位置后的子树指针依次后移
		p->ptr[i + 1] = p->ptr[i];
	p->ptr[j+1] = ap;
	(p->n)  ++;//个数+1
}

void Btree::move(BtreeNode* p, BtreeNode* q, int s, int m)//p是插入结点，q是建立的新结点即分裂的结点，s是分裂的在原数组结点位置，m是阶数
{
	int i, j;
	for (i = 1, j = s + 1; j < m + 1; i++, j++)//将p的key[s+1...m]移动q的ptr[1..s-1]
	{
		q->key[i] = p->key[j];
		//p->key[j].BookNum = MaxValue;
	}
	for (i = 0, j = s; j < m + 1; i++, j++)//将ptr[s..m]移动到q的ptr[0..s-1]
	{
		q->ptr[i] = p->ptr[j];
		if (p->ptr[j] != NULL)q->ptr[i]->parent = q;
		//p->ptr[j] = NULL;
	}
	p->n = s - 1;//原结点个数减少
	q->n = m - s;//分裂节点个数
}

bool Btree::Insert(BookNode*booknode, Btree& Btree)
{
	int x = booknode->BookNum;//获取目标书籍的书号
	Triple loc = Search(x,Btree);//在树种搜索x的插入位置
	BtreeNode* p = loc.r, * q;//r是关键码要插入的位置
	BtreeNode* ap = NULL, * t;//ap是插入关键码的右邻指针
	BookNode K=*booknode;
	int j = loc.i;//（k，ap）形成插入二元组
	if (K.BookNum < 0)return false;
	if (loc.tag==0)//x已经在树中，不插入
	{
		(p->key[j].currentNum)+=booknode->currentNum;//书现存量加
		(p->key[j].totalNum)+=booknode->totalNum;//书总量加
		return true;
	}
	
	while (1)
	{
		if (p->n < m - 1)//关键码个数未超出
		{
			insertkey(p, j, K, ap);//K,ap插入到j位置，且p->n加1
			return true;//输出结点
		}
		int s = (m + 1) / 2;//准备分裂节点，s是m/2取上整
		insertkey(p, j,K, ap);//先插入，结点p->n达到m
		q = new BtreeNode;//建立新结点q
		move(p, q, s, m);//将p的key[s+1..m]和ptr[s..m]移动到q的key[1..s-1]和ptr[0..s-1],p->n改为s-1,q->n改为m-s
		K = p->key[s]; ap = q;//(K,ap)形成向上插入二元组
		if (p->parent != NULL)//向上调整：原来p不为根
		{
			t = p->parent;//读取p父节点t
			j = 0;
			t->key[(t->n) + 1].BookNum= MaxValue;//父节点内顺序搜索插入位置
			while (t->key[j + 1] .BookNum< K.BookNum)j++;//找到大于K的关键码位置
			q->parent = p->parent;//新结点父指针赋值
			p = t;//p上升到父节点，向上调整
		}
		else
		{
			root = new BtreeNode;
			root->n = 1; root->parent = NULL;//创建新根
			root->key[1] = K;
			root->ptr[0] = p; root->ptr[1] = ap;
			q->parent = p->parent = root;
			return true;
		}
	}
};

bool Btree::Remove(int& x,Btree& Btree)
{
	Triple loc = Search(x,Btree);//搜索x
	if (loc.tag == 1)return false;//结点不存在，不删除
	BtreeNode* p = loc.r;
	BtreeNode* q;
	BtreeNode* s;
	int j = loc.i;
	if (p->ptr[j] != NULL)//非叶结点
	{
		s = p->ptr[j]; q = p;
		while (s != NULL) { q = s; s = s->ptr[0]; }
		p->key[j] = q->key[1];//从叶结点替补
		compress(q, 1);//在叶结点删除
		p = q;//转化为叶结点删除
	}//compress(q,k)表示吧结点q和k以后指针和关键码前移，删除key[k]
	else compress(p, j);//叶结点直接删除
	int d = (m + 1) / 2;
	while (1)//调整或者合并
	{
		if (p->n < d - 1)//小于最小限制
		{
			j = 0; q = p->parent;//找到父节点
			while (j <= q->n && q->ptr[j] != p)//在父节点找调整位置
				j++;
			if (j == 0)LeftAdjust(p, q, d, j);//结点与父节点q与p的右兄弟联合调整，j是q结点中调整的位置
			else RightAdjust(p, q, d, j);//结点p与父节点q与p的左兄弟联合调整，j是q结点中调整位置
			p = q;
			if (p == root)break;
		}
		else break;//不调整
	}
	if (root->n == 0)//调整后根的n为0
	{
		p = root->ptr[0];
		delete root;
		root = p;//删除根
		root->parent = NULL;//新根
	}
	return true;
};

void Btree::LeftAdjust(BtreeNode* p, BtreeNode* q, int d, int j)
//结点p与其父节点q一起调整，d是结点最少保持阶数，j是父节点调整位置
{
	BtreeNode* p1 = q->ptr[j + 1];//p的右兄弟
	if (p1->n > d - 1)//右兄弟空间还够，仅做调增
	{
		p->n++;
		p->key[p->n] = q->key[j + 1];//父节点相应关键码下移
		q->key[j + 1] = p1->key[1];//右兄弟最小关键码上移父节点
		p->ptr[p->n] = p1->ptr[0];//右兄弟最左指针左移
		p1->ptr[0] = p1->ptr[1];//右兄弟剩余关键码与指针前移
		compress(p1, 1);
	}
	else merge(p, q, p1, j + 1);//p与p1合并，保留p结点
}

void Btree::RightAdjust(BtreeNode* p, BtreeNode* q, int d, int j)
//结点p与其父节点q一起调整，d是结点最少保持阶数，j是父节点调整位置
{
	BtreeNode* p1 = q->ptr[j -1];//p的左兄弟
	if (p1->n > d - 1)//左兄弟空间还够，仅做调增
	{
		p->n++;
		p->key[p->n] = q->key[j - 1];//父节点相应关键码下移
		q->key[j -1] = p1->key[1];//左兄弟最小关键码上移父节点
		p->ptr[p->n] = p1->ptr[0];//左兄弟最左指针左移
		p1->ptr[0] = p1->ptr[1];//左兄弟剩余关键码与指针前移
		compress(p1, 1);
	}
	else merge(p, q, p1, j -1);//p与p1合并，保留p结点
}


void Btree::compress(BtreeNode* p,int j)
{
	for (int i = j; i < p->n; i++)//左移
	{
		p->key[i] = p->key[i + 1]; p->ptr[i] = p->ptr[i + 1];
	}
	p->n--;//结点元素个数减1
}

void Btree::merge(BtreeNode* p, BtreeNode* q, BtreeNode* p1, int j)//合并
{
	p->key[(p->n) + 1] = q->key[j];//从父节点下降一个关键码
	p->ptr[(p->n) + 1] = p1->ptr[0];//从右兄弟结点左移一个指针
	for (int i = 1; i <= p1->n; i++)//从右兄弟结点
	{
		p->key[(p->n) + 1 + i] = p1->key[i];//关键码从p1到p左移
		p->ptr[(p->n) + i + 1] = p1->ptr[i];//指针从p1到p左移
	}
	compress(q, j);//父节点q中值与指针左移
	p->n = p->n + p1->n + 1;
	delete p1;
}


void createLibrary(Btree& btree)
{
	ifstream fin;
	fin.open("图书馆.txt");//打开提前录入好信息的文件
	if (fin.fail())//文件打开失败
	{
		cout << "文件打开失败,图书馆初始化失败！" << endl;
		exit(1);
	}

	while (!fin.eof())//行读取
	{
		BookNode* node = new BookNode;
		char* str = new char[200];
		fin.getline(str, 200, '\n');//读取一行数据
		int i = 0;//记录在数组的位置
		int x = 0;//书号
		int d = 0;//现存
		int c = 0;//总存
		string k;
		for (; str[i] != ' '; i++)//读取书号
		{
			x = x * 10 + (int(str[i]) -int('0'));
			node->BookNum = x;
		}
		i++;//分隔符“ ”

		for (int j = 0; str[i] != ' '; j++, i++)//读入书名
		{
			node->Name += str[i];
		}
		i++;//分隔符“ ”

		for (int j = 0; str[i] != ' '; j++, i++)//读入作者
		{
			node->Author += str[i];
		}
		i++;//分隔符“-”

		for (; str[i] != ' '; i++)//读取书现存量
		{
			
			d = (int(str[i]) - int('0'));
			node->currentNum =d;
		}
		i++;

		for (; str[i] != ' '; i++)//读取书总量
		{
			
			c = (int(str[i]) - int('0'));
			node->totalNum= c;
		}

		btree.Insert(node,btree);//插入结点
		delete[]str;
		delete node;
	}
	fin.close();
}
