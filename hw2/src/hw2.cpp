//41043257 惲子威 
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;
class Term
{
	friend Polynomial;
	friend ostream& operator<<(ostream&, const Polynomial&); // 宣告朋友類別 ostream
	friend istream& operator>>(istream&, Polynomial&);   // 宣告朋友類別 istream
private:
	float coef; // 係數 
	int exp; // 指數 
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
	Polynomial Polynomial_Add(Polynomial b); // 相加 
	Polynomial Polynomial_Mult(Polynomial b); // 相乘
	Polynomial Polynomial_Sub(Polynomial b); //減法 
	void NewTerm(const float theCoeff, const int theExp); // 建立新的項目
	float Eval(float f);
};

istream& operator>>(istream& input, Polynomial& poly)
{
	float coef;
	int exp;
	while (input.peek() != '\n') // 當使用者沒按下Enter時，則繼續輸入多
	{
		input >> coef;
		input.ignore(2);  // 為了忽略 x^這兩個符號  
		input >> exp;
		poly.NewTerm(coef, exp); // 呼叫NewTerm多項式成員函式  將輸入的係數和指數加入多項式中 
	}
	return input;
}
ostream& operator<<(ostream& output, const Polynomial& poly)
{
	int i;
	for (i = 0; i < poly.terms; i++)
	{
		if (poly.termArray[i].exp == 0)  //指數為0直接印出
		{
			output << showpos << poly.termArray[i].coef; // showpos印出正負號 
			continue;
		}
		output << showpos << poly.termArray[i].coef << "x^" << noshowpos << poly.termArray[i].exp;  // noshowpos 則不顯示正負號 
	}
	return output;
}
Polynomial::Polynomial() :capacity(2), terms(0) // 初始化 
{
	termArray = new Term[capacity]; // 建立一個 Term型別的陣列 
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) // 當項目數等於陣列空間時 
	{
		capacity *= 2; // 給兩倍的空間 
		Term* temp = new Term[capacity]; // 動態配置 新 
		copy(termArray, termArray + terms, temp); // 複製陣列 
		delete[]termArray; // 刪除原本空間 
		termArray = temp; // 將新陣列 指定給termArray 
	}
	// terms加 1 
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}
Polynomial Polynomial::Polynomial_Add(Polynomial b)
{
	Polynomial c; // 建立c這個多項式 用來存放 *this 和 b多項式相加的結果 
	int aPos = 0, bPos = 0;  //a和b多項式陣列的index 
	while ((aPos < terms) && (bPos < b.terms))
	{

		if (termArray[aPos].exp == b.termArray[bPos].exp) //判斷兩多項式目前的位置 指數是否相等 
		{
			float coefficient = termArray[aPos].coef + b.termArray[bPos].coef;
			if (coefficient) c.NewTerm(coefficient, termArray[aPos].exp); // 如果係數有值 則建立新的項目，把相加的係數和指數放進去	
			aPos++; bPos++; //將陣列位置 ++
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp)
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); // 因為b多項式的指數較大，所以將b多項式對應位置的係數和指數 放進C這個多項式 
			bPos++; // 然後將b陣列位置 +1 
		}
		else  // 因為a多項式的指數較大，所以將a多項式對應位置的係數和指數 放進C這個多項式 
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	
	for (; aPos < terms; aPos++) //將a多加進去c 
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++) //將b加進去c
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}


Polynomial Polynomial::Polynomial_Sub(Polynomial b) //減法 
{
	Polynomial c;
	int aPos = 0, bPos = 0;  
	while ((aPos < terms) && (bPos < b.terms))
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) // 如果a和b兩多項式 分別在兩個陣列的該位置指數相同 
		{
			float coefficient = termArray[aPos].coef - b.termArray[bPos].coef; // 則將a多項式的係數減掉b多項式的係數 傳給coefficient這個變數 
			if (coefficient) c.NewTerm(coefficient, termArray[aPos].exp);// 只要這個變數不等於零 則將呼叫NewTerm函式傳入(coefficient,a陣列該位置的指數)  
			aPos++; bPos++;  // a和b的index各別+1 
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) // 如果a多項式在陣列中該位置的指數 小於  b多項式在陣列中該位置的指數
		{
			c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp); // 將b多項式的係數乘以-1，然後和指數部分，透過NewTerm函式傳入c多項式中 
			bPos++;
		}
		else                                                 // 如果a多項式在陣列中該位置的指數 大於  b多項式在陣列中該位置的指數
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); // 將a多項式的係數和指數，透過NewTerm函式傳入c多項式中 
			aPos++;
		}
	}
	for (; aPos < terms; aPos++)  // 將剩下不是上述的狀況的係數和指數 加入c多項式中 
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}


Polynomial Polynomial::Polynomial_Mult(Polynomial b) //乘法  
{
	Polynomial c;
	for (int bPos = 0; bPos < terms; bPos++) // 用兩個for迴圈來掃 a和b多項式的內容 b多項式是第一層迴圈相乘時左邊去和右邊的一個一個做相乘 
	{
		Polynomial temp;  // 存放a和b多項式相乘後 還沒合併的結果。 
		for (int aPos = 0; aPos < terms; aPos++)
		{
			temp.NewTerm(termArray[aPos].coef * b.termArray[bPos].coef, termArray[aPos].exp + b.termArray[bPos].exp);
		}
		c = c.Polynomial_Add(temp); // 將每次相乘後的結果去做合併 所以呼叫多項式相加這個成員函式 
	}
	return c;
}

float Polynomial::Eval(float f)
{
	float result = 0; // 用來存放多項式x代值進來後的結果 
	
	for (int i = 0; i < terms; i++) // for迴圈去把對應位置的係數乘x的指數次方 再將result做相加。 
	{
		result += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return result;
}

int main()
{
	Polynomial a, b;  
	double x;  
	cout << "輸入第一行的係數和指數:" << endl;
	cin >> a; 
	cin.get(); 
	cout << "請入第二行的係數和指數:" << endl; cin >> b; 
	cout << "輸入x值:"; cin >> x; 
	
	cout <<endl<<"相加後:";
	cout << a.Polynomial_Add(b) << "    x代" << x << "->" << a.Polynomial_Add(b).Eval(x) << endl;
	cout << "相減後:";
	cout << a.Polynomial_Sub(b) << "    x代" << x << "->" << a.Polynomial_Sub(b).Eval(x) << endl;
	cout << "相乘後:";
	cout << a.Polynomial_Mult(b) <<"     x代" << x << "->" << a.Polynomial_Mult(b).Eval(x) << endl;
	return 0;
}
