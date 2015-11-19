// 由前序序列和中序序列构造二叉树.cpp : 定义控制台应用程序的入口点。  
//  

#include <stdafx.h> 
#include <string>  
#include <iostream>  

using namespace std;

//二叉链表表示二叉树  
typedef struct BiNode
{
	char data;//节点数据  
	struct BiNode * lchild;//左孩子  
	struct BiNode * rchild;//右孩子  
}BiNode, *BiTree;

//由前序序列和中序序列建立二叉树的过程  
void CreateBiTree(BiTree & t, string presequence, string insequence)//t为要建立的二叉树,presequence和insequence分别为前序和中序序列  
{
	if (presequence.length() == 0)
	{
		t = NULL;
		return;
	}
	char rootNode = presequence[0];//根  
	int index = insequence.find(rootNode);//根在中序序列中的位置  
	string lchild_insequence = insequence.substr(0, index);//左孩子的中序序列  
	string rchild_insequence = insequence.substr(index + 1);//右孩子的中序序列  
	int lchild_length = lchild_insequence.length();//左孩子的长度  
	int rchild_length = rchild_insequence.length();//右孩子的长度  
	string lchild_presequence = presequence.substr(1, lchild_length);//左孩子的前序序列  
	string rchild_presequence = presequence.substr(1 + lchild_length);//右孩子的前序序列  

	t = (BiTree)malloc(sizeof(BiNode));
	if (t != NULL)
	{
		t->data = rootNode;
		CreateBiTree(t->lchild, lchild_presequence, lchild_insequence);//递归创建左孩子  
		CreateBiTree(t->rchild, rchild_presequence, rchild_insequence);//递归创建右孩子  
	}
}

//检验是否创建成功   
//递归前序遍历二叉树  
void PreOrderTraverse(BiTree & t)
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrderTraverse(t->lchild);
		PreOrderTraverse(t->rchild);
	}
}

//递归中序序遍历二叉树  
void InOrderTraverse(BiTree & t)
{
	if (t != NULL)
	{

		InOrderTraverse(t->lchild);
		cout << t->data;
		InOrderTraverse(t->rchild);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	BiTree t;
	string presequence = "ABCDEFG";
	string insequence = "CBEDAFG";
	CreateBiTree(t, presequence, insequence);

	PreOrderTraverse(t);
	cout << endl;
	InOrderTraverse(t);
	system("PAUSE");
	return 0;
}