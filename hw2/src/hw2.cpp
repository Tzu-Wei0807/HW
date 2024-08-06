//41043257 �@�l�� 
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;
class Term
{
	friend Polynomial;
	friend ostream& operator<<(ostream&, const Polynomial&); // �ŧi�B�����O ostream
	friend istream& operator>>(istream&, Polynomial&);   // �ŧi�B�����O istream
private:
	float coef; // �Y�� 
	int exp; // ���� 
};


class Polynomial
{
	friend ostream& operator<<(ostream&, const Polynomial&); 
	friend istream& operator>>(istream&, Polynomial&); 
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial();
	Polynomial Polynomial_Add(Polynomial b); // �ۥ[ 
	Polynomial Polynomial_Mult(Polynomial b); // �ۭ�
	Polynomial Polynomial_Sub(Polynomial b); //��k 
	void NewTerm(const float theCoeff, const int theExp); // �إ߷s������
	float Eval(float f);
};

istream& operator>>(istream& input, Polynomial& poly)
{
	float coef;
	int exp;
	while (input.peek() != '\n') // ��ϥΪ̨S���UEnter�ɡA�h�~���J�h
	{
		input >> coef;
		input.ignore(2);  // ���F���� x^�o��ӲŸ�  
		input >> exp;
		poly.NewTerm(coef, exp); // �I�sNewTerm�h���������禡  �N��J���Y�ƩM���ƥ[�J�h������ 
	}
	return input;
}
ostream& operator<<(ostream& output, const Polynomial& poly)
{
	int i;
	for (i = 0; i < poly.terms; i++)
	{
		if (poly.termArray[i].exp == 0)  //���Ƭ�0�����L�X
		{
			output << showpos << poly.termArray[i].coef; // showpos�L�X���t�� 
			continue;
		}
		output << showpos << poly.termArray[i].coef << "x^" << noshowpos << poly.termArray[i].exp;  // noshowpos �h����ܥ��t�� 
	}
	return output;
}
Polynomial::Polynomial() :capacity(2), terms(0) // ��l�� 
{
	termArray = new Term[capacity]; // �إߤ@�� Term���O���}�C 
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) // ���ؼƵ���}�C�Ŷ��� 
	{
		capacity *= 2; // ���⭿���Ŷ� 
		Term* temp = new Term[capacity]; // �ʺA�t�m �s 
		copy(termArray, termArray + terms, temp); // �ƻs�}�C 
		delete[]termArray; // �R���쥻�Ŷ� 
		termArray = temp; // �N�s�}�C ���w��termArray 
	}
	// terms�[ 1 
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}
Polynomial Polynomial::Polynomial_Add(Polynomial b)
{
	Polynomial c; // �إ�c�o�Ӧh���� �ΨӦs�� *this �M b�h�����ۥ[�����G 
	int aPos = 0, bPos = 0;  //a�Mb�h�����}�C��index 
	while ((aPos < terms) && (bPos < b.terms))
	{

		if (termArray[aPos].exp == b.termArray[bPos].exp) //�P�_��h�����ثe����m ���ƬO�_�۵� 
		{
			float coefficient = termArray[aPos].coef + b.termArray[bPos].coef;
			if (coefficient) c.NewTerm(coefficient, termArray[aPos].exp); // �p�G�Y�Ʀ��� �h�إ߷s�����ءA��ۥ[���Y�ƩM���Ʃ�i�h	
			aPos++; bPos++; //�N�}�C��m ++
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp)
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); // �]��b�h���������Ƹ��j�A�ҥH�Nb�h����������m���Y�ƩM���� ��iC�o�Ӧh���� 
			bPos++; // �M��Nb�}�C��m +1 
		}
		else  // �]��a�h���������Ƹ��j�A�ҥH�Na�h����������m���Y�ƩM���� ��iC�o�Ӧh���� 
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	
	for (; aPos < terms; aPos++) //�Na�h�[�i�hc 
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++) //�Nb�[�i�hc
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}


Polynomial Polynomial::Polynomial_Sub(Polynomial b) //��k 
{
	Polynomial c;
	int aPos = 0, bPos = 0;  
	while ((aPos < terms) && (bPos < b.terms))
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) // �p�Ga�Mb��h���� ���O�b��Ӱ}�C���Ӧ�m���ƬۦP 
		{
			float coefficient = termArray[aPos].coef - b.termArray[bPos].coef; // �h�Na�h�������Y�ƴb�h�������Y�� �ǵ�coefficient�o���ܼ� 
			if (coefficient) c.NewTerm(coefficient, termArray[aPos].exp);// �u�n�o���ܼƤ�����s �h�N�I�sNewTerm�禡�ǤJ(coefficient,a�}�C�Ӧ�m������)  
			aPos++; bPos++;  // a�Mb��index�U�O+1 
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) // �p�Ga�h�����b�}�C���Ӧ�m������ �p��  b�h�����b�}�C���Ӧ�m������
		{
			c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp); // �Nb�h�������Y�ƭ��H-1�A�M��M���Ƴ����A�z�LNewTerm�禡�ǤJc�h������ 
			bPos++;
		}
		else                                                 // �p�Ga�h�����b�}�C���Ӧ�m������ �j��  b�h�����b�}�C���Ӧ�m������
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); // �Na�h�������Y�ƩM���ơA�z�LNewTerm�禡�ǤJc�h������ 
			aPos++;
		}
	}
	for (; aPos < terms; aPos++)  // �N�ѤU���O�W�z�����p���Y�ƩM���� �[�Jc�h������ 
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}


Polynomial Polynomial::Polynomial_Mult(Polynomial b) //���k  
{
	Polynomial c;
	for (int bPos = 0; bPos < terms; bPos++) // �Ψ��for�j��ӱ� a�Mb�h���������e b�h�����O�Ĥ@�h�j��ۭ��ɥ���h�M�k�䪺�@�Ӥ@�Ӱ��ۭ� 
	{
		Polynomial temp;  // �s��a�Mb�h�����ۭ��� �٨S�X�֪����G�C 
		for (int aPos = 0; aPos < terms; aPos++)
		{
			temp.NewTerm(termArray[aPos].coef * b.termArray[bPos].coef, termArray[aPos].exp + b.termArray[bPos].exp);
		}
		c = c.Polynomial_Add(temp); // �N�C���ۭ��᪺���G�h���X�� �ҥH�I�s�h�����ۥ[�o�Ӧ����禡 
	}
	return c;
}

float Polynomial::Eval(float f)
{
	float result = 0; // �ΨӦs��h����x�N�ȶi�ӫ᪺���G 
	
	for (int i = 0; i < terms; i++) // for�j��h�������m���Y�ƭ�x�����Ʀ��� �A�Nresult���ۥ[�C 
	{
		result += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return result;
}

int main()
{
	Polynomial a, b;  
	double x;  
	cout << "��J�Ĥ@�檺�Y�ƩM����:" << endl;
	cin >> a; 
	cin.get(); 
	cout << "�ФJ�ĤG�檺�Y�ƩM����:" << endl; cin >> b; 
	cout << "��Jx��:"; cin >> x; 
	
	cout <<endl<<"�ۥ[��:";
	cout << a.Polynomial_Add(b) << "    x�N" << x << "->" << a.Polynomial_Add(b).Eval(x) << endl;
	cout << "�۴��:";
	cout << a.Polynomial_Sub(b) << "    x�N" << x << "->" << a.Polynomial_Sub(b).Eval(x) << endl;
	cout << "�ۭ���:";
	cout << a.Polynomial_Mult(b) <<"     x�N" << x << "->" << a.Polynomial_Mult(b).Eval(x) << endl;
	return 0;
}
