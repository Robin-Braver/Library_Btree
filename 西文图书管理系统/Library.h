#pragma once
#include"B-tree.h"
#include<iostream>
#include<fstream>
class Library
{
public:
	void InputBook(Btree&btree);//采编入库
	void DeleteBook(Btree& btree);//删除图书
	void LendBook(Btree& btree);//借书
	void ReturnBook(Btree& btree);//还书
	void showLibrary(BtreeNode* t);//展示图书系统信息
	void printTree(BtreeNode* t, int level);//凹入法打印B-tree
	void SearchBook( Btree& btree);//查找书信息
	void clearLibrary(BtreeNode* t, Btree& btree);//清空库存
	void TraverseLibrary(BtreeNode* t, int& num, int& Vnum);
private:
	Btree btree;//B-tree实现各种操作
	friend class Btree;
};

void Library::InputBook( Btree& btree)//采编入库
{
	bool result;//插入结果
	BookNode* Book = new BookNode;//插入图书
	cout << "请输入采编书籍的相关信息：" << endl;
	cout << "书号为：";
	cin >> Book->BookNum;
	Triple a=btree.Search(Book->BookNum,btree);//检测这本书是否存在于图书馆中
	if (a.tag == 0)//存在
	{
		int n;//添加书籍的数量
		cout << "由于此书已经存在于本系统，故请直接输入添加书籍的数量：";
		cin >> n;
		Book->currentNum = n;//修改插入书的现存
		Book->totalNum = n;//修改插入书的总量
	}
	else
	{
		int n;//插入书籍的数量
		cout << "书名为：";
		cin >> Book->Name;
		cout << "该书作者为：";
		cin >> Book->Author;
		cout << "添加该书数量为：";
		cin >> n;
		Book->currentNum = Book->currentNum + n;
		Book->totalNum = Book->totalNum + n;
	}
	result=btree.Insert(Book,btree);
	if (result == true)
		cout << "书籍采编入库成功！！！" << endl;
	cout << endl;
	delete Book;
}

void Library::DeleteBook( Btree& btree)
{
	bool result;//搜索
	int x ;//获取删除书籍书号
	cout << "请输入要删除书籍的书号：";
	cin >> x;
	result = btree.Remove(x, btree);
	if (result == false)
			cout << "删除书籍不在系统中，请确认后再试！" << endl;
	else
		cout << "删除成功！" << endl;
}
	

void Library::LendBook(Btree& btree)
{
	Triple result;
	int bookNum;//还书的书号
	int flag = 1;//标志
	while (flag)
	{
		cout << "请输入借阅书籍的书号：";
		cin >> bookNum;
		result = btree.Search(bookNum, btree);//搜索是否在树中
		if (result.tag == 1)
			cout << "所借阅书籍不在系统中，请确认书号后移重新输入！" << endl;
		else
		{
			BookNode book = result.r->key[result.i];//获取b-tree中查找书的信息
			if (book.currentNum < 1)//数量小于1
				cout << "当前书籍无剩余馆藏，借阅失败！" << endl;
			else
			{
				int flag2=1;//二重循环控制
				while (flag2 == 1)
				{
					int n = 0;//借阅图书的数量
					cout << "借阅图书信息如下：" << endl;
					cout << book;
					cout << "请输入借阅图书数量：";
					cin >> n;
					if (n > book.currentNum)
					{
						cout << "输入数量大于当前书籍的数量，借阅失败！" << endl;
						flag2 = 0;
					}
					else if (n < 1)
						cout << "请输入正确数字！！" << endl;
					else
					{
						book.currentNum -= n;//现存量减少
						result.r->key[result.i] = book;//修改为原来的值
						cout << "借阅成功！" << endl;
						flag2 = 0;//结束循环
					}
				}
				flag = 0;//结束循环
			}
		}	
	}
}



void Library::ReturnBook(Btree& btree)
{
	Triple result;
	int bookNum;
	int flag = 1;//标志
	while (flag == 1)
	{
		cout << "请输入归还书籍的书号：";
		cin >> bookNum;
		result = btree.Search(bookNum, btree);
		if (result.tag == 1)
			cout << "所归还的书籍不在系统中，请确认书号后重新输入！" << endl;
		else
		{
			BookNode book = result.r->key[result.i];//获取b-tree中查找书的信息
			int flag2 = 1;
			while(flag2==1)
			{
				int n = 0;//还书数量
				cout << "请输入还书的数量：";
				cin >> n;
				if (book.currentNum == book.totalNum)
					cout << "所归还的书并非来自本系统，请确认后再归还" << endl;
				else if (n < 1)
					cout << "请输入正确的还书本书！！" << endl;
				else if (n + book.currentNum > book.totalNum)
					cout << "所还书的数量过多，请确认后的再输入！！" << endl;
				else
				{
					book.currentNum += n;//现存量增加
					result.r->key[result.i] = book;//修改为原来的值
					cout << "还书成功！" << endl;
					flag2 = 0;
				}
			}
			flag = 0;
		}
	}
}


void Library::printTree(BtreeNode*t,int level)//凹入法打印B-tree，展示图书信息,传入根节点
{
	if (t == NULL)return;//空B树 返回
	int n = t->n;//获取当前结点的关键码个数
	int i =1,j;
	while (i <= n)
	{
		printTree(t->ptr[i - 1], level + 1);
		for (j = 0; j < level; j++)
			cout << "**********";
		if (level >=0)
		{
			if(level>1)
				cout << "------";
			cout << t->key[i].BookNum;
			cout << endl;
		}
		i++;
		
	}
	printTree(t->ptr[i-1],level + 1);
}


void Library::TraverseLibrary(BtreeNode* t, int& num, int& Vnum)
//遍历B-tree：展示图书系统信息, num:图书馆有多少本书,Vnum:图书馆有多少种书
{
	if (t != NULL)//空B树 返回
	{
		int n = t->n;
		for (int i = 0; i <= n; i++)
		{
			TraverseLibrary(t->ptr[i], num, Vnum);
			if(i+1<=n)
			{
				cout << t->key[i + 1];
				Vnum++;
				num = num + t->key[i + 1].totalNum;
			}
		}
	}
}

void Library::showLibrary(BtreeNode* t)//展示图书系统信息
{
	int num = 0;//图书馆一共有多少本书
	int Vnum = 0;//图书馆书种类
	int cVum = 0;//图书馆当前书籍总量
	cout << "*****************************************************************************************************************" << endl;
	TraverseLibrary(t, num, Vnum);
	cout << "*****************************************************************************************************************" << endl;
	cout << endl;
	cout << setw(30)<<"图书馆一共有" << num << "本书" << '\t' <<setw(30)<< "这些书共包含" << Vnum << "种类" << endl;
	printTree(t, 1);//凹入法打印
}

void Library::SearchBook(Btree& btree)//查找书信息
{
	Triple result;
	int bookNum;//书号
	cout << "请输入要查找书籍的序号：";
	cin >> bookNum;
	result=btree.Search(bookNum,btree);
	if (result.tag == 1)
		cout << "搜索失败，该书籍不在本系统中！" << endl;
	else
	{
		cout << "搜索成功!" << endl;
		cout << "搜索图书信息如下："<<endl;
		cout << result.r->key[result.i];//输出查找结果
	}
}

void Library::clearLibrary(BtreeNode* t, Btree& btree)//置空图书馆
{

	while(t ->n>0)
	{
		int x = t->key[1].BookNum;
		btree.Remove(x, btree);//根据remove调整特性，重复删除根第一个结点
	}
	cout << "系统图书清空成功！" << endl;
	cout << endl;
	//btree.root = NULL;
}

