//41043257 �@�l�� Ackermann Function
#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;
int A_r(int m,int n)//���j 
{
	if(m==0){return n+1;}
	else if(n==0){return A_r(m-1,1);}
	else{return A_r(m-1,A_r(m,n-1));}
		
}

int A_nr(int m,int n)//�D���j 
{
    stack<int> s;      //name s stack 
    s.push(m);         //push m
    while (!s.empty()) //���Oempty�~�� 
    {
    	m=s.top();
    	s.pop();
    	
    	if(m==0){n++;      //n+1
		}
		else if(n==0)      //A(m-1,1)
		{
			s.push(m-1);
			n=1;
		}
		else               //A(m-1,A(m,n-1))
		{
			s.push(m-1);
			s.push(m);
			n--;
		}
	
    }
    return n;
}


int main()
{
    int a,b,m,n,status;     //a=Recursive answer, b= Nonrecursive answer, m=m, n=n
    while(cin>>m>>n)//��J��Ӽ�
	{      
	a = A_r(m,n);
	b = A_nr(m,n);   
	cout<<"recursive "<<a<<endl; //output answer
	cout<<"non recursive "<<b<<endl;
	} 
	return 0;	
 } 
