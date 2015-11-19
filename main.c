#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�����������Ľڵ�
typedef struct node
{
	char data;
	struct node *lchild;
	struct node *rchild;
	struct node *next;
}Node, *pNode;

//����ջ�ڵ�
typedef struct stacknode
{
	struct node *parent;//�������ĸ��׽ڵ�
	int mark;//��ʶ��������Ϊ0��������Ϊ1
	int presequence_num;//����������ʼ���
	int insequence_num;//����������ʼ���
	int lenth;//���г���
	struct stacknode *next;
}Stacknode;

//����ջ
typedef struct stack
{
	struct stacknode *top;
}Stack;

//��ʼ��ջ
void Create_stack(Stack *s)
{
	s->top = (Stacknode*)malloc(sizeof(Stacknode));
	s->top->next = NULL;
}

//��ջ
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

//�ж��Ƿ�Ϊ��ջ
int Empty_stack(Stack *s)
{
	if (s->top->next == NULL)
	{
		return 1;
	}
	else
		return 0;
}
//��ջ
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

//��������
typedef struct quenode
{
	Node *front;//����
	Node *rear;//��β
			   //�Ӷ�����ӣ���β����
}Queue;

//��ʼ����
void Creat_queue(Queue *que)
{
	que->front = (Node*)malloc(sizeof(Node));
	que->rear = (Node*)malloc(sizeof(Node));
	que->front->next = que->rear;
}

//�ж϶��Ƿ�Ϊ��
int Empty_queue(Queue *que)
{
	if (que->front->next == que->rear)
	{
		return 1;
	}
	else
		return 0;
}

//���
void Inqueue(Queue *que, Node *p)
{
	p->next = que->front->next;
	que->front->next = p;
}

//����,����ֵ�ǽڵ������
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

//Ѱ��Ԫ���������е�λ�á�
int find(char a[], int n, char b)//����˵����aΪ�������飬nΪ�䳤�ȣ�b�Ǵ���Ԫ�ء�
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

//�ǵݹ齨��������
pNode Creat_tree_no_recur(char *presequence, char *insequence, int n)
{
	pNode parent, head;
	int mark, i, j, m, k;//��ǣ��������е���ʼ��ţ��������е���ʼ��ţ����г��ȣ�k���ڼ���
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

//�õݹ�ķ�������������
pNode Creat_tree_recur(char *presequence, char *insequence, int n)//����˵�������������׵�ַ ���������׵�ַ insequence����
{
	pNode root;
	char *p;
	char *q;
	int i;//��¼�����������е�λ��

	root = (Node*)malloc(sizeof(Node));
	if (n <= 1)
	{
		root->data = presequence[0];
		root->lchild = NULL;
		root->rchild = NULL;
		return root;
	}
	root->data = presequence[0];//�������еĵ�һ��Ԫ���Ƕ������ĸ���
	root->lchild = NULL;
	root->rchild = NULL;
	i = find(insequence, n, presequence[0]);
	//�Ȱ�i��һ��ִ�к�ߵ����,��ΪԪ�������ڱ������һ��
	p = presequence + 1;//p���µ���������
	q = insequence;//q���µ���������
	root->lchild = Creat_tree_recur(p, q, i);
	p = presequence + i + 1;
	q = insequence + i + 1;
	root->rchild = Creat_tree_recur(p, q, n - i - 1);
	return root;
}

/*

*/

//�������������
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

//�������������
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

//�������������
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

//�������������
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


//��������
//�������У�ABCDEGF
//�������У�CBEGDFA
//�������CGEFDBA
int main()
{
	char presequence[10];//����������������
	char insequence[10];//����������������
	int n;
	Node *root;
	Queue que;
	Creat_queue(&que);//����
	printf("�������������У�\n");
	gets(presequence);
	printf("�������������У�\n");
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