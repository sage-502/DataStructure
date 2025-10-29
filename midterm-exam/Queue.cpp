#include <iostream>
#include <algorithm>
using namespace std;

template <typename Type> class Single_list;

template <typename Type>
class Single_node {
private:
	Type element;
	Single_node<Type>* nextNode;
public:
	Type retrieve() const { return element; }
	Single_node<Type>* next() const { return nextNode; }

	friend class Single_list<Type>;
};

template <typename Type>
class Single_list {
private:
	Single_node<Type>* listHead;
	Single_node<Type>* listTail;
	int cnt;
public:
	Single_list() :listHead(0), listTail(0), cnt(0) {}
	~Single_list() {
		while (!empty()) pop_front();
		cout << "리스트 제거\n";
	}

	int size() const { return cnt; }
	bool empty() const { return (cnt == 0); }

	Type front() const {
		if (cnt == 0) throw UNDERFLOW;
		return listHead->element;
	}

	Type back() const {
		if (cnt == 0) throw UNDERFLOW;
		return listTail->element;
	}

	Single_node<Type>* head() const { return listHead; }
	Single_node<Type>* tail() const { return listTail; }

	int count(const Type& value) const {
		int i = 1;
		for (Single_node<Type>* ptr = listHead; ptr != 0; ptr = ptr->nextNode, i++) {
			if (ptr->element == value) return i;
		}
		return 0;
	}

	void push_front(const Type& value) {
		Single_node<Type>* new_node = new Single_node<Type>;
		new_node->element = value;
		new_node->nextNode = listHead;
		listHead = new_node;
		if (listTail == 0) listTail = new_node;
		cnt++;
	}

	void push_back(const Type& value) {
		Single_node<Type>* new_node = new Single_node<Type>;
		new_node->element = value;
		new_node->nextNode = 0;
		if (listTail != 0) listTail->nextNode = new_node;
		listTail = new_node;
		if (listHead == 0) listHead = new_node;
		cnt++;
	}

	Type pop_front() {
		if (empty()) throw UNDERFLOW;
		Single_node<Type>* temp = listHead;
		Type value = temp->element;
		listHead = temp->nextNode;
		if (listTail == temp) listTail = 0;
		delete temp;
		cnt--;
		return value;
	}

	int erase(const Type& value) {
		if (empty()) return 0;
		if (listHead->element == value) {
			pop_front();
			return 1;
		}
		for (Single_node<Type>* ptrNode = listHead, *preNode = 0;
			ptrNode != 0;
			preNode = ptrNode, ptrNode = ptrNode->nextNode) {
			if (ptrNode->element == value) {
				preNode->nextNode = ptrNode->nextNode;
				if (listTail == ptrNode) listTail = preNode;
				delete ptrNode;
				cnt--;
				return 1;
			}
		}
		return 0;
	}
};

template <typename Type>
class Queue_list {
private:
	Single_list<Type> list; //리스트 클래스 객체 이용
public:
	bool empty() const { return list.empty(); }
	Type front() const { return list.front(); }
	void push(const Type& value) { list.push_back(value); }
	Type pop() { return list.pop_front(); }
};

template <typename Type>
class Queue_array {
private:
	int queue_size; // 현재 큐 크기
	int ifront; //맨앞 인덱스
	int iback; //맨뒤 인덱스
	int array_capacity; //배열 한도
	Type* array; //배열 포인터
public:
	Queue_array(int n = 10):queue_size(0), ifront(0), iback(-1), array_capacity(n), array(new Type[max(1, n)]) {} //생성자
	~Queue_array() { //소멸자
		delete[] array; //배열 삭제
		cout << "큐 소멸\n";
	}

	bool empty() const { return(queue_size == 0); }
	Type front() const { return  array[ifront]; }

	void push(const Type& value){
		if (queue_size == array_capacity) { //배열이 꽉 찼다면
			Type* temp = array; //기존 배열 접근수단 백업
			array = new Type[array_capacity * 2]; //array를 2배 크기로 새로 할당
			for (int i = 0; i < array_capacity; i++) //기존 값 복사
				array[i] = temp[(ifront + i) % array_capacity];
			delete[]temp; //백업 배열 삭제
			array_capacity *= 2; //배열 크기 2배
		}
		iback = (iback + 1) % array_capacity; //인덱스 증가(범위 조정)
		array[iback] = value; //추가
		queue_size++; //큐 사이즈 증가
	}

	Type pop() {
		if (empty()) throw UNDERFLOW; //비어있을 때
		Type value = array[ifront]; //값 백업
		ifront = (ifront + 1) % array_capacity; //인덱스 증가(범위 조정)
		queue_size--; //큐 사이즈 감소
		return value; //백업 값 반환
	}
};

int main() {}
