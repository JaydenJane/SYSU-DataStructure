#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;
#define max_vex 25 /* ��󶥵���*/

struct ghedge // �ڽӶ��ر�߽ṹ�� 
{
	int mark;
	int ve1;
	int ve2;
	int weight;
	ghedge* path1;
	ghedge* path2;
	ghedge()
	{
		mark = 0;
		path1 = NULL;
		path2 = NULL;
	}
};

struct vex // �ڽӶ��ر�Ľ��ṹ�� 
{
	int data;
	ghedge* first;
	vex()
	{
		first = NULL;
	}
};

struct graph //ͼ�Ľṹ�� 
{
	vex adj[max_vex];
	int vexnum;
	int edgenum;
};

struct Lvex //�ڽӱ�ߵĽṹ�� 
{
	int data;
	int weight;
	Lvex* next;
	Lvex()
	{
		next = NULL;
	}
};

struct Vexnode //�ڽӱ���Ľṹ�� 
{
	int data;
	Lvex* adj;
	Vexnode()
	{
		adj = NULL;
	}	
};


void path(int vex1 , int vex2 , graph* g, int weight)//vex1��vex2 �佨���ߵĺ��� 
{
	ghedge *tmp , *p , *q;
	tmp = new ghedge;
	tmp->ve1 = vex1;
	tmp->ve2 = vex2;
	tmp->weight = weight;
	if(g->adj[vex1].first == NULL)
	{
		g->adj[vex1].first = tmp;
	}
	else
	{
		p = g->adj[vex1].first;
		if(g->adj[vex1].first->ve1 == vex1)
		{
			q = p->path1;
		}
		else if(g->adj[vex1].first->ve2 == vex1)
		{
			q = p->path2;
		}
		while(q)
		{
			if(q->ve1 == vex1)
			{
				p = q;
				q = q->path1;
			}
			else if(q->ve2 == vex1)
			{
				p = q;
				q = p->path2;
			}
		}
		if(p->ve1 == vex1) p->path1 = tmp;
		else if(p->ve2 == vex1) p->path2 = tmp;
	}
	if(g->adj[vex2].first == NULL) g->adj[vex2].first = tmp;
	else
	{
		p = g->adj[vex2].first;
		q = p->path2;
		while(q)
		{
			p = q;
			q = p->path2;
		}
		p->path2 = tmp;
	} 
} 

graph* creategraph() //����ͼ�ĺ���,Ĭ��ͼΪtestcase��ͼ�����Ϊ���� 
{
	graph *g = new graph;
	ghedge *p; 
	g->vexnum = 25;
	g->edgenum = 30;
	for(int i = 0 ; i < max_vex ; i++)
	{
		g->adj[i].data = i;
		if(i == 0)
		{
			path(0,1,g,668);
			path(0,6,g,695);
			path(0,8,g,137);
		}
		else if(i == 1)
		{
			path(1,2,g,1145);
		}
		else if(i == 2)
		{
			path(2,3,g,216);
			path(2,4,g,1892);
			path(2,5,g,676);
		}
		else if(i == 5)
		{
			path(5,6,g,511);
			path(5,15,g,842);
		}
		else if(i == 6)
		{
			path(6,7,g,349);
			path(6,14,g,534);
		}
		else if(i == 7)
		{
			path(7,8,g,674);
			path(7,13,g,651);
		}
		else if(i == 8)
		{
			path(8,9,g,704);
		}
		else if(i == 9)
		{
			path(9,10,g,397);
			path(9,11,g,305);
		}
		else if(i == 11)
		{
			path(11,12,g,242);
		}
		else if(i == 13)
		{
			path(13,19,g,825);
		}
		else if(i == 14)
		{
			path(14,18,g,409);
		}
		else if(i == 15)
		{
			path(15,16,g,1100);
			path(15,17,g,967);
		}
		else if(i == 16)
		{
			path(16,17,g,639);
		}
		else if(i == 17)
		{
			path(17,18,g,902);
			path(17,21,g,607);
		}
		else if(i == 18)
		{
			path(18,19,g,367);
			path(18,21,g,672);
			path(18,23,g,675);
		}
		else if(i == 19)
		{
			path(19,20,g,622);
		}
		else if(i == 21)
		{
			path(21,22,g,255);
		}
		else if(i == 23)
		{
			path(23,24,g,140);
		}
	}
	return g;
}

void BFS(graph *g , int v , string *place) //������ȱ��� 
{
	int n = g->vexnum;
	int *visit = new int[n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	cout << setw(8) << place[g->adj[v].data] << endl;
	queue<int> q;
	q.push(v);
	int pos;
	while(!q.empty()) //���г���һ���ڵ㣬�����Χ�ڵ㲢�Ұ���Χ�ڵ�ѹ����� 
	{
		pos = q.front();
		q.pop();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					cout << setw(8)<< place[p->ve2]   << "  ·��Ϊ�� ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve2] = 1;
					q.push(p->ve2);
				}
				p = p->path1;
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					cout <<  setw(8)  << place[p->ve1]  << "  ·��Ϊ�� ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve1] = 1;
					q.push(p->ve1);
				}
				p = p->path2;
			}	
		}
	}
	cout << "END";
}

void DFS(graph *g , int v , string *place) //����������� 
{
	int n = g->vexnum;
	int *visit = new int [n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	cout << setw(8) << place[g->adj[v].data] << endl;
	stack<int> s;
	s.push(v);
	int pos;
	while(!s.empty()) //��ȡջ��ͷ�ڵ� �������һ����Χû�б����Ľ�㲢��ѹ��ջ�������Χ�ڵ㶼�����ʹ�����ɾ����ͷ�ڵ� 
	{
		pos = s.top();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					cout << setw(8)<< place[p->ve2]   << "  ·��Ϊ�� ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve2] = 1;
					s.push(p->ve2);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path1;			
				}
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					cout <<  setw(8)  << place[p->ve1]  << "  ·��Ϊ�� ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve1] = 1;
					s.push(p->ve1);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path2;
				}
			}	
		}
		s.pop();
	}
	cout << "END";
}

Vexnode* DSPT( graph* g , int v , string* place) //�ڽӱ�洢����ȱ��������� 
{
	int n = g->vexnum;
	int *visit = new int [n];
	Vexnode *st = new Vexnode [25];
	Lvex *adj , *box;
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	stack<int> s;
	s.push(v);
	int pos;
	while(!s.empty())
	{
		pos = s.top();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					adj = new Lvex;
					adj->data = p->ve2;
					adj->weight = p->weight;
					
					if(st[p->ve1].adj == NULL) st[p->ve1].adj = adj;
					else
					{
						box = st[p->ve1].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					
					visit[p->ve2] = 1;
					s.push(p->ve2);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path1;			
				}
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					adj = new Lvex;
					adj->data = p->ve1;
					adj->weight = p->weight;
					
					if(st[p->ve2].adj == NULL) st[p->ve2].adj = adj;
					else
					{
						box = st[p->ve2].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					visit[p->ve1] = 1;
					s.push(p->ve1);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path2;
				}
			}	
		}
		s.pop();
	}
	return st;	
}

Vexnode* BSPT( graph* g , int v , string* place) //������ȱ����������� 
{
	int n = g->vexnum;
	int *visit = new int[n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	Vexnode *st = new Vexnode [25];
	Lvex *adj , *box;
	queue<int> q;
	q.push(v);
	int pos;
	while(!q.empty())
	{
		pos = q.front();
		q.pop();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					adj = new Lvex;
					adj->data = p->ve2;
					adj->weight = p->weight;
					
					if(st[p->ve1].adj == NULL) st[p->ve1].adj = adj;
					else
					{
						box = st[p->ve1].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					
					visit[p->ve2] = 1;
					q.push(p->ve2);
				}
				p = p->path1;
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					adj = new Lvex;
					adj->data = p->ve1;
					adj->weight = p->weight;
					
					if(st[p->ve2].adj == NULL) st[p->ve2].adj = adj;
					else
					{
						box = st[p->ve2].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					visit[p->ve1] = 1;
					q.push(p->ve1);
				}
				p = p->path2;
			}	
		}
	}
	return st;
}

void Preorder(Vexnode *st , int v , int *visit,string * place) //����������ǰ����� 
{
	visit[v] = 1;
	Lvex *p;
	p = st[v].adj;
	cout << place[v] <<"->"; 
	if(p == NULL) return;
	else
	{
		while(p)
		{
			if( visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Preorder(st,p->data,visit,place);
			}
		}
	}
}

void Preorder_edge(Vexnode *st , int v , int *visit,string * place) //����������ǰ����� ,�ߵ���� 
{
	visit[v] = 1;
	Lvex *p;
	p = st[v].adj; 
	if(p == NULL) return;
	else
	{
		while(p)
		{
			if( visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				cout << "  ·��Ϊ�� " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;
				Preorder_edge(st,p->data,visit,place);
			}
		}
	}
}

void Inorder(Vexnode *st , int v , int *visit , string *place)//����������������� 
{
	Lvex *p;
	int count = 0;
	if(st[v].adj == NULL)
	{
		cout << place[v] << "->";
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(count == 1) 
			{
				cout << place[v] << "->";
				visit[v] = 1;
			}
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Inorder(st,p->data,visit,place);
			}
			count++;
		}
	}
}

void Inorder_edge(Vexnode *st , int v , int *visit , string *place)//����������������� ���ߵ���� 
{
	Lvex *p;
	int count = 0;
	if(st[v].adj == NULL)
	{
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(count == 1) 
			{
				visit[v] = 1;
			}
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Inorder_edge(st,p->data,visit,place);
				cout << "  ·��Ϊ�� " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;	
			}
			count++;
		}
	}
}

void Postorder(Vexnode *st , int v , int *visit , string *place) //���������ĺ������ 
{
	Lvex *p;
	if(st[v].adj == NULL)
	{
		cout << place[v] << "->";
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Postorder(st,p->data,visit,place);
			}
		}
		cout << place[v] << "->";
		visit[v] = 1;
	}
}

void Postorder_edge(Vexnode *st , int v , int *visit , string *place)//���������ĺ������ ���ߵ���� 
{
	Lvex *p;
	if(st[v].adj == NULL)
	{
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Postorder_edge(st,p->data,visit,place);
				if(!p->next)
				{
					cout << "  ·��Ϊ�� " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;
				}
				//else cout << "    �ص㣺 " << setfill(' ') << setw(8) << place[p->data] << endl;
			}
		}
		visit[v] = 1;
	}
}

struct tnode//�ֵܺ������Ľڵ�ṹ 
{
	int data;
	tnode* child;
	tnode* brother; 
	tnode()
	{
		child = NULL;
		brother = NULL;
	}
};

void buildtree(Vexnode*st , int v , tnode* root)//�ڽӱ�洢����תΪ�ֵܺ����� 
{
	tnode *p ,*tmp;
	Lvex* q;
	q = st[v].adj;
	if(q == NULL) return;
	tmp = new tnode;
	tmp->data = q->data;
	root->child = tmp;
	p = tmp;
	buildtree(st,p->data,p);
	q = q->next;
	while(q)
	{
		tmp = new tnode;
		tmp->data = q->data;
		p->brother = tmp;
		buildtree(st,tmp->data,tmp);
		p = tmp; 
		q = q->next; 
	}		
}

void printtree(tnode* root , string* place) //���Ĵ�ӡ 
{
	int i ;
	static int deep = 0 ;
	if(root == NULL)
	{
		cout << "| | | | | | | | | | |"<< endl;
		return;
	}
	for(i = 0 ; i < deep ; i++)
	{
		cout << "| ";
	}
	cout << "depth[" << deep  << "] " << place[root->data] << endl;
	++deep;
	printtree(root->child,place);
	--deep;
	printtree(root->brother,place);
} 

string *name() //�ص�ĺ��� 
{
	string *p;
	p = new string [26];
	p[0] = "����"; p[1] = "���ͺ���"; p[2] = "����";
	p[3] = "����"; p[4] = "��³ľ��"; p[5] = "����";
	p[6] = "֣��"; p[7] = "����"; p[8] = "���";
	p[9] = "����"; p[10] = "����"; p[11] = "����";
	p[12] = "������"; p[13] = "�Ϻ�"; p[14] = "�人"; 
	p[15] = "�ɶ�"; p[16] = "����"; p[17] = "����";
	p[18] = "����"; p[19] = "�ϲ�"; p[20] = "����";
	p[21] = "����"; p[22] = "����"; p[23] = "����";
	p[24] = "����"; 
	return p;
}

void reset(int *visit)
{
	for(int i = 0 ; i < 25 ; i++)
		visit[i] = 0;
}

int main()
{
	string *place;
	place = name();
	
	graph *g;
	ghedge *p;
	g = creategraph();
	
	Vexnode *dst , *bst;
	dst = DSPT(g,0,place);
	bst = BSPT(g,0,place);
	int *visit = new int [25];
	int n; 
	string s = "";
	cout <<  "               -------------------------------------" << endl;
	cout <<  "               ---------  �й�����ͼ����  ----------" << endl;
	cout <<  "               -------------------------------------" << endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 1�� ���� 1  �����ȱ���ͼ�ĵص�����            -"<< endl;
	cout << "--- 2�� ���� 2  �����ȱ���ͼ�ĵص�����            -"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 3�� ���� 3  ������������������ǰ������ص�����-"<< endl;
	cout << "--- 4�� ���� 4  ��������������������������ص�����-"<< endl;
	cout << "--- 5�� ���� 4  �����������������ĺ�������ص�����-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 6�� ���� 6  ������������������ǰ������ص�����-"<< endl;
	cout << "--- 7�� ���� 7  ��������������������������ص�����-"<< endl;
	cout << "--- 8�� ���� 8  �����������������ĺ�������ص�����-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 9�� ���� 9  ������������������ǰ�����·������-"<< endl;
	cout << "--- 10������ 10 �������������������������·������-"<< endl;
	cout << "--- 11������ 11 �����������������ĺ������·������-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 12������ 12 ������������������ǰ�����·������-"<< endl;
	cout << "--- 13������ 13 �������������������������·������-"<< endl;
	cout << "--- 14������ 14 �����������������ĺ������·������-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 15������ 15 ��ӡ�������������                  -"<< endl;
	cout << "--- 16������ 16 ��ӡ�������������                  -"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 0������ 0 �˳�-----------------------------------"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "      ������Ҫʹ�õĹ��ܣ�" ; 
	while(cin >> n) 
	{
		if(n == 1)
		{
			cout << "��ȱ���ͼ�ĵص�����Ϊ��" << endl;
			DFS(g,0,place);
			cout << endl;
		}
		else if(n == 2)
		{
			cout << "��ȱ���ͼ�ĵص�����Ϊ��" << endl;
			BFS(g,0,place);
			cout << endl;
		}
		else if(n == 3)
		{
			cout << "���������������ǰ������ص�����Ϊ��" << endl;
			reset(visit);
			Preorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 4)
		{
			cout << "�����������������������ص�����Ϊ��" << endl;
			reset(visit);
			Inorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 5)
		{
			cout << "��������������ĺ�������ص�����Ϊ��" << endl;
			reset(visit);
			Postorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 6)
		{
			cout << "���������������ǰ������ص�����Ϊ��" << endl;
			reset(visit);
			Preorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 7)
		{
			cout << "�����������������������ص�����Ϊ��" << endl;
			reset(visit);
			Inorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 8)
		{
			cout << "��������������ĺ�������ص�����Ϊ��" << endl;
			reset(visit);
			Postorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 9)
		{
			cout << "����������������������·������Ϊ�� " << endl;
			reset(visit);
			Preorder_edge(dst,0,visit,place);
			cout << endl;
		}
		else if(n == 10)
		{
			cout << "����������������������·������Ϊ�� " << endl;
			reset(visit);
			Inorder_edge(dst,0,visit,place);
			cout << endl;	
		}
		else if(n == 11)
		{
			cout << "��������������ĺ������·������Ϊ�� " << endl;
			reset(visit);
			Postorder_edge(dst,0,visit,place);
			cout << endl;	
		}
		else if(n == 12)
		{
			cout << "����������������������·������Ϊ�� " << endl;
			reset(visit);
			Preorder_edge(bst,0,visit,place);
			cout << endl;
		}
		else if(n == 13)
		{
			cout << "����������������������·������Ϊ�� " << endl;
			reset(visit);
			Inorder_edge(bst,0,visit,place);
			cout << endl;	
		}
		else if(n == 14)
		{
			cout << "��������������ĺ������·������Ϊ�� " << endl;
			reset(visit);
			Postorder_edge(bst,0,visit,place);
			cout << endl;	
		}
		else if(n == 15)
		{
			tnode* root = new tnode;
			root->data = 0;
			root->brother = NULL;
			root->child = NULL;
			buildtree(dst , 0 , root);
			cout << "  �������������Ϊ�� " << endl;
			printtree( root ,place);
		} 
		else if(n == 16)
		{
			tnode* root = new tnode;
			root->data = 0;
			root->brother = NULL;
			root->child = NULL;
			buildtree(bst , 0 , root);
			cout << "  �������������Ϊ�� " << endl;
			printtree( root ,place);
		} 
		else if( n == 0) break;
		else
		{
			cout << "-----------�������� �� ���������� ��������������-------" << endl;
		}
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 1�� ���� 1  �����ȱ���ͼ�ĵص�����            -"<< endl;
		cout << "--- 2�� ���� 2  �����ȱ���ͼ�ĵص�����            -"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 3�� ���� 3  ������������������ǰ������ص�����-"<< endl;
		cout << "--- 4�� ���� 4  ��������������������������ص�����-"<< endl;
		cout << "--- 5�� ���� 4  �����������������ĺ�������ص�����-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 6�� ���� 6  ������������������ǰ������ص�����-"<< endl;
		cout << "--- 7�� ���� 7  ��������������������������ص�����-"<< endl;
		cout << "--- 8�� ���� 8  �����������������ĺ�������ص�����-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 9�� ���� 9  ������������������ǰ�����·������-"<< endl;
		cout << "--- 10������ 10 �������������������������·������-"<< endl;
		cout << "--- 11������ 11 �����������������ĺ������·������-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 12������ 12 ������������������ǰ�����·������-"<< endl;
		cout << "--- 13������ 13 �������������������������·������-"<< endl;
		cout << "--- 14������ 14 �����������������ĺ������·������-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 15������ 15 ��ӡ�������������                  -"<< endl;
		cout << "--- 16������ 16 ��ӡ�������������                  -"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 0������ 0 �˳�-----------------------------------"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << endl << "              ������Ҫʹ�õĹ��ܣ�      " ; 
	}
//	int i = 16;
//	p = g->adj[i].first;
//	while(p)
//	{
//		if(p->ve1 == i)
//		{
//			cout << p->ve1 <<" "<< p->ve2 << " " << p->weight<< endl;
//			p = p->path1;
//		}
//		else if(p->ve2 == i)
//		{
//			cout << p->ve1 <<" "<< p->ve2  <<" " << p->weight<< endl;
//			p = p->path2;
//		}
//	}

	
	return 0;
} 
