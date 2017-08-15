#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

char invalid = '#';
char error = '@';

struct bnode
{
	string data;
	bnode* lchild ;
	bnode* rchild ;
};  

//ȥ���ո� 
string removeblank(string s)
{
	string str;
	for(int i = 0 ; i < s.length() ; i++)
	{
		if(s[i] == ' ' );
		else str = str + s[i]; 
	}
	return str;
}

//�ַ���ת���� 
long double transform(string s)
{
	int pos = s.find(".");
	long double sum = 0;
	if(s[0] != '-')
	{
		//������ΪС��ʱ�� 
		if(pos != -1) 
		{
			for(int i = 0; i < pos ; i++)
			{
				sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
			}
			for(int j = pos + 1; j < s.length() ; j++)
			{
				sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
			}
			return sum;
		}
		//��ΪС��ʱ�� 
		else 
		{
			for(int i = 0 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return sum;
		}
	}
	else
	{
		//������ΪС��ʱ�� 
		if(pos != -1) 
		{
			for(int i = 1; i < pos ; i++)
			{
				sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
			}
			for(int j = pos + 1; j < s.length() ; j++)
			{
				sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
			}
			return (-1.0)*sum;
		}
		//��ΪС��ʱ�� 
		else 
		{
			for(int i = 1 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return (-1.0)*sum;
		}
	}
} 

//���㺯�� 
long double cal(long double num1_ , char op , long double num2_)
{
	if(op == '+') return num1_ + num2_;
	else if(op == '-') return num1_ - num2_;
	else if(op == '*') return num1_ * num2_;
	else if(op == '/') return num1_ / num2_;
	else if(op == '^') return pow(num1_,num2_);
	
}

//���Ľ��� 
bnode* createtree(string s , int &pos)
{
	bnode* root = NULL;
	if(pos < s.length() && s[pos] != invalid)//����λ�ò�Ϊ��ʱ 
	{
		root = new bnode;
		root->data = s[pos];
		root->lchild = createtree(s , ++pos);
		root->rchild = createtree(s , ++pos);
	}
	return root;
}

//ǰ׺�Ķ�ȡ�͸��캯�� ����ΪҶ�ӽڵ�ض�Ϊ0-9����a-z,������ÿ��Ҷ�ӽڵ����λ�ü�����##��������ΪҶ�ӽڵ�  
string ReadExpr(string s)
{
	string str;
	for(int i = 0 ; i < s.length() ; i++)
	{
		if( (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z'))
		{
			str = str + s[i];
			str = str + invalid;
			str = str + invalid;
		}
		else 
		{
			if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
			{
				str = str + s[i];
			}
			else//�Ƿ��ַ��������ж� 
			{
				str = error + str;
				break;
			}
		}
	}
	return str;
}

//������׺ʽ���� 
void postorder(bnode* root , string &posexpr)
{
	bnode* p = root;
	if(p == NULL) return;
	else
	{
		postorder(p->lchild,posexpr);
		postorder(p->rchild,posexpr);
		posexpr = posexpr + p->data + " ";
	}
}

//�����׺ʽ���� 
void WriteExpr(string por, bool &flag)
{
	stack<string> op;
	string tmp; 
	for(int i = 0 ; i < por.length(); i++)
	{
		while(por[i] != ' ') //�ո���Ϊ���������� 12 �� 1 2 ������ 
		{
			tmp = tmp + por[i];
			i++;
		}
		if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^")
		{
			string opr1 , opr2 , exp;
			opr1 = op.top();
			op.pop();
			if(op.empty() == 1)//������������ 
			{
				op.push("false");
				break;
			}
			else
			{
				if(i == por.length()-1)
				{
					opr2 = op.top();
					op.pop();
					if(opr1 == "0" && tmp == "+")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "+")
					{
						exp = opr1;
					}
					else if(opr1 == "0" && tmp == "-")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "-")
					{
						exp = "-" + opr1;
					}
					else exp =  opr2 + tmp + opr1 ;
					op.push(exp);
				}
				else
				{
					opr2 = op.top();
					op.pop();
					if(opr1 == "0" && tmp == "+")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "+")
					{
						exp = opr1;
					}
					else if(opr1 == "0" && tmp == "-")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "-")
					{
						exp ="(-" + opr1 + ")";
					}
					else exp = "(" + opr2 + tmp + opr1 + ")";
					op.push(exp);
				}
			}
		}
		else 
		{
			op.push(tmp);
		}
		tmp.clear();
	}
	cout << op.top() << endl;
	if(op.top() == "false") flag = false;
}

//��ĳ�������и�ֵ���� 
void assign(bnode* root , string V , string value)
{
	bnode* tmp = root;
	queue<bnode*> q;
	q.push(tmp);
	while( !q.empty() ) // ��α������в��� 
	{
		bnode* top = q.front();
		if(top->data == V)
		{
			top->data = value;
		}
		q.pop();
		if(top->lchild != NULL) q.push(top->lchild);
		if(top->rchild != NULL) q.push(top->rchild);
	} 
}

//��ֵ���� 
void Value(string posexpr)
{
	stack<string> op;
	string tmp; 
	long double opra1 , opra2,re;
	stringstream ss;
	for(int i = 0 ; i < posexpr.length(); i++)
	{
		while(posexpr[i] != ' ') 
		{
			tmp = tmp + posexpr[i];
			i++;
		}
		if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^")
		{
			string opr1 , opr2 , exp;
			opr1 = op.top();
			op.pop();
			opra1 = transform(opr1);
			opr2 = op.top();
			op.pop();
			opra2 = transform(opr2);
			re = cal(opra2,tmp[0],opra1);
			ss << re;
			ss >> exp;
			op.push(exp);
			ss.clear();
		}
		else
		{
			if(tmp[0] >= 'a' && tmp[0] <= 'z')
			{
				op.push("0");
			}
			else op.push(tmp);
		}
		tmp.clear();
	}
	cout << op.top() << endl;	
}

//�������ʽ�ĸ��� 
bnode* CompoundExpr(char op , bnode* root1 , bnode* root2)
{
	bnode *newroot = new bnode;
	newroot->data = op;
	newroot->lchild = root1;
	newroot->rchild = root2;
	return newroot;
} 

//�ϲ�������� 
void MergeConst(bnode *root)
{
	bnode* tmp = root;
	long double a,b ,re;
	bool flag1 , flag2; // �ж��Ƿ���������˶�Ϊ���� 
	stringstream ss;
	string s;
	if(tmp == NULL) return ;
	else
	{	
		flag1 = true;	
		flag2 = true;	
		if((tmp->lchild->data == "+" || tmp->lchild->data == "-" || tmp->lchild->data == "*"|| tmp->lchild->data == "/"|| tmp->lchild->data == "^") && tmp->lchild->data.length()==1)
		{
			MergeConst(tmp->lchild); // �ǲ������������� 
            flag1 = false;
		}
		else flag1 = false;
		if( tmp->lchild->data[0] >= '0' && tmp->lchild->data[0] <= '9' || tmp->lchild->data.length() > 1) //�жϲ��������������֮���Ƿ�Ϊһ������ 
		{
			a = transform(tmp->lchild->data);
			flag1 = true;
		}
		if((tmp->rchild->data == "+" || tmp->rchild->data == "-" || tmp->rchild->data == "*"|| tmp->rchild->data == "/"|| tmp->rchild->data == "^") & tmp->rchild->data.length()==1)
		{
			MergeConst(tmp->rchild);
			flag2 = false;
		}
		else flag2 = false;
		if(tmp->rchild->data[0] >= '0' && tmp->rchild->data[0] <= '9' || tmp->rchild->data.length() > 1)
		{
			b = transform(tmp->rchild->data);
			flag2 = true;
		}
		if(flag1 == true && flag2 == true) //���Ҷ������֣����м��㲢���¸ýڵ㡣 
		{
			re = cal(a,tmp->data[0],b);
			ss << re;
			ss >> s;
			tmp->data = s;
			tmp->lchild = NULL;
			tmp->rchild = NULL;
		}
	}
}

//���������ƺ��� 
bnode* Copy(bnode* root)
{	
	bnode* first ;
	first = new bnode;
	queue<bnode*> qformer;
	queue<bnode*> qcopy;
	if(root != NULL)
	{
		first->data = root->data;
		first->lchild = NULL;
		first->rchild = NULL;
		qformer.push(root);
		qcopy.push(first);
	}
	while(!qformer.empty())
	{
		bnode* pf = qformer.front();
		bnode *pc = qcopy.front();
		if(pf->lchild != NULL)
		{
			bnode* temp ;
			temp = new bnode;
			temp -> data = pf->lchild->data;
			temp->lchild = NULL;
			temp->rchild = NULL;
			qformer.push(pf->lchild);
			qcopy.push(temp);
			pc->lchild = temp;
		}
		if(pf->rchild != NULL)
		{
			bnode* temp ;
			temp = new bnode;
			temp -> data = pf->rchild->data;
			temp->lchild = NULL;
			temp->rchild = NULL;
			qformer.push(pf->rchild);
			qcopy.push(temp);
			pc->rchild = temp;	
		}
		qformer.pop();
		qcopy.pop();
	}
	return first;
}

//�󵼺��� 
void Diff(bnode* root , string var)
{
	bnode* tmp = root;
	if( tmp->lchild == NULL && tmp->rchild == NULL) return; 
	else
	{
		if(tmp->data == "+" || tmp->data == "-")  // + , - �� 
		{
			if(tmp->lchild->data == var) tmp->lchild->data = "1";
			else
			{
				if(tmp->lchild->data == "+" || tmp->lchild->data == "-" || tmp->lchild->data == "*"|| tmp->lchild->data == "/"|| tmp->lchild->data == "^")
				{
					Diff(tmp->lchild,var);	
				}
				else
				{
					tmp->lchild->data = "0";
				}
			}
			if(tmp->rchild->data == var) tmp->rchild->data = "1";
			else
			{
				if(tmp->rchild->data == "+" || tmp->rchild->data == "-" || tmp->rchild->data == "*"|| tmp->rchild->data == "/"|| tmp->rchild->data == "^")
				{
					Diff(tmp->rchild,var);	
				}
				else
				{
					tmp->rchild->data = "0";
				}
			}
		}
		
		else if(tmp->data == "*")  // �˷��� �� ԭ�� ��ab��' = a'b + ab' ,���Խ����������Ľ��� 
		{
			bnode *newr , *newl , *pl , *pr;
			newl = Copy(tmp);
			newr = Copy(tmp);
			tmp->data = "+";
			tmp->lchild = newl;
			tmp->rchild = newr;
			pl = tmp->lchild; 
			pr = tmp->rchild;
			if(pl->lchild->data == var)
			{
				pl->lchild->data = "1"; 
			}
			else
			{
				if(pl->lchild->data == "+" || pl->lchild->data == "-" || pl->lchild->data == "*"|| pl->lchild->data == "/"|| pl->lchild->data == "^")
				{
					Diff(pl->lchild,var);
				}
				else
				{
					pl->lchild->data = "0";
					pl->data = "0";   // ֻҪ������Ϊ0������������Ϊʲô��ֵ��Ϊ0 
					pl->lchild = NULL;
					pl->rchild = NULL;
				}
			}
			if(pr->rchild->data == var)
			{
				pr->rchild->data = "1"; 
			}
			else
			{
				if(pr->rchild->data == "+" || pr->rchild->data == "-" || pr->rchild->data == "*"|| pr->rchild->data == "/"|| pr->rchild->data == "^")
				{
					Diff(pr->rchild,var);
				}
				else
				{
					pr->rchild->data = "0";
					pr->data = "0";
					pr->lchild = NULL;
					pr->rchild = NULL;
				}
			}
		}
		
		else if(tmp->data == "/") //������ԭ��, (a/b)'  =  (a'b - ab') / b*b ��Ҳ�ǽ����������Ľ��� 
		{
			bnode *newr , *newl , *newl_, *newr_ , *tmpnewl ,*tmpnewr, *pl ,*pr;
			newl = Copy(tmp);
			newr = Copy(tmp);
			newl->data = "*";
			newr->data = "*";
			newl_ = Copy(tmp->rchild);
			newr_ = Copy(tmp->rchild);
			
			tmpnewl = new bnode;
			tmpnewl->data = "-";
			tmpnewl->lchild = newl;
			tmpnewl->rchild = newr;
			tmp->lchild = tmpnewl;
			tmpnewr = new bnode;
			tmpnewr->data = "*";
			tmpnewr->lchild = newl_;
			tmpnewr->rchild = newr_;
			tmp->rchild = tmpnewr;
			
			pl = tmp->lchild->lchild;
			pr = tmp->lchild->rchild;
			if(pl->lchild->data == var)
			{
				pl->lchild->data = "1";
			}
			else
			{
				if(pl->lchild->data == "+" || pl->lchild->data == "-" || pl->lchild->data == "*"|| pl->lchild->data == "/"|| pl->lchild->data == "^")
				{
					Diff(pl->lchild,var);
				}
				else
				{
					pl->lchild->data = "0";
					pl->data = "0";
					pl->lchild = NULL;
					pl->rchild = NULL; 
				}
			}
			if(pr->rchild->data == var)
			{
				pr->rchild->data = "1"; 
			}
			else				
			{
				if(pr->rchild->data == "+" || pr->rchild->data == "-" || pr->rchild->data == "*"|| pr->rchild->data == "/"|| pr->rchild->data == "^")
				{
					Diff(pr->rchild,var);
				}
				else
				{
					pr->rchild->data = "0";
					pr->data = "0";
					pr->lchild = NULL;
					pr->rchild = NULL; 
				}
			}
		}
		
		else if(tmp->data == "^") // �˷���ԭ��a^n = n*a'*a^(n-1) ��Ҳ�ǽ����������Ľ��� 
		{
			bnode *newr , *newl , *pl , *pr;
			stringstream ss;
			string da;
			newl = Copy(tmp);
			newr = Copy(tmp);
			newl->data = "*";
			tmp->data = "*";
			tmp->lchild = newl;
			tmp->rchild = newr;
			long double d = transform(newr->rchild->data);
			d--;
			ss << d ;
			ss >> da ;
			newr->rchild->data = da;
			Diff(tmp->lchild,var);
		}		
	}
}


int main()
{
	string s , posexpr;
	bool flag , con;
	cout << "                       --------------------------"<< endl;
	cout << "                       -��ӭʹ��ǰ׺���ʽ������-"<< endl;
	cout << "                       --------------------------"<< endl;
	while(1)
	{
		posexpr.clear();
		flag = true;
		con = true;
		bnode* root;
		cout << "  ������ǰ׺���ʽ �� "<< endl;
		cin >> s;
		s = removeblank(s);
		string str = ReadExpr(s);
		if(str[0] == error)
		{
			cout << "���벻�Ϸ������������롣" << endl;
			con = false;
		}
		else
		{
			int pos = 0;
			root = createtree(str,pos); 		
			postorder(root , posexpr);
			cout << posexpr << endl;
			WriteExpr(posexpr,flag);
		}
		if(flag == false)
		{
			 con = false;
			 cout << " �Բ������������������������롣" << endl;
		}
		while(con)
		{
			cout << "  ������������еĲ��� ��" << endl;
			cout << "  --�Ա������и�ֵ����1��" << endl;
			cout << "  --�Ա��ʽ������ֵ������2��" << endl;
			cout << "  --�Ա��ʽ�������±��ʽ�ϲ�������3��" << endl;
			cout << "  --�Ա��ʽ����ƫ������������4��" << endl;
			cout << "  --�Ա��ʽ���кϲ�������������5��" << endl;
			cout << "  --�˳��밴��1,2,3,4,5�������" << endl;
			char n;
			cin >> n;
			if(n == '1')
			{
				cout << "������Ҫ�����ı���:" << endl;
				string var;
				cin >> var;
				cout << "������Ҫ�����ֵ:"  << endl;
				string value;
				cin >> value;
				assign(root,var,value);
				cout << "���ʽ��Ϊ��"  << endl;
				posexpr.clear();
				postorder(root,posexpr);
				WriteExpr(posexpr,flag);
			}
			else if(n == '2')
			{
				cout << "�����ֵΪ��" << endl;
				Value(posexpr);
			}	
			else if(n == '3')
			{
				cout << " --�������µ�ǰ׺���ʽ��" << endl;
				string snew , posexprnew;
				bool flagnew = true , connew = true;
				cin >> snew;
				snew = removeblank(snew);
				snew = ReadExpr(snew);
				int posnew = 0;
				bnode* rootnew = createtree(snew,posnew); 		
				postorder(rootnew , posexprnew);
				WriteExpr(posexprnew,flagnew);
				if(flagnew == false)
				{
					 connew = false;
					 cout << " �Բ����������������޷����㡣" << endl;
				}
				if(connew)
				{
					cout << "�����������������ʽ�Ĳ�������+,-,*,/,^��" << endl; 
					char op;
					cin >> op;
					root = CompoundExpr(op,root,rootnew);
					MergeConst(root);
					cout << "���ʽ��Ϊ��"  << endl;
					posexpr.clear();
					postorder(root,posexpr);
					WriteExpr(posexpr,flag);
				}
			}
			else if(n == '4')
			{
				cout << "������Ҫ��΢�ֵı�����" << endl;
				string var;
				cin >> var;
				MergeConst(root);
				Diff(root,var);
				MergeConst(root);
				posexpr.clear();
				postorder(root,posexpr);
				cout << "΢�ֺ�ı��ʽΪ�� " << endl; 
				WriteExpr(posexpr,flag);
				
			} 
			else if(n == '5')
			{
				MergeConst(root);
				cout << "���ʽ��Ϊ�� " << endl; 
				posexpr.clear();
				postorder(root,posexpr);
				WriteExpr(posexpr,flag);
			}
			else break;
		}
	}
	return 0;
}
