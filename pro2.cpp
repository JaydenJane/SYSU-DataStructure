#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

//���溯��
void printrule()
{
	cout << "  **************************************" << endl;
	cout << "  ********��ӭʹ���������ʽ������******" << endl;
	cout << "  **************************************" << endl << endl;
}

//�½�һ���ṹ�壬Ϊ�˷��㽫��ʽ�ֽ�֮����д洢 
struct Linkstring
{
	string data;
	struct Linkstring *next;
};

//��������������ʽ�ֽ⣬ÿһ���ִ洢������Ľڵ����ʽ 
Linkstring* transform(string str)
{
	Linkstring *first = new Linkstring;
	first -> next = NULL;
	Linkstring *p;
	p = first;
	for(int i = 0 ; i < str.length(); i++)
	{
		//Ϊ��������ʱ 
		if(str[i] == '(' || str[i] == ')' || str[i] == '+'  || str[i] == '-' || str[i] == '*' || str[i] == '/'|| str[i] == '#') 
		{
			//���нڵ�Ĳ��� 
			string tmp;
			tmp.push_back(str[i]);
			Linkstring *q = new Linkstring;
			q -> data = tmp; 
			q -> next = p -> next;
			p -> next = q ;
			p = q;
		} 
		//Ϊ����ʱ 
		else if(str[i] >= '0' && str[i] <= '9')
		{
			bool judge = false;
			string tmp;  
            while(str[i]>='0' && str[i]<='9')  
            {
                tmp.push_back(str[i]);  
                ++i;  
            }
            //С������� 
            if(str[i] == '.')  
            {  
            	judge = true;
                ++i;  
                if((str[i]>='0' && str[i]<='9'))  
                {  
                    tmp.push_back('.');  
                    while((str[i]>='0' && str[i]<='9') || str[i] == '^')  
                    {  
                        tmp.push_back(str[i]);  
                        ++i;  
                    }  
                    Linkstring *q = new Linkstring;
					q -> data = tmp; 
					q -> next = p -> next;
					p -> next = q ;
					p = q;
                }
                //��С�����û�����֣���ʽ�д��˽ڵ����FALSE�� 
				else    
                {  
                    Linkstring *q = new Linkstring;
					q -> data = "FALSE"; 
					q -> next = p -> next;
					p -> next = q ; 
					p = q;
                }    
			}
			//Ϊ�˷�ʱ 
			else if(str[i] == '^')
			{
				judge = true;
                ++i;  
                if(str[i]>='0' && str[i]<='9')  
                {  
                    tmp.push_back('^');  
                    while((str[i]>='0' && str[i]<='9') || str[i] == '.')  
                    {  
                        tmp.push_back(str[i]);  
                        ++i;  
                    }  
                    Linkstring *q = new Linkstring;
					q -> data = tmp; 
					q -> next = p -> next;
					p -> next = q ;
					p = q;
                }
                //�˷����ź���û�����֣���ʽ���󣬴���FALSE 
				else    
                {  
                    Linkstring *q = new Linkstring;
					q -> data = "FALSE"; 
					q -> next = p -> next;
					p -> next = q ; 
					p = q;
                }    
			}
			//�������ж�С���ͳ˷�ʱ�ѽ��нڵ�Ĳ��룬���Խ����жϴ����Ƿ�ΪС�����߳˷���������нڵ���� 
			if(judge == false)
			{
				Linkstring *q = new Linkstring;
				q -> data = tmp; 
				q -> next = p -> next;
				p -> next = q ;
				p = q;
			}
			i--;
		}
		//������Ϊ�������Ż���ĸ������FALSE 
		else    
        {  
            Linkstring *q = new Linkstring;
			q -> data = "FALSE"; 
			q -> next = p -> next;
			p -> next = q ; 
			p = q;
        } 
	} 
	return first;
}
// �쳣��Ķ���
class lstackexception
{
	public:
		lstackexception(const char* msg);
		const char* what() const;
	private:
		const char* message; 
}; 
lstackexception::lstackexception(const char* msg)
{
	message = msg;
}
const char* lstackexception::what() const
{
	return message;
}

// ��ջ�Ķ���
template <class DT>
class Lstack
{
	public:
		Lstack();
		~Lstack();
		void push(DT n);
		DT pop();
		DT gettop();
		void printf();
		bool empty();
	private:
		struct snode{
			DT data;
			struct snode *next;
		}; 
		snode *top;
};

template <class DT>
Lstack<DT>::Lstack()
{
	top = NULL;
}

template <class DT>
Lstack<DT>::~Lstack()
{
	while(top != NULL)
	{
		snode *tmp;
		tmp = top;
		top = top->next;
		delete tmp;
	} 
}

template <class DT>
void Lstack<DT>::push(DT n)
{
	snode *tmp ;
	tmp = new snode;
	tmp->data = n;
	tmp->next = top;
	top = tmp;
}

template <class DT>
DT Lstack<DT>::pop()
{
	if(top == NULL) 
	{
		throw lstackexception("Linkstack is empty!"); //�׳��쳣 
	}
	DT databox = top->data;
	snode *p = top;
	top = top->next;
	delete p;
	return databox;
}

template <class DT>
DT Lstack<DT>::gettop()
{
	if(top == NULL) 
	{
		throw lstackexception("Linkstack is empty!"); //�׳��쳣 
	}
	return top->data;
}

template <class DT>
void Lstack<DT>::printf()
{
	if(top == NULL) 
	{
		cout << setw(30) << setiosflags(ios::left) << "NULL" ;
	}
	else
	{
		string s;
		snode* p;
		p = top;
		while(p)
		{
			s =  p->data + " " +s ;
			p = p->next;			
		}
		cout << setw(30) << setiosflags(ios::left) << s ;
	}
}

template <class DT>
bool Lstack<DT>::empty()
{
	if(top == NULL)
	{
		return true;
	}
	return false;
}

//���ȼ������Ķ��� 
int priority(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == "(" || ch ==")") return 1;
	else if( ch == "*" || ch == "/") return 3;
	else if( ch == "+" || ch == "-") return 4;
	else return -2;
} 

//ջ�����ȼ���������
int priorityOUT(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == "(") return 8;
	else if (ch == ")") return 1;
	else if( ch == "*" || ch == "/") return 3;
	else if( ch == "+" || ch == "-") return 2;
	else return -2;
} 

 
//ջ�����ȼ������Ķ��� 
int priorityIN(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == ")") return 8;
	else if (ch == "(") return 1;
	else if( ch == "*" || ch == "/") return 5;
	else if( ch == "+" || ch == "-") return 3;
	else return -2;
} 

//�����쳣��������
bool correction(Linkstring* str)
{
	bool judge = true;
	int rcount = 0 , lcount = 0; //�����������������������Ƿ���� 
	Linkstring* pre = str->next;
	Linkstring* post ;
	cout << "----analysis:---" << endl;
	//�����ڷǷ��ַ������룬 �������� 
	while(pre)
	{
		cout << "    <" << pre->data <<"  , "<< priority(pre->data)<< ">"<< endl;
		if(pre->data == "FALSE")
		{
			 judge = false;
			 break;
		}
		pre = pre -> next;
	}
	cout << endl;
	if( judge == false) return judge;
	//�ж��Ƿ���������ʽ�Ĵ��� 
	pre = str->next;
	post = pre->next;
	//�ж��Ƿ���ڿ�ͷΪ�������� 
	if(priority(pre->data) != -2 && pre->data != "(")
	{
		return false;
	}
	while(post->next)
	{
		//��Ϊ������ʱ����ǰһλ������Ϊ�����ֺ�������֮��ģ� 
		if(post->data == ")")
		{
			rcount++;
			if(priority(pre->data) != -2)
			{
				if( pre->data != post->data)
				{
//				cout << "gg1" << endl;
					judge = false;
					break;
				}
			}
		}
		//��Ϊ������ʱ�����һλ������Ϊ�����ֺ�������֮��ģ�
		else if(pre->data == "(")
		{
			lcount++;
			if(priority(post->data) != -2)
			{
				if(post->data != pre->data)
				{
//					cout << "gg2" << endl;
					judge = false;
					break;
				}
			}
		}
		//�����������ݵ����ȼ�����ֵ֮��С��2 
		else if( abs( priority(post->data) - priority(pre->data) ) < 2)
		{
//			cout << "gg3" << endl;
			judge = false;
			break;
		}
		pre = post;
		post= post->next;
	}
	if (priority(pre->data) == 3 || priority(pre->data) == 4) judge = false;
	//������������������������� 
	if(rcount != lcount) judge = false;
	return judge;
} 

//ȥ���ַ����ո�ĺ���
string replace(string ls)
{
	string s;
	for(int i = 0 ; i < ls.length() ; i++)
	{
		if(ls[i] != ' ') s = s + ls[i];
	}
	return s;
} 

//ת�������ֺ���
long double transform_to_num(string s)
{
	int pos = s.find(".");
	int chengfang = s.find("^");
	long double sum = 0;
	//������ΪС��ʱ�� 
	if(pos != -1) 
	{
		//��û�г˷�ʱ 
		if(chengfang == -1)
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
		//�г˷� 
		else
		{
			if(pos < chengfang)
			{
				for(int i = 0; i < pos ; i++)
				{
					sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
				}
				for(int j = pos + 1; j < chengfang ; j++)
				{
					sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
				}
				long double jieshu = 0;
				for(int j = chengfang + 1; j < s.length() ; j++)
				{
					jieshu = jieshu + 1.0*pow(10,j-chengfang-1)*(s[j] - '0');
				}
				return pow(sum,jieshu);
			}
			else
			{
				for(int i = 0; i < chengfang ; i++)
				{
					sum = sum + 1.0*pow(10,chengfang-i-1)*(s[i] - '0');
				}
				long double jieshu = 0;
				for(int j = chengfang + 1; j < pos ; j++)
				{
					jieshu = jieshu + 1.0*pow(10,pos-j-1)*(s[j] - '0');
				}
				for(int j = pos+1 ; j < s.length() ; j++)
				{
					jieshu = jieshu + 1.0*pow(0.1,j-pos) *(s[j] - '0');
				}
				return pow(sum,jieshu);
			}
		}
	}
	//��ΪС��ʱ�� 
	else 
	{
		if(chengfang == -1)
		{
			for(int i = 0 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return sum;
		}
		else
		{
			for(int i = 0; i < chengfang ; i++)
			{
				sum = sum + 1.0*pow(10,chengfang-i-1)*(s[i] - '0');
			}
			long double jieshu = 0;
			for(int j = chengfang + 1; j < s.length() ; j++)
			{
				jieshu = jieshu + 1.0*pow(10,j-chengfang-1)*(s[j] - '0');
			}
			return pow(sum,jieshu);
		}
	}
} 


//���㺯�� 
long double calculate(long double num1_, string op , long double num2_)
{
	if(op == "+") return num1_ + num2_;
	else if(op == "-") return num1_ - num2_;
	else if(op == "*") return num1_ * num2_;
	else if(op == "/") return num1_ / num2_;
	else throw lstackexception("Does not conform to the rules of calculation��");
}

//�������к��� 
void run()
{
	//out��¼��������
	string str , op , out , stmp;
	stringstream ss;
	long double num1, num2 ,tmpnum;
	bool step = true;
	long double result;
	int process , len;
	while(1) 
	{ 	
		Lstack<long double> OPRD;       //����ջ 
		Lstack<string> OPTD , OR , OT;  // OPTD�������ջ ��OTģ�⵱ǰ�����ջ��ORģ�⵱ǰ����ջ  
		bool judge;
		if(step == false) 
		{
			cout << "    �����������ʽ��ʽ��������������: " << endl;
			step = true;
		}
		else cout << "   �������������ʽ��" << endl; 
		getline(cin,str,'\n');
		str = replace(str);       //ȥ�ո� 
		str = str + "#";          //��# 
		Linkstring* ls = transform(str);
		judge = correction(ls);
		//cout << judge << endl;
		if(judge == false)
		{
			step = false;
		}
		else 
		{
			process = 1;
			//��ʼ��ʽ��ӡ 
			cout << setw(30) << setiosflags(ios::left ) << "process"  ;
			cout << setw(30) << setiosflags(ios::left) << "operand stack" ;
			cout << setw(30) << setiosflags(ios::left) << "opertor stack" ;
			cout << setw(30) << setiosflags(ios::left) << "operation";
			cout << endl;
			cout << setw(30) << setiosflags(ios::left) << process ;
			cout << setw(30) << setiosflags(ios::left) << "NULL" ;
			cout << setw(30) << setiosflags(ios::left) << "NULL" ;
			cout << endl;
			OPTD.push("#");
			OT.push("#");
			Linkstring* p;
			p = ls->next;
			while(p)
			{
				if( priority(p->data) == -2) //�ò���Ϊ����ʱ 
				{
					tmpnum = transform_to_num(p->data);
					OPRD.push(tmpnum);
					result = tmpnum;
					process++;
					cout << setw(30) << setiosflags(ios::left) << process ; 
					OR.push(p->data);
					OR.printf();
					OT.printf();
					out = p->data + "��������ջ";
					cout << setw(30) << setiosflags(ios::left) << out;
					cout << endl;
					p = p->next;
					
				}
				else  //Ϊ������ʱ 
				{
					try{
						string tmp = OPTD.gettop();
						if(priorityOUT(p->data) >= priorityIN(tmp) ) // �ж����ȼ� 
						{
							process++;
							OPTD.push(p->data);
							cout << setw(30) << setiosflags(ios::left) << process ;
							OT.push(p->data);
							OR.printf();
							OT.printf();
							out = p->data + "���������ջ";
							cout << setw(30) << setiosflags(ios::left) << out;
							cout << endl;
						}
						else
						{
							if(p->data == ")")
							{
								while(tmp != "(")
								{
									num2 = OPRD.pop();
									num1 = OPRD.pop();
									op = OPTD.pop();
									result = calculate(num1,op,num2);
									OPRD.push(result);
									process++;
									OR.pop();
									OR.pop();
									OT.pop();
									ss << result; //��doubleת��Ϊstring�� 
									ss >> stmp;
									ss.clear();  // ��� 
									cout << setw(30) << setiosflags(ios::left) << process ;
									OR.printf();
									OT.printf();
									out = op + "��ջ����";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
									OR.push(stmp);
									op.clear();
									tmp = OPTD.gettop();
									process++;
									cout << setw(30) << setiosflags(ios::left) << process;
									OR.printf();
									OT.printf();
									out = "�ó������ջ";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
								}
								OPTD.pop();	
								OT.pop();
							} 
							else if(p->data != "#")
							{
								num2 = OPRD.pop();
								num1 = OPRD.pop();
								op = OPTD.pop();
								result = calculate(num1,op,num2);
								OPRD.push(result);
								OPTD.push(p->data);
								process++;
								OR.pop();
								OR.pop();
								OT.pop();
								ss << result;
								ss >> stmp;
								ss.clear();
								cout << setw(30) << setiosflags(ios::left) << process ;
								OR.printf();
								OT.printf();
								out = op + "��ջ����";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								OR.push(stmp);
								op.clear();
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OR.printf();
								OT.printf();
								out = "�ó������ջ";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OT.push(p->data);
								OR.printf();
								OT.printf();
								out = p->data + "���������ջ";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
							}
							else if(p->data == "#")
							{
								while(tmp!="#")
								{
									num2 = OPRD.pop();
									num1 = OPRD.pop();
									op = OPTD.pop();
									result = calculate(num1,op,num2);
									OPRD.push(result);
									ss << result;
									ss >> stmp;
									ss.clear();
									process++;
									OR.pop();
									OR.pop();
									OT.pop();
									cout << setw(30) << setiosflags(ios::left) << process ;
									OR.printf();
									OT.printf();
									out = op + "��ջ����";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
									OR.push(stmp);
									op.clear();
									tmp = OPTD.gettop();
								}
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OR.printf();
								OT.printf();
								out = "�ó������";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								OR.pop();
								op.clear();
							}
						}
						p = p->next;
					}
					catch(lstackexception ex)
					{
						cout << ex.what() << endl;
						break;
					}
				}
			}
			cout <<"   ������Ϊ��  " <<  result << endl << endl << endl;
			str.clear();		
		}
	}
}

int main()
{
	printrule();
	while(1)
	{
		run();
	}
	return 0;
}
