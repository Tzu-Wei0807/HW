//41043257 惲子威 
#include<iostream>
#include<cmath>
#include<Windows.h>
using namespace std;

int count = 0;//次數

struct Term
{
	int coef =-1;
	int exp =-1 ;
	Term set(int c, int e)	//係數和指數次方
	{
		coef = c;
		exp = e;
		return *this;
	}	 
};

template<class T> 
class LinkList;

template<class T>
class LinkNode //ChainNode 
{
friend class LinkList<T>;
private:
	T data;
	LinkNode<T>* link;
public:
	LinkNode(const T& element = T(), LinkNode<T>* next = 0) {
		count += 2;
		data = element;
		link = next;
	}
};


template<class T>
class LinkList//Chain,circularlist
{
private:
	LinkNode<T>* first;
	LinkNode<T>* last;
public:
	LinkList()
	{
		count += 3;
		first = new LinkNode<T>;
		first -> link = first ;
		last = first;
	}
	~LinkList() //解構
	{
		count++;
		static LinkNode<T>* av;
		if (last)
		{
			count += 4;
			LinkNode<T>* first = last->link;
			last->link = av;
			av = first;
			last = 0;
		}
	}
	
	void InsertBack(const T& e)//插入串列後端
	{
		count++;
		if (first)
		{
			count += 3;
			last->link = new LinkNode<T>(e);	//last指向鏈結的最後一個節點
			last= last ->link;		
			last -> link = first;
		}
		else
		{
			count++;
			first = last = new LinkNode<T> (e);
		}
	}
	class iterator//指向串列鏈結的指標
	{
	public:
		iterator(LinkNode<T>* startNode = 0)//預設值，設定起始指標
		{
			count++;
			current = startNode;//初始化程式
		}
		/*兩種寫法*/
		T& operator*() const { 
			count++;  
			return current->data; 
		}
		T* operator->() const { 
			count++;
			return &current->data;
		}
		iterator& operator ++()//先存取再往下走
		{
			count++;
			current = current->link;
			return *this;
		}
		iterator operator ++(int)//先調指標，再取內容
		{
			count += 2;
			iterator old = *this;//old=取舊的指標
			current = current->link;//新的
			return *this;
		}

		/*檢查current屬性是否相等*/
		bool operator!=(const iterator right) const
		{
			count++;
			return current != right.current;
		}
		bool operator ==(const iterator right) const
		{
			count++;
			return current == right.current;
		}
	private:
		LinkNode<T>* current;
	};
	iterator begin() const { //回傳串列第一個節點
		count++;
		return iterator(first->link);
	} 
	iterator end() const { //回傳串列最後節點的後一個
		count++;
		return iterator(first);
	}
};


class Polynomial
{
private:
	LinkList<Term> poly;
public:
	Polynomial() {};
	Polynomial operator+(const Polynomial& b)
	{
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		count += 3;
		while (1)
		{
			count++;
			if (ai->exp == bi->exp) //a、b指數次方一樣
			{
				count++;
				if (ai->exp == -1)
				{
					count++;
					return c;
				}

				int sum = ai->coef + bi->coef; //相加a、b項目的係數
				count++;
				if (sum) {
					count += 3;
					c.poly.InsertBack(temp.set(sum, ai->exp));
					ai++; bi++; //ai、bi前進
				}
			}
			else if (ai->exp < bi->exp) //a次方<b次方
			{
				count += 2;
				c.poly.InsertBack(temp.set(bi->coef, bi->exp)); //複製b的項目並連接到 Polynomial物件c之後
				bi++;//bi前進
			}
			else //a次方>b次方
			{
				count += 2;
				c.poly.InsertBack(temp.set(ai->coef, ai->exp)); //複製a的項目並連接到 Polynomial物件c之後
				ai++; //ai前進
			}
		}
	}


	/* 住意負號的問題 */
	Polynomial operator-(const Polynomial& b)
	{	
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		count += 3;
		while (1)
		{
			count++;
			if (ai->exp == bi->exp)
			{
				count++;
				if (ai->exp == -1)
				{
					count++;
					return c;
				}
				count++;
				int sum = ai->coef - bi->coef; 
				if (sum) {
					count++;
					c.poly.InsertBack(temp.set(sum, ai->exp));
				}
				count++;
				ai++; bi++;
			}
			else if (ai->exp < bi->exp)
			{
				count+=2;
				c.poly.InsertBack(temp.set((-1)*(bi->coef), bi->exp));	//因為是相減，所以係數要乘上-1
				bi++;
			}
			else
			{
				count+=2;
				c.poly.InsertBack(temp.set(ai->coef, ai->exp));
				ai++;
			}
		}
	}


	Polynomial operator*(const Polynomial& b)
	{
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		count+=3;
		while (1)
		{
			count++;
			Polynomial c1; //c1 物件暫存相乘過後的結果
			if (ai->exp < 0)
			{
				count++;
				break;
			}
			while (1)
			{
				count+=2;
				c1.poly.InsertBack(temp.set( (ai->coef)*(bi->coef) , bi->exp+ai->exp));
				bi++;
				if (bi->exp < 0 ) 
				{
					count+=2;
					bi = b.poly.begin();
					c = c + c1; //再將暫存的結果利用多項式加法相加
					break;
				}
			}
			count++;
			ai++;
		}		
		return c;
	}
	friend istream& operator>>(istream& in, Polynomial& a);
	friend ostream& operator<<(ostream& ot, Polynomial& a);
	Polynomial(const Polynomial &a)
	{
		count++;
		poly = a.poly;
	}
	const Polynomial& operator=(const Polynomial& b) 
	{
		count++;
		this->poly = b.poly;

		return *this;
	}
	~Polynomial(){ }

	float Evaluate(float x) const		//代入X值計算
	{
		count+=2;
		LinkList<Term>::iterator ai = poly.begin();
		float sum = 0.0;

		while (1)
		{
			count++;
			if (ai->exp == -1)
			{
				count++;
				break;
			}
			count+=2;
			sum += (ai-> coef) * pow(x, ai -> exp);
			ai++;
		}
		return sum;
	}
};

istream& operator>>(istream& op_in, Polynomial& a)	//運算式多載輸入
{
	count++;
	Term temp;
	int n, c, e;
	count++;
	cout << "輸入項數:"<<endl;
	cin >> n;
	cout << "輸入係數及次方 " << endl;
	while (n)
	{
		count++;
		op_in >> c >> e;
		a.poly.InsertBack(temp.set(c, e));
		n--;
		count++;
	}
	return op_in;
	count++;
}

ostream& operator<<(ostream& op_out, Polynomial& a)//運算式多載輸出
{
	count++;
	LinkList<Term>::iterator ai = a.poly.begin();
	while (1)
	{
		count++;
		if (ai->exp == -1)
		{
			count++;
			return op_out;
		}
		if (ai->exp == 0)	//當輸出為X的0次方
		{
			count++;
			op_out << ai->coef;		//直接輸出X的0次方項的係數
		}
		else{
			count++;
			op_out << ai->coef << "X^" << ai->exp;
		}
		ai++;
		count++;
		if (ai->coef > 0 && ai-> exp != -1)		//判斷係數是否為負，若為負則不用輸出+
		{
			count++;
			op_out << "+";
		}	
	}
}

int main()
{
	LARGE_INTEGER start1, end1, start2, end2,fre,start3,end3,start4,end4;
	double times1, times2,times3,times4;

	Polynomial Polya,Polyb,Polyc,Polyd,Polye;

	cin >> Polya;
	cin >> Polyb;
	
	cout << "a=" << Polya << endl;
	cout << "b=" << Polyb << endl;

	QueryPerformanceFrequency(&fre);
	QueryPerformanceCounter(&start1);
	Polyc = Polya + Polyb;
	QueryPerformanceCounter(&end1);

	times1 = ((double)end1.QuadPart - (double)start1.QuadPart) / fre.QuadPart;

	cout << "a+b="<< Polyc;
	cout << endl;

	QueryPerformanceCounter(&start2);
	Polyd = Polya - Polyb;
	QueryPerformanceCounter(&end2);

	times2 = ((double)end2.QuadPart - (double)start2.QuadPart) / fre.QuadPart;

	cout << "a-b="<<Polyd;
	cout << endl;

	QueryPerformanceCounter(&start3);
	Polye = Polya * Polyb;
	QueryPerformanceCounter(&end3);
	times3 = ((double)end3.QuadPart - (double)start3.QuadPart) / fre.QuadPart;

	cout << "a*b="<<Polye;
	cout << endl;
	
	float x;
	cout << "輸入要代入的X值:" << endl;
	cin >> x;
	QueryPerformanceCounter(&start4);
	cout << "a=" << Polya.Evaluate(x);
	cout << endl;
	cout << "b=" << Polyb.Evaluate(x);
	cout << endl;
	cout << "a+b="<< Polyc.Evaluate(x);
	cout << endl;
	cout << "a-b="<< Polyd.Evaluate(x);
	cout << endl;
	cout << "a*b="<< Polye.Evaluate(x);
	cout << endl;
	QueryPerformanceCounter(&end4);

	times4 = ((double)end4.QuadPart - (double)start4.QuadPart) / fre.QuadPart;

	count += 11;

}
