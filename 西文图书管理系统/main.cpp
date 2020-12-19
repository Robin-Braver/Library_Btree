#include"Library.h"
#include <stdlib.h>

int main()
{
	Library Lib;//����ͼ��ݶ���
	Btree tree;
	BtreeNode* root;
	createLibrary(tree);
	root = tree.root;
	while (1)
	{
		//������
		cout << "*********************************************************" << endl;
		cout << "*                                                       *" << endl;
		cout << "*" << "\t" << "\t" << "��ӭʹ��STAR����ͼ�����ϵͳ" << "\t" << "\t" << "*" << endl;
		cout << "*                                                       *" << endl;
		cout << "*" << "\t" << "\t" << "      " << "1������Աģʽ" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*" << "\t" << "\t" << "     " << " 2��ѧ��ģʽ" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*" << "\t" << "\t" << "    " << "  0���˳�ϵͳ" << "\t" << "\t" << "\t" << "*" << endl;
		cout << "*                                                       *" << endl;
		cout << "*********************************************************" << endl;
		cout << "��ѡ��Ȩ��ģʽ��";

		int choice1;//ѡ��Ȩ��
		cin >> choice1;
		if (choice1 == 1)
		{
			int flag = 1;
			while (flag==1)
			{
				system("cls");
				cout << "*********************************************************" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "��ӭʹ��STAR����ͼ�����ϵͳ" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "    " << "��ǰ״̬������Ա״̬" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "      " << "1���ɱ����" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "     " << " 2����տ���" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "3������ͼ��	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "4���黹ͼ��	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "5��Ѱ��ͼ��" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "6���鿴ͼ���״̬" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "7��ɾ��ͼ��" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "0������" << "\t" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*********************************************************" << endl;
				int choice2;//����ģʽ����ѡ��
				cout << "��ѡ����Ҫʹ�õķ���";
				cin >> choice2;
				system("cls");
				switch (choice2)
				{
				case 0:
					flag = 0;
					break;
				case 1:
					Lib.InputBook(tree);//�ɱ����
					cout << "��ѡ��������Ĳ���:" <<endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 2:
					Lib.clearLibrary(root, tree);//��տ��
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 3:
					Lib.LendBook(tree);//�����鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 4:
					Lib.ReturnBook(tree);//�黹�鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 5:
					Lib.SearchBook(tree);//�����鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 6:
					Lib.showLibrary(root);//չʾͼ�����Ϣ
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 7:
					Lib.DeleteBook(tree);//ɾ��ͼ��	
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
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
				cout << "*" << "\t" << "\t" << "��ӭʹ��STAR����ͼ�����ϵͳ" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "    " << "��ǰ״̬��ѧ��״̬" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*" << "\t" << "\t" << "      " << "1������ͼ��	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "2���黹ͼ��	" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "3��Ѱ��ͼ��" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "4���鿴ͼ���״̬" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*" << "\t" << "\t" << "      " << "0������" << "\t" << "\t" << "\t" << "\t" << "*" << endl;
				cout << "*                                                       *" << endl;
				cout << "*********************************************************" << endl;

				int choice2;//ѧ������ѡ��
				cout << "��ѡ����Ҫʹ�õķ���";
				cin >> choice2;
				system("cls");
				switch (choice2)
				{
				case 0:
					flag = 0;
					break;
				case 1:
					Lib.LendBook(tree);//�����鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 2:
					Lib.ReturnBook(tree);//�黹�鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 3:
					Lib.SearchBook(tree);//�����鼮
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				case 4:
					Lib.showLibrary(root);//չʾͼ�����Ϣ
					Lib.printTree(root, 1);//���뷨��ӡ
					cout << "��ѡ��������Ĳ���:" << endl;
					cout << "1���������в���" << endl;
					cout << "0��������һ��" << endl;
					cin >> flag;
					system("cls");
					break;
				}
			}
		}
		else if (choice1 == 0)
		{
			cout << "�˳��ɹ����ڴ��ٴ�ʹ�ã�" << endl;
			return 0;
		}
		else
		{
			cout << "�����������������룡" << endl;
		}
	}
}