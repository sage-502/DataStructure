#pragma once
#include<iostream>
using namespace std;

template<class Type>
class MaxHeap {
private:
	Type* array = nullptr;
	int capacity = 0;
	int size = 0;

	void extend() {
		capacity *= 2;
		Type* temp = new Type[capacity + 1];
		for (int i = 1; i <= size; i++) temp[i] = array[i];
		delete[] array;
		array = temp;
	}
public:
	MaxHeap(int c = 10) {
		capacity = c;
		array = new Type[capacity + 1];
	}
	~MaxHeap() {
		delete[] array;
	}

	void insert(Type const& value){
		if (size == capacity) extend();
		int i = ++size;
		while (i>1 && array[i/2]<value) {
			array[i] = array[i / 2];
			i /= 2;
		}
		array[i] = value;
	}

	Type pop() {
		if (size == 0) throw underflow_error("empty heap\n");
		Type root = array[1];

		int i = 1;
		array[i] = array[size--];
		while (i*2<=size) {
			int child = i * 2;
			if (child + 1 <= size && array[child + 1] > array[child]) 
				child++;
			if (array[i] < array[child]) {
				Type temp = array[i];
				array[i] = array[child];
				array[child] = temp;
				i = child;
			}
			else break;
		}

		return root;
	}

	void showBFS() {
		cout << "elements: ";
		for (int i = 1; i <= size; i++) cout << array[i] << " ";
		cout << endl;
	}
};
