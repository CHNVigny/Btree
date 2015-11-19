#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//建立二叉树的节点
typedef struct node
{
	char data;
	struct node *lchild;
	struct node *rchild;
	struct node *next;
}Node, *pNode;

//定义栈节点
typedef struct stacknode
{
	struct node *parent;//左子树的父亲节点
	int mark;//标识，左子树为0，右子树为1
	int presequence_num;//先序序列起始标号
	int insequence_num;//中序序列起始标号
	int lenth;//序列长度
	struct stacknode *next;
}Stacknode;

//定义栈
typedef struct stack
{
	struct stacknode *top;
}Stack;

//初始化栈
void Create_stack(Stack *s)
{
	s->top = (Stacknode*)malloc(sizeof(Stacknode));
	s->top->next = NULL;
}

//进栈
void Push(Stack *s, struct node *parent, int mark, int presequence_num, int insequence_num, int lenth)
{
	struct stacknode *ss = (Stacknode*)malloc(sizeof(Stacknode));
	ss->parent = parent;
	ss->mark = mark;
	ss->presequence_num = presequence_num;
	ss->insequence_num = insequence_num;
	ss->lenth = lenth;
	ss->next = s->top->next;
	s->top->next = ss;
}

//判断是否为空栈
int Empty_stack(Stack *s)
{
	if (s->top->next == NULL)
	{
		return 1;
	}
	else
		return 0;
}
//弹栈
void Pop(Stack *s, struct node *parent, int *mark, int *presequence_num, int *insequence_num, int *lenth)
{
	Stacknode *p = s->top->next;
	if (Empty_stack(s))
	{
		exit(-1);
	}
	else
	{
		parent = p->parent;
		*mark = p->mark;
		*presequence_num = p->presequence_num;
		*insequence_num = p->insequence_num;
		*lenth = p->lenth;
		s->top->next = p->next;
		free(p);
	}
}

//建立队列
typedef struct quenode
{
	Node *front;//队首
	Node *rear;//队尾
			   //从队首入队，队尾出队
}Queue;

//初始化队
void Creat_queue(Queue *que)
{
	que->front = (Node*)malloc(sizeof(Node));
	que->rear = (Node*)malloc(sizeof(Node));
	que->front->next = que->rear;
}

//判断队是否为空
int Empty_queue(Queue *que)
{
	if (que->front->next == que->rear)
	{
		return 1;
	}
	else
		return 0;
}

//入队
void Inqueue(Queue *que, Node *p)
{
	p->next = que->front->next;
	que->front->next = p;
}

//出队,返回值是节点的数据
pNode Outqueue(Queue *que)
{
	Node *p;
	Node *q;
	p = que->front;
	q = p->next;
	while (q->next != que->rear)
	{
		p = p->next;
		q = q->next;
	}
	
	p->next = q->next;
	return q;
}

//寻找元素在数组中的位置。
int find(char a[], int n, char b)//参数说明：a为待查数组，n为其长度，b是待查元素。
{
	int i;
	for (i = 0;i < n;i++)
	{
		if (b == a[i])
		{
			break;
		}
	}
	return i;
}

//非递归建立二叉树
pNode Creat_tree_no_recur(char *presequence, char *insequence, int n)
{
	pNode parent, head;
	int mark, i, j, m, k;//标记，先序序列的起始标号，中序序列的起始标号，序列长度，k用于计数
	Stack stk;
	Create_stack(&stk);
	parent = (Node*)malloc(sizeof(Node));
	head = (Node*)malloc(sizeof(Node));
	head->lchild = NULL;
	head->rchild = NULL;
	Push(&stk, head, 0, 0, 0, n);
	while (!Empty_stack(&stk))
	{
		Pop(&stk, parent, &mark, &i, &j, &m);
		if (m > 0)
		{
			if (mark == 0) 
			{
				parent->lchild = (Node*)malloc(sizeof(Node));
				parent->lchild->data = presequence[i];
				parent->lchild->lchild = NULL;
				parent->lchild->rchild = NULL;
				k = 0;
				while (k < m)
				{
					if (presequence[i] == insequence[j + k])
					{
						break;
					}
					k = k + 1;
				}
				Push(&stk, parent->lchild, 0, i + 1, j, k);
				Push(&stk, parent->lchild, 1, i + k + 1, k + 1, m - k - 1);
			}
			else
			{
				parent->rchild = (Node*)malloc(sizeof(Node));
				parent->rchild->data = presequence[i];
				parent->rchild->lchild = NULL;
				parent->rchild->rchild = NULL;
				k = 0;
				while (k < m)
				{
					if (presequence[i] == insequence[j + k])
					{
						break;
					}
					k = k + 1;
				}
				Push(&stk, parent->rchild, 0, i + 1, j, k);
				Push(&stk, parent->rchild, 1, i + k + 1, k + 1, m - k - 1);
			}

		}
	}
	return (head->lchild);
}

//用递归的方法建立二叉树
pNode Creat_tree_recur(char *presequence, char *insequence, int n)//参数说明：先序序列首地址 中序序列首地址 insequence长度
{
	pNode root;
	char *p;
	char *q;
	int i;//记录根在中序序列的位置

	root = (Node*)malloc(sizeof(Node));
	if (n <= 1)
	{
		root->data = presequence[0];
		root->lchild = NULL;
		root->rchild = NULL;
		return root;
	}
	root->data = presequence[0];//先序序列的第一个元素是二叉树的根。
	root->lchild = NULL;
	root->rchild = NULL;
	i = find(insequence, n, presequence[0]);
	//先把i加一再执行后边的语句,因为元素数等于标号数加一。
	p = presequence + 1;//p是新的先序序列
	q = insequence;//q是新的中序序列
	root->lchild = Creat_tree_recur(p, q, i);
	p = presequence + i + 1;
	q = insequence + i + 1;
	root->rchild = Creat_tree_recur(p, q, n - i - 1);
	return root;
}

/*

*/

//先序遍历二叉树
void Preread(pNode root)
{
	printf("%c", root->data);
	if (root->lchild != NULL)
	{
		Preread(root->lchild);
	}
	if (root->rchild != NULL)
	{
		Preread(root->rchild);
	}
}

//中序遍历二叉树
void Inread(pNode root)
{
	if (root->lchild != NULL)
	{
		Inread(root->lchild);
	}
	printf("%c", root->data);
	if (root->rchild != NULL)
	{
		Inread(root->rchild);
	}
}

//后序遍历二叉树
void Postread(pNode root)
{
	if (root->lchild != NULL)
	{
		Postread(root->lchild);
	}
	if (root->rchild != NULL)
	{
		Postread(root->rchild);
	}
	if (root->data != '\0')
	{
		printf("%c", root->data);
	}
}

//层序遍历二叉树
void Seread(pNode root,Queue *que)
{
	Node *p;
	if (root->data != '\0')
	{
		printf("%c", root->data);
	}
	if (root->lchild != NULL)
	{
		Inqueue(que, root->lchild);
	}
	if (root->rchild != NULL)
	{
		Inqueue(que, root->rchild);
	}
	if (Empty_queue(que)==0)
	{
		p = Outqueue(que);
		Seread(p,que);
	}
}


//测试数据
//先序序列：ABCDEGF
//中序序列：CBEGDFA
//输出后序：CGEFDBA
int main()
{
	char presequence[10];//二叉树的先序序列
	char insequence[10];//二叉树的中序序列
	int n;
	Node *root;
	Queue que;
	Creat_queue(&que);//建队
	printf("请输入先序序列：\n");
	gets(presequence);
	printf("请输入中序序列：\n");
	gets(insequence);
	n = strlen(presequence);
	root = Creat_tree_no_recur(presequence, insequence, n);
	Preread(root);
	printf("\n");
	Inread(root);
	printf("\n");
	Postread(root);
	printf("\n");
	Seread(root, &que);
	system("pause");
	return 0;
}