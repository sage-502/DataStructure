#include <iostream>
#include <algorithm>
using namespace std;
#define UNDERFLOW -1

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
	Single_list():listHead(0), listTail(0), cnt(0) { }
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
		for (Single_node<Type>* ptr = listHead; ptr!=0; ptr = ptr->nextNode, i++) {
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
class Stack_list {
private:
	Single_list<Type> list; //Single_list 클래스의 객체 이용
public:
	bool empty() const { return list.empty(); }
	Type top() const { return list.front(); }
	void push(const Type& value) { list.push_front(value); }
	Type pop() { return list.pop_front(); }
};

template <typename Type>
class Stack_array {
private:
	int stack_size; //현 스택의 크기(스택에 객체가 몇 개 들어가 있는가)
	int array_capacity; //배열의 최대 크기
	Type* array; //배열을 가르킬 포인터
public:
	Stack_array(int n) :stack_size(0), array_capacity(std::max(1, n)), array(new Type[array_capacity]) {} //constructure
	~Stack_array() { //destructure
		delete[] array; //메모리 해제
		cout << "스택 소멸\n";
	}

	bool empty() { return (stack_size == 0); } //stack_size가 0이면 빈 거

	Type top() const { 
		if (empty()) throw UNDERFLOW; //비어있을 때
		return array[stack_size - 1]; //배열 마지막 값 반환
	}

	void push(const Type& value) {
		if (array_capacity == stack_size) throw UNDERFLOW; //배열이 다 차지 않았다면
		array[stack_size] = value; //배열 마지막 값 뒤에 추가
		stack_size++; //stack_size 증가
	}

	Type pop() {
		if (empty()) throw UNDERFLOW; //비어있을 때
		stack_size--; //stack_size 감소
		return array[stack_size]; //배열 마지막 값 반환(바로 위 라인에서 감소시켰으니가 -1 안함)
	}
};

int main() { }
