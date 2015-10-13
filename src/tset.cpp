// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp = 100) : BitField(mp), MaxPower(mp){}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	BitField = bf;
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	TSet tmp;
	tmp.BitField = s.BitField;
	tmp.MaxPower = s.MaxPower;
	return tmp;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower==s.MaxPower)
		if (BitField==s.BitField)
			return 1;
		else
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower!=s.MaxPower)
		if (BitField!=s.BitField)
			return 1;
		else
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp(MaxPower);
	tmp = BitField | s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
/*	if (Elem>MaxPower)
	{
		TSet tmp(Elem);
		tmp.BitField.SetBit(Elem);
	return tmp;
	}
	else
		TSet tmp(MaxPower);
*/
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(*this);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp(MaxPower);
	tmp = BitField & s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator~(void) // дополнение
{
	TSet _s(MaxPower);
	_s.BitField=~BitField;
	return _s;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < s.MaxPower))
	{
		s.InsElem(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		 ostr << (s.BitField.GetBit(i));
	return ostr;
}
