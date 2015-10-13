// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int _bitSize)
{
	bitSize = _bitSize;
	size = bitSize / (sizeof(TELEM)* 8) + 1;
	storage = new TELEM[size];
	for (int i = 0; i<size; i++)
		storage[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	size = bf.size;
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
	return(n / sizeof(TELEM)* 8);
}

TELEM TBitField::GetMemMask(const int n1) const // битовая маска для бита n
{
	int n = n1 % (sizeof(int)* 8);
	TELEM mask = 1 << n;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitSize;
}

void TBitField::SetBit(const int n) // установить бит
{
	int tmp=n;
	while((n<0)&&(n>size))
	{
		cout << "Input another number"<<endl;
		cin >> tmp;
	}
	storage[GetMemIndex(tmp)] |= GetMemMask(tmp);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int tmp=n;
	while((n<0)&&(n>size))
	{
		cout << "Input another number"<<endl;
		cin >> tmp;
	}
	storage[GetMemIndex(tmp)] &= ~(GetMemMask(tmp));
}

int TBitField::GetBit(const int n) const // получить значение бита
{

	int temp = storage[GetMemIndex(n)];
	temp &= GetMemMask(n);
	if (temp != 0)
		return 1;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	size = bf.size;
	storage = new TELEM[size];
	for (int i = 0; i<size; i++)
		storage[i] = bf.storage[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int tmp1 = 0, tmp2 = 0;
	for (int i = 0; i<size; i++)
		tmp1 = tmp1 + storage[i];
	for (int i = 0; i<bf.size; i++)
		tmp2 = tmp2 + bf.storage[i];
	if (tmp1 == tmp2)
		return 1;
	else
		return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int tmp1 = 0, tmp2 = 0;
	for (int i = 0; i<size; i++)
		tmp1 = tmp1 + storage[i];
	for (int i = 0; i<bf.size; i++)
		tmp2 = tmp2 + bf.storage[i];
	if (tmp1 != tmp2)
		return 1;
	else
		return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpsize = 0;
	int n = 0;
	if (size >= bf.size)
		tmpsize = size;
	else tmpsize = bf.bitSize;

	TBitField tmp(tmpsize);
	while ((size>tmp.size) && (bf.size>tmp.size))
	{
		tmp.storage[n] = storage[n] + bf.storage[n];
		n++;
	};
	if (tmp.size == size)
	for (int i = n; i<size; i++)
		tmp.storage[i] = storage[i];
	else
	for (int i = n; i<bf.size; i++)
		tmp.storage[i] = bf.storage[i];

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpsize=0;
	int n=0;
	if (size>=bf.size)
		tmpsize=size;
	else tmpsize=bf.bitSize;

	TBitField tmp(tmpsize);
	while ((size>tmp.size)&&(bf.size>tmp.size))
	{
		tmp.storage[n] = storage[n]-bf.storage[n];// Errors ?
		n++;
	};
	if (tmp.size==size)
		for (int i=n;i<size;i++)
			tmp.storage[i]=storage[i];
	else
		for (int i=n;i<bf.size;i++)
			tmp.storage[i]=bf.storage[i];
			
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
		bf.GetBit(i); istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitSize; i++)
	if (bf.GetBit(i)) ostr << 1;
	else ostr << 0;
	return ostr;
}
