#pragma once
#include<iostream>
using namespace std;
template<class T>
class Array_Queue
{
	T* array;
	int* freq;
	int size;

public:
	Array_Queue();
	~Array_Queue();
	void EnQueue(T input, int frequency);
	int DeQueue();
	void SortAccordingToFrequency();
	int QueueSize();
};

template<class T>
inline Array_Queue<T>::Array_Queue()
{
	array = nullptr;
	freq = nullptr;
	size = 1;
}

template<class T>
inline Array_Queue<T>::~Array_Queue()
{
	if (array)
		delete[]array;
	if (freq)
		delete[]freq;
}

template<class T>
inline void Array_Queue<T>::EnQueue(T input, int frequency)
{

	if (!array)
	{
		array = new T[size];
		freq = new int[size];
		array[0] = input;
		freq[0] = frequency;
	}
	else
	{
		T* temp_array = new T[size];
		int* temp_freq = new int[size];
		for (int i = 0; i < size; i++)
		{
			temp_array[i] = array[i];
			temp_freq[i] = freq[i];
		}
		delete[]array;
		delete[]freq;
		size++;
		array = new T[size];
		freq = new int[size];
		for (int i = 0; i < size - 1; i++)
		{
			array[i] = temp_array[i];
			freq[i] = temp_freq[i];
		}
		array[size - 1] = input;
		freq[size - 1] = frequency;
		delete[]temp_array;
		delete[]temp_freq;
	}
}

template<class T>
inline int Array_Queue<T>::DeQueue()
{
	if (size >= 1)
	{
		size -= 1;
		return array[size];
	}
	else
	{
		return NULL;
	}
}

template<class T>
inline void Array_Queue<T>::SortAccordingToFrequency()
{
	if (freq)
	{
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (freq[i] < freq[j])
				{
					int temp = freq[i];
					freq[i] = freq[j];
					freq[j] = temp;
					temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
	}
}

template<class T>
inline int Array_Queue<T>::QueueSize()
{
	return size;
}
