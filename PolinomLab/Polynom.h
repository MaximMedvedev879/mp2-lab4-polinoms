#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "List.h"
using namespace std;

class Monom
{
public:
	double coeff;
	unsigned int abc;
	Monom(double COEFF = 0, unsigned int ABC = 0);
	bool operator< (const Monom& m) const { return (abc < m.abc); }
	bool operator> (const Monom& m) const { return (abc > m.abc); }
	bool operator==(const Monom& m) const { return (abc == m.abc && coeff == m.coeff); }
	bool operator!=(const Monom& m) const { return !(*this == m); }
	Monom& operator=(const Monom& m) { coeff = m.coeff; abc = m.abc; return *this; }
};

class Polynom
{
protected:
	List<Monom> M1;
public:
	Polynom();
	Polynom(int n, const int m[][2]);
	Polynom(string S);
	Polynom(const Polynom& P) : M1(P.M1) {};  // конструктор копирования
	void Clean();
	Polynom operator+(const Monom& monom) const;
	Polynom operator+ (const Polynom& P) const;
	Polynom operator- (const Polynom& P) const { return (*this + P * (-1.0)); }
	Polynom operator* (const Polynom& P) const;
	Polynom operator* (const double c) const;
	Polynom operator* (const Monom& monom) const;
	bool operator== (const Polynom& POL) const { return M1 == POL.M1; }
	bool operator!= (const Polynom& POL) const { return M1 != POL.M1; }

	friend ostream& operator<< (ostream& os, const Polynom& P)
	{
		Polynom tmp = P;
		tmp.M1.Reset();
		tmp.M1.SetNext();
		Node<Monom>* First = tmp.M1.GetIT();
		Node<Monom>  Mon;
		while (!(tmp.M1.IsEnd()))
		{
			Mon = tmp.M1.GetIT()->data;
			if (Mon.data.coeff > 0 && tmp.M1.GetIT() != First) // вывод + между мономов
			{
				os << " + ";
			}
			if (Mon.data.coeff != 1 && Mon.data.coeff != -1 && Mon.data.coeff != 0) // вывод коэффицента
			{
				os << Mon.data.coeff; if (Mon.data.abc != 0) { cout << "*"; }
			}
			else
			{
				if (Mon.data.coeff == -1 && Mon.data.abc != 0) // вывод (-1)xyz
				{
					os << " - ";
				}
				else
				{
					if ((Mon.data.coeff == 1 || Mon.data.coeff == -1) && Mon.data.abc == 0) // вывод 1 и (-1)
					{
						os << Mon.data.coeff;
					}
				}
			}
			int f[3] = { 100,10,1 };
			char c[3] = { 'x','y','z' };
			for (int i = 0; i < 3; i++)
			{
				if (Mon.data.abc / f[i] % 10 != 0)
				{
					os << c[i];
					if (Mon.data.abc / f[i] % 10 != 1)
					{
						os << '^' << Mon.data.abc / f[i] % 10;
					}
				}
			}
			tmp.M1.SetNext();
		}
		tmp.M1.Reset();
		return os;
	}
	friend istream& operator>>(istream& in, Polynom& P)
	{ 
		string S;
		cout << "\t";
		in >> S;
		P = Polynom(S);
		return in;
	}
};

Monom::Monom(double COEFF, unsigned int ABC)
{
	if (ABC > 999) { throw 1; }
	coeff = COEFF;
	abc = ABC;
}

// Pелизации для полинома
Polynom::Polynom()
{ 
	Monom tmp;
	tmp.coeff = 0;
	tmp.abc = -1;
	M1.InsertToTail(tmp);
}
Polynom::Polynom(int n, const int M[][2])
{ 
	Monom tmp;
	tmp.coeff = 0;
	tmp.abc = -1;
	M1.InsertToTail(tmp);
	//прибавление остальных мономов
	for (int i = 0; i < n; i++)
	{
		if ((M[i][0] > 10) || (M[i][0] < 0)) { throw 1; }
		tmp.coeff = M[i][0];
		tmp.abc = M[i][1];
		*this = *this + tmp;
	}
}
Polynom::Polynom(string S)
{
	string M, P = S;
	int k = 1;
	int d[] = { 100, 10, 1 };
	char c[] = { 'x', 'y', 'z' };
	Monom tmp;
	Polynom P1;
	while (P.length())
	{
		k = 1;  tmp.abc = 0;  tmp.coeff = 0;
		while ((P[k] != '-') && (P[k] != '+') && (k < P.length()))
		{
			k++;
		}
		M = P.substr(0, k);
		P.erase(0, k);
		if (M[0] == '-')
		{
			tmp.coeff = -1;
			M.erase(0, 1);
		}
		else
		{
			tmp.coeff = 1;
			if (M[0] == '+')
			{
				M.erase(0, 1);
			}
		}
		if (isdigit(M[0])) //isdigit - если десятичное число
		{
			k = 0;
			while ((isdigit(M[k])) || (M[k] == '.'))
			{
				k++;
			}
			tmp.coeff *= std::stod(M.substr(0, k));
			M.erase(0, k);
		}
		for (int i = 0; i < 3; i++)
		{
			int pos = M.find(c[i]);
			if (pos != -1)
			{
				if (M[pos + 1] == '^')
				{
					tmp.abc = tmp.abc + d[i] * std::stoi(M.substr(pos + 2, 1));
				}
				else
				{
					tmp.abc += d[i];
				}
			}
		}
		P1 = P1 + tmp;
	}
	*this = P1;
}
void Polynom::Clean()
{
	M1.Clean();
	Monom tmp;
	tmp.coeff = 0;
	tmp.abc = -1;
	M1.InsertToTail(tmp);
}

Polynom Polynom::operator+(const Monom& MOL) const
{
	Polynom P1;
	Node <Monom>* T;
	int f = 0;
	P1.M1 = M1; 
	P1.M1.Reset();
	T = P1.M1.GetIT();
	P1.M1.SetNext(); 
	while (!P1.M1.IsEnd()) 
	{
		if (P1.M1.GetIT()->data.abc > MOL.abc) 
		{
			T = P1.M1.GetIT();
			P1.M1.SetNext();
		}
		else
		{
			if ((P1.M1.GetIT()->data.abc < MOL.abc)) 
			{
				if (MOL.coeff != 0)
				{
					P1.M1.InsertAfter(T, MOL);
					P1.M1.End();
					f = 1;
				}
			}
			else 
			{
				double cf = P1.M1.GetIT()->data.coeff + MOL.coeff;
				if (cf) 
				{
					P1.M1.GetIT()->data.coeff = cf;
					P1.M1.End();
					f = 1;
				}
				else
				{
					P1.M1.Delete(P1.M1.GetIT());
					P1.M1.End();
					f = 1;
				}
			}
		}
	}
	
	if ((f == 0) && (MOL.coeff != 0))
	{
		P1.M1.InsertAfter(T, MOL);
	}
	return P1;
}
Polynom Polynom::operator+(const Polynom& POL) const
{
	Polynom P1;
	P1.M1 = M1;
	List<Monom>  P2 = POL.M1;
	P2.Reset();
	P2.SetNext(); 

	while (!P2.IsEnd())
	{
		P1 = P1 + P2.GetIT()->data;
		P2.SetNext();
	}
	return P1;
}
Polynom Polynom::operator*(const double c) const
{
	Polynom res;
	if (c)
	{
		res = *this;
		res.M1.Reset();
		while (!(res.M1.IsEnd()))
		{
			res.M1.GetIT()->data.coeff *= c;
			res.M1.SetNext();
		}
	}
	else
	{
		res.M1.Clean();
	}
	return res;
}
Polynom Polynom::operator* (const Monom& MOL) const
{
	Polynom res;
	Polynom P1;
	Monom tmp;
	P1.M1 = M1;
	int a;
	double c;
	P1.M1.Reset();
	P1.M1.SetNext();
	while (!P1.M1.IsEnd())
	{
		a = P1.M1.GetIT()->data.abc;
		c = P1.M1.GetIT()->data.coeff;
		if ((MOL.abc % 10 + a % 10) < 10 && (MOL.abc / 10 % 10 + a / 10 % 10) < 10 && (MOL.abc / 100 + a / 100) < 10)
		{
			Monom tmp;
			tmp.coeff = MOL.coeff * c;
			tmp.abc = MOL.abc + a;
			res = res + tmp;
			P1.M1.SetNext();
		}
		else
		{
			throw 1;
		}
	}
	return res;
}
Polynom Polynom::operator*(const Polynom& POL) const
{
	Polynom P1, r;
	P1.M1 = M1;
	List<Monom>  P2 = POL.M1;
	P2.Reset();
	P2.SetNext(); 
	while (!P2.IsEnd())
	{
		r = r + P1 * P2.GetIT()->data;
		P2.SetNext();
	}
	return r;
}