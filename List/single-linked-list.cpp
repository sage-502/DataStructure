// 단일 linked list
#include<iostream>
using namespace std;

class underflow {
	//empty
};

//노드 클래스 정의
class Node {
private:
	int element; //값
	Node* next_node; //다음 노드 주소
public:
	Node(int = 0, Node* = 0); //생성자
	friend class List;
};

Node::Node(int e, Node* n):element(e), next_node(n) { }

//리스트 클래스 정의
class List {
private:
	Node* list_head; //대가리 주소
public:
	List(); //constructor
	~List(); //destructor

	//접근
	bool empty() const; //리스트가 비었는가?
	int front() const; //리스트의 첫번째 멤버 반환
	Node* head() const; //대가리 주소 반환
	bool member(int) const; //해당 노드가 있는가?
	void show() const; //리스트 내용물 출력

	//조작
	void push_front(int); //대가리 넣기
	int pop_front(); //대가리 빼기
	bool erase(int); // 해당 노드 빼기
	void clear(); //리스트 비우기

	List& operator= (const List&);
};

List::List():list_head(0){ } //constructor

List::~List() { //destructor
	clear(); //리스트 비우기
	cout << "리스트 소멸" << endl;
}

// 접근
bool List::empty() const { //리스트가 비었는가?
	return (list_head == 0); //대가리 주소가 없으면 빈 걸로.
}

int List::front() const { //리스트의 대가리 값이 무엇인가?
	if (empty()) throw underflow(); //비었으면 execption
	else return list_head->element; //첫 항목 반환
}

Node* List::head() const { //대가리 주소 반환
	return list_head;
}

bool List::member(int n) const { //n이 리스트에 있는가
	for (Node* ptr = list_head; ptr != 0; ptr = ptr->next_node) { //노드 포인터 ptr : 대가리부터 꼬리까지 탐색
		if (ptr->element == n) return true; // 현재 노드가 n 값이면 true
	}
	return false; //끝까지 뒤졌는데도 없으면 false
}

void List::show() const { //리스트 내용물 보여주기
	cout << "[ ";
	for (Node* ptr = list_head; ptr != 0; ptr = ptr->next_node) {
		cout << ptr->element ;
		if (ptr->next_node) cout << ", ";
	}
	cout << " ]";
}

//조작
void List::push_front(int n) { //대가리 넣기
	list_head = new Node(n, list_head); //1. n을 element로 Node 생성, 2. 기존 대가리 주소를 next로, 3. 대가리 주소를 새 Node 주소로 갱신
}

int List::pop_front() { //대가리 빼기
	if (empty()) throw underflow(); //비었으면 execption

	int pop = front(); //기존 대가리 값 백업(pop으로 뱉기 위해)
	Node* temp = list_head; //기존 대가리 주소 백업(삭제를 위해)
	list_head = list_head->next_node; //기존 대가리의 다음 노드 주소를 새로운 대가리 주소로
	delete temp; //기존 대가리 제거
	return pop; //기존 대가리 값 반환
}

bool List::erase(int n) { //n값 가진 노드 제거
	if (empty()) return false; //비었으면 flase

	if (front() == n) { //대가리 값이 n이면
		pop_front(); //대가리 제거
		return true; //true 반환
	}

	for (Node* prv = list_head, *ptr = prv -> next_node;  //노드 포인터 prv : 이전 노드(첫번째 노드부터), 노드 포인터 ptr : 현재 노드(두번째 노드부터)
		ptr != 0; // ptr이 꼬리를 가르킬 때까지
		prv = prv -> next_node, ptr = prv -> next_node) { //prv, ptr 한 칸씩 이동
		if (ptr->element == n) { //현재 노드 값이 n이라면
			prv->next_node = ptr->next_node; //이전 노드의 다음 노드 → 현재 노드의 다음 노드
			delete ptr; //현재 노드 제거
			return true; // true 반환
		}
	}
	return false; //끝까지 뒤졌는데도 없으면 false
}

void List::clear() { //리스트 비우기
	while (!empty()) { //리스트가 비어있지 않은 동안
		pop_front(); //대가리 제거
	}
}

List& List::operator=(const List& rsh) { //복사
	if (&rsh == this) return *this; //자기 자신 복사일 때

	clear(); //기존 리스트 비우기

	if (rsh.empty()) return *this; //복사 대상이 비어있으면 그대로 반환

	list_head = new Node(rsh.front(), 0); //첫번째 노드 만들기

	for (Node* lptr = list_head, *rptr = rsh.list_head; //현재 노드 포인터 lptr(대가리 주소로 시작), 복사 대상의 현재 대응 노드 포인터 rptr(복사 대상 대가리 주소로 시작)
		rptr->next_node != 0; //복사 대상 대응 노드 포인터의 다음 노드(복사할 노드)가 꼬리일 때까지
		lptr = lptr->next_node, rptr = rptr->next_node) { //lptr, rptr 한 칸씩 이동
		lptr->next_node = new Node(rptr->next_node->element, 0); //현재 노드(lptr) 다음에 뒤에 복사 대상 대응 노드(rptr) 다음 노드 추가
	}

	return *this;
}
