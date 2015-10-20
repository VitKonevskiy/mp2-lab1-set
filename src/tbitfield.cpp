// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
//

//

TBitField::TBitField(int _bitSize)
{
	if (_bitSize < 0)
		throw _bitSize;
	else
	{
		bitSize = _bitSize;
		size = bitSize / (sizeof(TELEM)* 8) + 1;
		storage = new TELEM[size];
		for (int i = 0; i < size; i++)
			storage[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	size = bf.size;
	bitSize = bf.bitSize;
	storage = new TELEM[size];
	for (int i = 0; i<size; i++)
		storage[i] = bf.storage[i];
}

TBitField::~TBitField()
{
	delete[]storage;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n<0)
		throw n;
	else
	return(n / (sizeof(TELEM)* 8));
}

TELEM TBitField::GetMemMask(const int n1) const // битовая маска для бита n
{
	if (n1<0)
		throw n1;
	else
	{
		int n = n1 % (sizeof(int)* 8);
		TELEM mask = 1<<n;
		return mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitSize;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0)||(n>bitSize))
		throw n;
	else
	{
		int tmp=n;
		storage[GetMemIndex(tmp)] = storage[GetMemIndex(tmp)] | GetMemMask(tmp);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int tmp=n;
	if ((n<0)||(n>bitSize))
		throw n;
	else
	{
		storage[GetMemIndex(tmp)] &= ~(GetMemMask(tmp));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0)||(n>bitSize))
		throw n;
	else
	{
		int temp = storage[GetMemIndex(n)];
		temp &= GetMemMask(n);
		if (temp != 0)
			return 1;
		else return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	size = bf.size;
	bitSize = bf.bitSize;
	storage = new TELEM[size];
	for (int i = 0; i<size; i++)
		storage[i] = bf.storage[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i=0;i<bitSize;i++)
	{	
		if (GetBit(i)!=bf.GetBit(i))
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int n = 0;
	for (int i=0;i<bitSize;i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			n = 1;
	}
	return n;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpsize = 0;
	int n = 0;
	if (bitSize >= bf.bitSize)
	{
		tmpsize = bitSize;
		n = bf.bitSize;
	}	
	else
	{
		tmpsize = bf.bitSize;
		n = bitSize;
	}
	TBitField tmp(tmpsize);
	if (tmpsize == bitSize)
		tmp = *this;
	else tmp = bf;

	for (int i = 0; i < n;i++)
	if ((GetBit(i) || bf.GetBit(i)))
		tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpsize = 0;
	int n = 0;
	if (bitSize >= bf.bitSize)
	{
		tmpsize = bitSize;
		n = bf.bitSize;
	}

	else
	{
		tmpsize = bf.bitSize;
		n = bitSize;
	}

	TBitField tmp(tmpsize);
	for (int i = 0; i < n;i++)
	if (GetBit(i) && bf.GetBit(i))
		tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(bitSize);
	for (int i=0;i<size;i++)
		tmp.storage[i]=~storage[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.bitSize))
	{
		bf.SetBit(i); 
		istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitSize; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
