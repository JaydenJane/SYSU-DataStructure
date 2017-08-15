#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

//һԪ����ʽ����Ķ��� 
struct poly
{
	double coef; // ϵ�� 
	int expon;  //  ָ�� 
	struct poly *next; 
};

//����ʽ�����Ĳ��� 
int length(poly *p)
{
	int length = 0;
	poly* re;
	re = p -> next;
	while(re != NULL)
	{
		re = re -> next;
		length ++ ;
	}
	return length;
} 

//ɾ��ֵΪ0�Ľڵ�
poly* delete0(poly* p)
{
	poly* pre;
	pre = p ;
	poly* box;
	while(pre -> next)
	{
		if(pre -> next -> coef == 0)
		{
			box = pre -> next;
			pre -> next = box -> next;
			delete(box);
		}
		else pre = pre -> next;
	}
	if(length(p) == 0) 
	{
		p = new poly;
		p -> coef = p -> expon = 0;
		p -> next = NULL;
		box = new poly;
		box -> coef = box -> expon = 0;
		box -> next = NULL;
		p -> next = box;
	} 
	return p; 
}

//һԪ����ʽ�Ĵ��� 
poly* createpoly(poly *p)
{
	// pre���Ա���ǰ�� , post���Ա����� 
	poly *re , *pre , *post;	
	// ����ʽ������ 
	int num;                   
	bool judge , in;
	// ����һ��ͷ��� 
	p = new poly;	           
	p -> next = NULL;	
	p -> coef = 0;	
	p -> expon = 0;
	in = false;
	while(in == false)
	{
		cout << "--��--��--��--��--��--ʽ--��--��--��--��" << endl;	
		cin >> num;
		if(num <= 0)
		{
			cout << "--��--��--��--��--��--��--��--��--��--��" << endl << endl; 
			in = false;
		} 
		else in = true;
	}
	int i = 1;
	while(num--)
	{
		// ����һ����� 
		re = new poly;	
		//�ж�������������Ƿ�����ָͬ����ָ�� 	
		judge = false;      
		cout << endl << "-----�������" << i << "��ϵ��-----��" << endl;		
		cin >> re -> coef;		
		cout << endl << "-----�������" << i << "��ָ��-----��" << endl;		
		cin >> re -> expon;
		//�����������ϵ��Ϊ0����ͳһΪָ��ҲΪ0��������кϲ������� 
		if( re -> coef == 0) re -> expon = 0;
		pre = p ; 
		post = p -> next;
		// Ϊ�˰��������� ,һֱ�ҵ���һ������������ָ��С���� 
		while(post && post -> expon >= re -> expon) 
		{
			// ��Ѱ�ҹ������ҵ�ָ����ͬ������кϲ�ͬ������� 
			if(post -> expon == re -> expon)
			{
				post -> coef = post -> coef + re -> coef;
				judge = true;
				break;
			}
			pre = post;
			post = post -> next;
		}
		//���н�����Ĺ��� 
		if( judge == false)
		{
			pre -> next = re;
			re -> next = post; 
		}
		i++;
	}
	p = delete0(p);
	return p;
}   

//����ʽ�Ĵ�ӡ��� 
void print(poly *p)
{
	poly *re = p -> next;
	int len = length(p) , count = 0;
	bool flag;
	cout << " ���� :" << len << endl; 
	while(re != NULL )
	{
		// ��ָ��Ϊ 0 ��������� 
		if(re -> expon == 0) 		 
		{
			
			cout << re -> coef ; 
		} 
		else                      
		{
			//�� ϵ��Ϊ1��������� 
			if(re -> coef == 1) 
			{
				if(re -> expon == 1) cout << "x" ;
				else cout << "x^" << re -> expon ;
			}
			//�� ϵ��Ϊ-1��������� 
			else if(re -> coef == -1) 
			{
				if(re -> expon == 1) cout << "-x" ;
				else cout << "-x^" << re -> expon ;
			}
			else 
			{
				//�� ָ��Ϊ1��������� 
				if(re -> expon == 1) cout << re -> coef << "x" ;
				else cout << re -> coef << "x^" << re -> expon ;
			}
		}
		count++ ;
		if( count < len )
		{
			cout << " + " ;
		} 
		else cout << endl;
		re = re -> next;
	} 
}

//����ʽ��� 
poly* add(poly* p1 , poly* p2)
{
	//ȷ��p1�����в�����ֻ���нڵ�ı�������p2�Ľڵ���б����Լ����������շ���p2 
	poly* re1 , *re2 , *pre ,*add;
	bool flag ;
	pre = p2;
	re1 = p1 -> next;
	while(re1)
	{
		//��һ���µ�ָ��add��ָ����ָ��NULL������ʱp1�е�һ���ڵ�����ݸ��Ƹ�add�� 
		add = new poly;
		add -> coef = re1 -> coef;
		add -> expon = re1 -> expon;
		add -> next = NULL;
		re2 = pre -> next;
		//flag ��������������ͬ�����ָ�� 
		flag = false;
		//����p2�ҵ���һ��ָ��С�ڵ���add��ָ������ 
		while( re2 && re2 -> expon >= add -> expon)
		{
			//�ҵ�ͬ���ֱ�ӶԴ�ʱ��������p2�Ľڵ��ֵ���и��ģ�flag=true���ͷ�add�Ŀռ� 
			if( re2 -> expon == add -> expon )
			{
				re2 -> coef = add -> coef + re2 -> coef;
				flag = true;
				delete(add);
			}
			pre = re2;
			re2 = re2 -> next;
		}
		//�����겢����ͬ��������нڵ�Ĳ��� 
		if(flag == false)
		{
			pre -> next = add;
			add -> next = re2; 
		}
		re1 = re1 -> next;
	}
	p2 = delete0(p2);
	return p2;
}

//����ʽ���� 
poly* sub(poly* p1 , poly* p2)
{
	//�����̶��������Ա�������������в��� 
	poly* re1 , *re2 , *pre ,*sub;
	bool flag ;
	pre = p1;
	re1 = p2 -> next;
	while(re1)
	{
		//��һ���µ�ָ��sub��ָ����ָ��NULL������ʱp1�е�һ���ڵ�����ݸ��Ƹ�sub�� 
		sub = new poly;
		sub -> coef = re1 -> coef;
		sub -> expon = re1 -> expon;
		sub -> next = NULL;
		re2 = pre -> next;
		//flag ��������������ͬ�����ָ�� 	
		flag = false;
		while( re2 && re2 -> expon >= sub -> expon)
		{
			//�ҵ�ͬ���ֱ�ӶԴ�ʱ��������p2�Ľڵ��ֵ���и��ģ�flag=true���ͷ�sub�Ŀռ� 
			if( re2 -> expon == sub -> expon )
			{
				re2 -> coef = re2 -> coef - sub -> coef;
				flag = true;
			}
			pre = re2;
			re2 = re2 -> next;
		}
		//��������ͬ������нڵ�Ĳ��룬��ʱ����Ľڵ��ϵ�����-1 
		if(flag == false)
		{
			sub -> coef = sub -> coef * (-1);
			pre -> next = sub;
			sub -> next = re2; 
		}
		re1 = re1 -> next;
	}
	p1 = delete0(p1);
	return p1;
}

//����ʽ��� 
poly* mul(poly* p1 , poly* p2)
{
	poly* re1 , *re2 ,*p3 ,*box;
	int exp ;
	double coe;
	if(length(p1) > length(p2))
	{
		p3 = p1;
		p1 = p2;
		p2 = p3;
	}
	re1 = p1 -> next;
	while(re1)
	{
		//ֱ��ʹ������������¼����һ������һ���ڵ�����ݣ�Ȼ���������һ���ڵ���в����� 
		exp = re1 -> expon;
		coe = re1 -> coef;
		re2 = p2 -> next;
		while(re2)
		{
			re2 -> coef = re2 -> coef * coe;
			re2 -> expon = re2 -> expon + exp;
			re2 = re2 -> next;
		}
		re1 = re1 -> next;
	}
	p2 = delete0(p2);
	return p2;
}

// ����ʽ��  
poly* deri(poly* p1)
{
	//��ʱ��ע�����������ָ��Ϊ0ʱ���󵼺�����Ϊ0�� 
	poly* re1 ;
	re1 = p1 -> next;
	while(re1)
	{
		if(re1 -> expon == 0)
		{
			re1 -> coef = 0;
		}
		else
		{
			re1 -> coef = re1 -> coef * re1 -> expon;
			re1 -> expon = re1 -> expon - 1 ;
		}
		re1 = re1 -> next ;
	}
	p1 = delete0(p1);
	return p1;
}

//������ж���ʽ���� 
double cal(poly* p , double x)
{
	poly* re ;
	double sum = 0;
	re = p -> next;
	double coe , expon;
	while(re)
	{
		coe = re -> coef;
		expon = re -> expon;
		sum = sum + coe*pow(x,expon);
		re = re -> next;
	}
	return sum;
}

//����ʹ�ù���Ĵ�ӡ
void printrule()
{
	cout << "- �� ӭ ʹ �� �� �� ʽ �� �� �� �� -" << endl << endl; 
	cout << "----------------------------------------------" << endl;
	cout << " �� �� ʽ �� �� �� �� �� �� �� �� Ϊ �� �� �� " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " һ �� �� ϵ �� �� �� �� �� һ �� �� ָ �� �� " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " �� �� �� һ �� �� �� ʽ ֮ �� �� �� ѡ �� �� " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " �� �� �� ʽ �� �� �� �� �� �� �� �� ˵ �� Ϊ " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 1���� �� + �� �� �� �� �� ʽ �� �� �� �� ��  " << endl;  
	cout << "----------------------------------------------" << endl;
	cout << " 2���� �� - �� �� �� �� �� ʽ �� �� �� �� ��  " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 3���� �� * �� �� �� �� �� ʽ �� �� �� �� ��  " << endl; 
	cout << "----------------------------------------------" << endl;
	cout << " 4���� �� d �� �� �� �� �� ʽ �� �� �� �� ��  "<< endl;
	cout << "----------------------------------------------" << endl;
	cout << " 5���� �� = �� �� �� �� �� �� ʽ �� �� �� �� ��"  << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 6���� �� c �� �� �� �� �� �� �� �� �� �룬�� ʼ �� "  << endl;
	cout << "----------------------------------------------" << endl << endl; 
}
 
int main()
{
	printrule();
	while(1)
	{ 
		poly *p1 , *p2 , *result;
		char ch;
		cout << endl << "--��--��--ʽ--��--��--��--:" << endl;
		p1 = createpoly(p1);
		result -> next = NULL;
		while(1)
		{
			cout << "--��--��--��--��--��--��--��--"<< endl;
			cin >> ch;
			if(result -> next != NULL) p1 = result;
			if( ch == '+') 
			{
				cout << endl << "--��--��--ʽ--��--��--��--:" << endl;
				p2 = createpoly(p2);
				cout << "--��--��--��--��--��--��--ʽ--��--��--Ϊ--:" << endl << endl;
				cout << "--��--��--ʽ--1-- ��";
				print(p1);
				cout << endl;
				cout << "--��--��--ʽ--2-- ��";
				print(p2);
				cout << endl;
				result = add(p1 , p2);
				cout << "-----��������ʽ��ӽ��Ϊ-----��"; 
				print(result);
				cout << endl;
			}
			else if(ch == '-')
			{
				cout << "--��--��--ʽ--��--��--��--:" << endl;
				p2 = createpoly(p2);
				cout << "--��--��--��--��--��--��--ʽ--��--��--Ϊ--:" << endl << endl;
				cout << "--��--��--ʽ--1-- ��";
				print(p1);
				cout << endl;
				cout << "--��--��--ʽ--2-- ��";
				print(p2);
				cout << endl;
				result = sub(p1 , p2);
				cout << "-----����ʽ1������ʽ2���Ϊ-----��"; 
				print(result);
				cout << endl;
			}
			else if(ch == '*')
			{
				cout << "--��--��--ʽ--��--��--��--:" << endl;
				p2 = createpoly(p2);
				cout << "--��--��--��--��--��--��--ʽ--��--��--Ϊ--:" << endl << endl;
				cout << "--��--��--ʽ--1-- ��";
				print(p1);
				cout << endl;
				cout << "--��--��--ʽ--2-- ��";
				print(p2);
				cout << endl;
				result = mul(p1,p2);
				cout << "-----��������ʽ��˽��Ϊ-----��";
				print(result);
				cout << endl;
			}
			else if(ch == 'd')
			{
				print(p1);
				result = deri(p1);
				cout << "--��--��--ʽ--��--��--��-- : ";
				print(result);
				cout << endl;
			}
			else if(ch == '=')
			{
				cout << endl << "--��--��--��--x--��--ֵ--" << endl ;
				double x;
				cin >> x;
				cout << "-----����x = " << x <<" ����Ľ��Ϊ-----:";
				cout << cal(p1,x) << endl << endl;;
			}
			else if(ch == 'c')
			{
				delete(p1);
				break;
			} 
		}
	}
	return 0;
}
 
