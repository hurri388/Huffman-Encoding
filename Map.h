#pragma once
#include<string>
using namespace std;
template<class T,class U>
class map {
	T* type1;
	U* type2;
	int size;
public:
	map();
	~map();
	void insert(T, U);
	T getFirst(int index);
	U getSecond(int index);
	int Size();
};

template<class T, class U>
inline map<T, U>::map()
{
	type1 = nullptr;
	type2 = nullptr;
	size = 1;
}

template<class T, class U>
inline map<T, U>::~map()
{
	if (type1)
		delete[]type1;
	if (type2)
		delete[]type2;
}

template<class T, class U>
inline void map<T, U>::insert(T input1, U input2)
{
	if (!type1)
	{
		type1 = new T[size];
		type2 = new U[size];
		type1[0] = input1;
		type2[0] = input2;
	}
	else
	{
		T* temp_array1 = new T[size];
		U* temp_array2 = new U[size];
		for (int i = 0; i < size; i++)
		{
			temp_array1[i] = type1[i];
			temp_array2[i] = type2[i];
		}
		delete[]type1;
		delete[]type2;
		size++;
		type1 = new T[size];
		type2 = new U[size];
		for (int i = 0; i < size - 1; i++)
		{
			type1[i] = temp_array1[i];
			type2[i] = temp_array2[i];
		}
		type1[size - 1] = input1;
		type2[size - 1] = input2;
		delete[]temp_array1;
		delete[]temp_array2;
	}
}

template<class T, class U>
inline T map<T, U>::getFirst(int index)
{
	if (index < size)
		return type1[index];
}

template<class T, class U>
inline U map<T, U>::getSecond(int index)
{
	if (index < size)
		return type2[index];
}

template<class T, class U>
inline int map<T, U>::Size()
{
	return size;
}
