#include"Library.h"
#include <stdlib.h>

int main()
{
	Library Lib;//定义图书馆对象
	Btree tree;
	BtreeNode* root;
	createLibrary(tree);
	root = tree.root;
	while (1)
	{
		//功能区
		cout << "*********************************************************" << endl;
		cout << "*                                                       *" << endl;
		cout << "*" << "\t" << "\t" << "欢迎使用STAR西文图书管理系统" << "\t" << "\t" << "*" << endl;
		cout << "*                                                       *" << endl;
		cout << "*" << "\t" << "\t" << "      " << "1：管理员模式" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*" << "\t" << "\t" << "     " << " 2：学生模式" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*" << "\t" << "\t" << "    " << "  0：退出系统" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*                                                       *" << endl;
		cout << "*********************************************************" << endl;
		cout << "请选择权限模式：";

		int choice1;//选择权限
		cin >> choice1;
		if (choice1 == 1)
		{
			int flag = 1;
			while (flag==1)
			{
				system("cls");
				cout << "*********************************************************" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "欢迎使用STAR西文图书管理系统" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "    " << "当前状态：管理员状态" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "      " << "1：采编入库" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "     " << " 2：清空库存库" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "3：借阅图书	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "4：归还图书	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "5：寻找图书" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "6：查看图书馆状态" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "7：删除图书" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "0：返回" << "\t" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*********************************************************" << endl;
				int choice2;//管理模式服务选择
				cout << "请选择你要使用的服务：";
				cin >> choice2;
				system("cls");
				switch (choice2)
				{
				case 0:
					flag = 0;
					break;
				case 1:
					Lib.InputBook(tree);//采编入库
					cout << "请选择接下来的操作:" <<endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 2:
					Lib.clearLibrary(root, tree);//清空库存
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 3:
					Lib.LendBook(tree);//借阅书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 4:
					Lib.ReturnBook(tree);//归还书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 5:
					Lib.SearchBook(tree);//查找书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 6:
					Lib.showLibrary(root);//展示图书馆信息
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 7:
					Lib.DeleteBook(tree);//删除图书	
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				}
			}
		}
		else if (choice1 == 2)
		{
			int flag = 1;
			while (flag == 1)
			{
				system("cls");
				cout << "*********************************************************" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "欢迎使用STAR西文图书管理系统" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "    " << "当前状态：学生状态" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "      " << "1：借阅图书	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "2：归还图书	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "3：寻找图书" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "4：查看图书馆状态" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "0：返回" << "\t" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*********************************************************" << endl;

				int choice2;//学生服务选择
				cout << "请选择你要使用的服务：";
				cin >> choice2;
				system("cls");
				switch (choice2)
				{
				case 0:
					flag = 0;
					break;
				case 1:
					Lib.LendBook(tree);//借阅书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 2:
					Lib.ReturnBook(tree);//归还书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 3:
					Lib.SearchBook(tree);//查找书籍
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				case 4:
					Lib.showLibrary(root);//展示图书馆信息
					Lib.printTree(root, 1);//凹入法打印
					cout << "请选择接下来的操作:" << endl;
					cout << "1：继续进行操作" << endl;
					cout << "0：返回上一级" << endl;
					cin >> flag;
					system("cls");
					break;
				}
			}
		}
		else if (choice1 == 0)
		{
			cout << "退出成功！期待再次使用！" << endl;
			return 0;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
		}
	}
}