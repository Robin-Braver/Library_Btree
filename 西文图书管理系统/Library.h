#pragma once
#include"B-tree.h"
#include<iostream>
#include<fstream>
class Library
{
public:
	void InputBook(Btree&btree);//�ɱ����
	void DeleteBook(Btree& btree);//ɾ��ͼ��
	void LendBook(Btree& btree);//����
	void ReturnBook(Btree& btree);//����
	void showLibrary(BtreeNode* t);//չʾͼ��ϵͳ��Ϣ
	void printTree(BtreeNode* t, int level);//���뷨��ӡB-tree
	void SearchBook( Btree& btree);//��������Ϣ
	void clearLibrary(BtreeNode* t, Btree& btree);//��տ��
	void TraverseLibrary(BtreeNode* t, int& num, int& Vnum);
private:
	Btree btree;//B-treeʵ�ָ��ֲ���
	friend class Btree;
};

void Library::InputBook( Btree& btree)//�ɱ����
{
	bool result;//������
	BookNode* Book = new BookNode;//����ͼ��
	cout << "������ɱ��鼮�������Ϣ��" << endl;
	cout << "���Ϊ��";
	cin >> Book->BookNum;
	Triple a=btree.Search(Book->BookNum,btree);//����Ȿ���Ƿ������ͼ�����
	if (a.tag == 0)//����
	{
		int n;//����鼮������
		cout << "���ڴ����Ѿ������ڱ�ϵͳ������ֱ����������鼮��������";
		cin >> n;
		Book->currentNum = n;//�޸Ĳ�������ִ�
		Book->totalNum = n;//�޸Ĳ����������
	}
	else
	{
		int n;//�����鼮������
		cout << "����Ϊ��";
		cin >> Book->Name;
		cout << "��������Ϊ��";
		cin >> Book->Author;
		cout << "��Ӹ�������Ϊ��";
		cin >> n;
		Book->currentNum = Book->currentNum + n;
		Book->totalNum = Book->totalNum + n;
	}
	result=btree.Insert(Book,btree);
	if (result == true)
		cout << "�鼮�ɱ����ɹ�������" << endl;
	cout << endl;
	delete Book;
}

void Library::DeleteBook( Btree& btree)
{
	bool result;//����
	int x ;//��ȡɾ���鼮���
	cout << "������Ҫɾ���鼮����ţ�";
	cin >> x;
	result = btree.Remove(x, btree);
	if (result == false)
			cout << "ɾ���鼮����ϵͳ�У���ȷ�Ϻ����ԣ�" << endl;
	else
		cout << "ɾ���ɹ���" << endl;
}
	

void Library::LendBook(Btree& btree)
{
	Triple result;
	int bookNum;//��������
	int flag = 1;//��־
	while (flag)
	{
		cout << "����������鼮����ţ�";
		cin >> bookNum;
		result = btree.Search(bookNum, btree);//�����Ƿ�������
		if (result.tag == 1)
			cout << "�������鼮����ϵͳ�У���ȷ����ź����������룡" << endl;
		else
		{
			BookNode book = result.r->key[result.i];//��ȡb-tree�в��������Ϣ
			if (book.currentNum < 1)//����С��1
				cout << "��ǰ�鼮��ʣ��ݲأ�����ʧ�ܣ�" << endl;
			else
			{
				int flag2=1;//����ѭ������
				while (flag2 == 1)
				{
					int n = 0;//����ͼ�������
					cout << "����ͼ����Ϣ���£�" << endl;
					cout << book;
					cout << "���������ͼ��������";
					cin >> n;
					if (n > book.currentNum)
					{
						cout << "�����������ڵ�ǰ�鼮������������ʧ�ܣ�" << endl;
						flag2 = 0;
					}
					else if (n < 1)
						cout << "��������ȷ���֣���" << endl;
					else
					{
						book.currentNum -= n;//�ִ�������
						result.r->key[result.i] = book;//�޸�Ϊԭ����ֵ
						cout << "���ĳɹ���" << endl;
						flag2 = 0;//����ѭ��
					}
				}
				flag = 0;//����ѭ��
			}
		}	
	}
}



void Library::ReturnBook(Btree& btree)
{
	Triple result;
	int bookNum;
	int flag = 1;//��־
	while (flag == 1)
	{
		cout << "������黹�鼮����ţ�";
		cin >> bookNum;
		result = btree.Search(bookNum, btree);
		if (result.tag == 1)
			cout << "���黹���鼮����ϵͳ�У���ȷ����ź��������룡" << endl;
		else
		{
			BookNode book = result.r->key[result.i];//��ȡb-tree�в��������Ϣ
			int flag2 = 1;
			while(flag2==1)
			{
				int n = 0;//��������
				cout << "�����뻹���������";
				cin >> n;
				if (book.currentNum == book.totalNum)
					cout << "���黹���鲢�����Ա�ϵͳ����ȷ�Ϻ��ٹ黹" << endl;
				else if (n < 1)
					cout << "��������ȷ�Ļ��鱾�飡��" << endl;
				else if (n + book.currentNum > book.totalNum)
					cout << "��������������࣬��ȷ�Ϻ�������룡��" << endl;
				else
				{
					book.currentNum += n;//�ִ�������
					result.r->key[result.i] = book;//�޸�Ϊԭ����ֵ
					cout << "����ɹ���" << endl;
					flag2 = 0;
				}
			}
			flag = 0;
		}
	}
}


void Library::printTree(BtreeNode*t,int level)//���뷨��ӡB-tree��չʾͼ����Ϣ,������ڵ�
{
	if (t == NULL)return;//��B�� ����
	int n = t->n;//��ȡ��ǰ���Ĺؼ������
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
//����B-tree��չʾͼ��ϵͳ��Ϣ, num:ͼ����ж��ٱ���,Vnum:ͼ����ж�������
{
	if (t != NULL)//��B�� ����
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

void Library::showLibrary(BtreeNode* t)//չʾͼ��ϵͳ��Ϣ
{
	int num = 0;//ͼ���һ���ж��ٱ���
	int Vnum = 0;//ͼ���������
	int cVum = 0;//ͼ��ݵ�ǰ�鼮����
	cout << "*****************************************************************************************************************" << endl;
	TraverseLibrary(t, num, Vnum);
	cout << "*****************************************************************************************************************" << endl;
	cout << endl;
	cout << setw(30)<<"ͼ���һ����" << num << "����" << '\t' <<setw(30)<< "��Щ�鹲����" << Vnum << "����" << endl;
	printTree(t, 1);//���뷨��ӡ
}

void Library::SearchBook(Btree& btree)//��������Ϣ
{
	Triple result;
	int bookNum;//���
	cout << "������Ҫ�����鼮����ţ�";
	cin >> bookNum;
	result=btree.Search(bookNum,btree);
	if (result.tag == 1)
		cout << "����ʧ�ܣ����鼮���ڱ�ϵͳ�У�" << endl;
	else
	{
		cout << "�����ɹ�!" << endl;
		cout << "����ͼ����Ϣ���£�"<<endl;
		cout << result.r->key[result.i];//������ҽ��
	}
}

void Library::clearLibrary(BtreeNode* t, Btree& btree)//�ÿ�ͼ���
{

	while(t ->n>0)
	{
		int x = t->key[1].BookNum;
		btree.Remove(x, btree);//����remove�������ԣ��ظ�ɾ������һ�����
	}
	cout << "ϵͳͼ����ճɹ���" << endl;
	cout << endl;
	//btree.root = NULL;
}

