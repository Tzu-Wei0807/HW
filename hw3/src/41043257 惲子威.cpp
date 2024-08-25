//41043257 �@�l�� 
#include<iostream>
#include<cmath>
#include<Windows.h>
using namespace std;

int count = 0;//����

struct Term
{
	int coef =-1;
	int exp =-1 ;
	Term set(int c, int e)	//�Y�ƩM���Ʀ���
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
	~LinkList() //�Ѻc
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
	
	void InsertBack(const T& e)//���J��C���
	{
		count++;
		if (first)
		{
			count += 3;
			last->link = new LinkNode<T>(e);	//last���V�쵲���̫�@�Ӹ`�I
			last= last ->link;		
			last -> link = first;
		}
		else
		{
			count++;
			first = last = new LinkNode<T> (e);
		}
	}
	class iterator//���V��C�쵲������
	{
	public:
		iterator(LinkNode<T>* startNode = 0)//�w�]�ȡA�]�w�_�l����
		{
			count++;
			current = startNode;//��l�Ƶ{��
		}
		/*��ؼg�k*/
		T& operator*() const { 
			count++;  
			return current->data; 
		}
		T* operator->() const { 
			count++;
			return &current->data;
		}
		iterator& operator ++()//���s���A���U��
		{
			count++;
			current = current->link;
			return *this;
		}
		iterator operator ++(int)//���ի��СA�A�����e
		{
			count += 2;
			iterator old = *this;//old=���ª�����
			current = current->link;//�s��
			return *this;
		}

		/*�ˬdcurrent�ݩʬO�_�۵�*/
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
	iterator begin() const { //�^�Ǧ�C�Ĥ@�Ӹ`�I
		count++;
		return iterator(first->link);
	} 
	iterator end() const { //�^�Ǧ�C�̫�`�I����@��
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
			if (ai->exp == bi->exp) //a�Bb���Ʀ���@��
			{
				count++;
				if (ai->exp == -1)
				{
					count++;
					return c;
				}

				int sum = ai->coef + bi->coef; //�ۥ[a�Bb���ت��Y��
				count++;
				if (sum) {
					count += 3;
					c.poly.InsertBack(temp.set(sum, ai->exp));
					ai++; bi++; //ai�Bbi�e�i
				}
			}
			else if (ai->exp < bi->exp) //a����<b����
			{
				count += 2;
				c.poly.InsertBack(temp.set(bi->coef, bi->exp)); //�ƻsb�����بós���� Polynomial����c����
				bi++;//bi�e�i
			}
			else //a����>b����
			{
				count += 2;
				c.poly.InsertBack(temp.set(ai->coef, ai->exp)); //�ƻsa�����بós���� Polynomial����c����
				ai++; //ai�e�i
			}
		}
	}


	/* ��N�t�������D */
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
				c.poly.InsertBack(temp.set((-1)*(bi->coef), bi->exp));	//�]���O�۴�A�ҥH�Y�ƭn���W-1
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
			Polynomial c1; //c1 ����Ȧs�ۭ��L�᪺���G
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
					c = c + c1; //�A�N�Ȧs�����G�Q�Φh�����[�k�ۥ[
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

	float Evaluate(float x) const		//�N�JX�ȭp��
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

istream& operator>>(istream& op_in, Polynomial& a)	//�B�⦡�h����J
{
	count++;
	Term temp;
	int n, c, e;
	count++;
	cout << "��J����:"<<endl;
	cin >> n;
	cout << "��J�Y�ƤΦ��� " << endl;
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

ostream& operator<<(ostream& op_out, Polynomial& a)//�B�⦡�h����X
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
		if (ai->exp == 0)	//���X��X��0����
		{
			count++;
			op_out << ai->coef;		//������XX��0���趵���Y��
		}
		else{
			count++;
			op_out << ai->coef << "X^" << ai->exp;
		}
		ai++;
		count++;
		if (ai->coef > 0 && ai-> exp != -1)		//�P�_�Y�ƬO�_���t�A�Y���t�h���ο�X+
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
	cout << "��J�n�N�J��X��:" << endl;
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
