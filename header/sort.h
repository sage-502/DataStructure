#pragma once
#include <iostream>
using namespace std;

template<class Type>
class Hsort {
private:
	void HeapPath(Type* arr, int size, int j) {
		while (j * 2 <= size) {
			int child = j * 2;
			if (child + 1 <= size && arr[child + 1] > arr[child])
				child++;

			if (arr[j] < arr[child]) {
				Type temp = arr[j];
				arr[j] = arr[child];
				arr[child] = temp;
				j = child;
			}
			else break;
		}
	}

	void makeMaxHeap(Type* arr, int size) {
		for (int i = size / 2; i > 0; i--) {
			HeapPath(arr, size, i);
		}
	}

	void popMaxHeap(Type* arr, int size) {
		Type temp = arr[1];
		arr[1] = arr[size];
		arr[size] = temp;
		HeapPath(arr, size - 1, 1);
	}

public:
	void HeapSort(Type* arr, int size) {
		makeMaxHeap(arr, size);
		for (int i = size; i > 1; i--) {
			popMaxHeap(arr, i);
		}
	}
};


template<class Type>
class Msort {
private:
	void BubbleSort(Type *arr, int start, int end) {
		for (int i = start; i < end; i++) {
			for (int j = start; j < end - (i - start); j++) {
				if (arr[j] > arr[j + 1]) {
					Type temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	void merge(Type *arr, int start, int end) {
		int mid = (start + end) / 2;
		int l = start;
		int r = mid + 1;
		int i = 0;

		int size = end - start + 1;
		Type* temp = new Type[size];

		while (l <= mid && r <= end)
			temp[i++] = (arr[l] <= arr[r]) ? arr[l++] : arr[r++];

		while (l <= mid)
			temp[i++] = arr[l++];

		while (r <= end)
			temp[i++] = arr[r++];

		for (int i = 0; i < size; i++)
			arr[i + start] = temp[i];

		delete[] temp;
	}

public:
	void MergeSort(Type* arr, int start, int end) {
		if (end - start < 3) {
			BubbleSort(arr, start, end);
			return;
		}

		int mid = (start + end) / 2;
		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);

		merge(arr, start, end);
	}
};
