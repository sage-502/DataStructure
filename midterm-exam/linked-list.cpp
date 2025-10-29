#include <iostream>
using namespace std;
#define UNDERFLOW -1

class Node {
private:
	int element; //저장된 값
	Node* nextNode; //다음 노드 주소
public:
	int retrieve()const { return element; } //값 반환
	Node* next()const { return nextNode; } //다음 노드 주소 반환

	friend class List;
};

class List {
private:
	Node* listHead; //리스트의 첫번째 노드 주소
	Node* listTail; //리스트의 마지막 노드 주소
public:
	List():listHead(0), listTail(0) {} //생성자
	~List() { //소멸자
		while (!empty()) pop_front();
		cout << "리스트 소멸\n";
	}

	bool empty() const { return (listHead == 0); } //리스트가 비었는가?

	int front() const { //리스트 대가리 노드 값 반환
		if (empty()) throw UNDERFLOW; //대가리가 없는데용... -> 교재에서는 underflow()라고 적음
		else return listHead->retrieve();
	}

	Node* head() const { //리스트 대가리 노드 주소 반환
		return listHead;
	}

	bool member(int n) const { //n을 가진 노드가 리스트에 있는가?
		for (Node* ptr = listHead; ptr != 0; ptr = ptr->next()) {
			if (ptr->retrieve() == n) return true;
		}
		return false;
	}

	void push_front(int n) {
		Node* new_node = new Node; //새 대가리 노드 만들기
		new_node->element = n; // 새 노드에 값 저장
		new_node->nextNode = listHead; //다음 노드 주소 = 기존 대가리 주소
		listHead = new_node; //새로운 대가리 임명
		if (listTail == 0) listTail = new_node; //만약 꼬리가 없으면? 얘가 꼬리임
	}

	void push_back(int n) {
		Node* new_node = new Node; //새 꼬리 노드 만들기
		new_node->element = n; //새 노드에 값 저장
		new_node->nextNode = 0; //꼬리의 다음 노드 주소는 null
		if (listTail != 0) listTail->nextNode = new_node; //기존 꼬리 노드에 새 노드 연결
		listTail = new_node; //새로운 꼬리 임명
		if (listHead == 0) listHead = new_node; //만약 대가리가 없으면? 얘가 대가리임.
	}

	int pop_front() {
		if (empty()) throw UNDERFLOW;
		Node* tempPtr = listHead; //기존 대가리 접근 수단 백업
		int value = tempPtr->element; //기존 대가리의 값 백업
		listHead = tempPtr->nextNode; //새로운 대가리 임명
		if (listTail == tempPtr) listTail = 0; //만약 기존 대가리가 꼬리 겸직이었다면? listTail = null
		delete tempPtr; //기존 대가리 사형
		return value; //기존 대가리 값 반환
	}

	bool remove(int n) {
		if (empty()) return false; //리스트가 비었을 때
		if (listHead->element == n) { //대가리 노드가 n일 때
			pop_front();
			return true;
		}
		for (Node* ptrNode = listHead, *preNode = 0; ptrNode != 0; preNode = ptrNode, ptrNode = ptrNode->nextNode) { //ptrNode 현재 탐색 중인 노드. preNode 이전 노드.
			if (ptrNode->element == n) { //현재 탐색 중인 노드가 n일 때
				preNode->nextNode = ptrNode->nextNode; //이전 노드의 다음 노드 -> 현재 노드의 다음 노드
				if (listTail == ptrNode) listTail = preNode; //만약 현재 노드가 꼬리였다면 이전 노드가 새로운 꼬리
				delete ptrNode; //현재 노드 제거
				return true;
			}
		}
		return false;
	}
};

void main(){}
