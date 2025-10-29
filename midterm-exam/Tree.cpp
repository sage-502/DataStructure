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
class Simple_tree {
private:
	Type element; //트리 노드가 담고 있는 데이터
	Simple_tree<Type>* parent_node; //부모 노드 주소
	Single_list<Simple_tree<Type>*> children; //자식 노드들 주소가 담긴 리스트
public:
	Simple_tree(Type const& e, Simple_tree<Type>* p) : element(e), parent_node(p) {} //constructor
	~Simple_tree() {} //destructor인데... 각 노드들을 메인에서 관리한다면 필요없을듯.

	Type retrieve() const { return element; } //노드 저장 데이터 반환
	Simple_tree<Type>* parent() const { return parent_node; } //부모 노드 주소 반환
	int degree() const { return children.size(); } //자식 노드 수 반환
	bool is_root() const { return (parent_node == 0); } //root인가?
	bool is_leaf() const { return (degree() == 0); } //leaf인가?

	Simple_tree<Type>* child(int n) const { //n번째 자식 노드(트리의 노드) 주소 반환
		if (n<1 || degree()<n) throw UNDERFLOW; //n이 유효하지 않을 때 처리
		Single_node<Simple_tree<Type>*>* ptr = children.head(); //ptr은 children 리스트의 각 노드들 주소. 대가리로 초기화.
		for (int i = 1; i < n;i++) { //n-1번 건너가기
			if (ptr != 0) ptr = ptr->next(); //개쫄려서 포인터 확인
		}
		return ptr->retrieve(); //해당 노드에 담겨 있는 데이터(트리 노드 주소) 반환
	}

	int height() {
		int h = 0; //height 초기값
		for (
			Single_node<Simple_tree<Type>*>* ptr = children.head(); //첫번째 자식 노드 주소에서 시작
			ptr != 0; //자식 노드가 끝날 때까지
			ptr = ptr->next() //자식 노드의 형제 노드로 이동
			) {
			h = std::max(h, 1 + ptr->retrieve()->height()); //재귀호출(DFS방식으로 동작하게 됨)
		}
		return h; //현 트리 노드에서의 height 반환
	}

	int size() const {
		int s = 1;
		for (
			Single_node<Simple_tree<Type>*>* ptr = children.head(); //첫번째 자식 노드 주소에서 시작
			ptr != 0; //자식 노드가 끝날 때까지
			ptr = ptr->next() //자식 노드의 형제 노드로 이동
			) {
			s += ptr->retrieve()->size(); //내 자식들에게 사이즈 보고 받아서 합산(나 포함)
		}
		return s; //현 트리 노드에서의 height 반환
	}

	void detach() {
		if (is_root()) return; //루트면 분리할 게 없음
		parent()->children.erase(this); //엄마, 저 자식 노드 리스트에서 호적 파주세요
		parent_node = 0; //이제 부모 없음
	}

	void insert(Type const& obj) {
		children.push_back(new Simple_tree<Type>(obj, this));
		//새로운 트리 노드 주소를 자식 노드 리스트에 추가 : 담을 데이터, 부모 알려주기
	}

	void insert(Simple_tree<Type>* tree) {
		if (!tree->is_root()) tree->detach(); //추가할 트리노드가 루트가 아니다? 뜯는다.
		tree->parent_node = this; //tree의 부모노드가 나
		children.push_back(tree); //내 자식 노드 리스트에 tree 추가
	}
};

int main() {}
