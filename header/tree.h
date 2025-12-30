//tree.h
#pragma once
#include<iostream>
#include <stdexcept>
#include"list.h"
using namespace std;

//기본 트리
template <class Type>
class Tree {
private:
	Type element;
	Tree<Type>* parent_node = nullptr;
	SinglyLinkedList<Tree<Type>*> children;
public:
	Tree(){}
	Tree(Type e) { element = e; }
	~Tree() { 
		Type temp = this->element;
		clear();
		cout << "delete:: element " << temp << endl;
	}

	Type retreive() const { return element; }
	Tree<Type>* parent() const { return parent_node; }
	int degree() { return children.count(); }
	bool is_root() { return parent_node == 0; }
	bool is_leaf() { return children.empty(); }

	void insert(Type const& e){
		Tree<Type>* temp = new Tree<Type>(e);
		children.push_back(temp);
		temp->parent_node = this;
	}

	void insert(Tree<Type>* node) {
		children.push_back(node);
		node->parent_node = this;
	}

	void detach() {
		Tree<Type>* p = this->parent_node;
		(p->children).remove(*this);
		this->parent_node = nullptr;
	}

	int size() const{
		int s = 1;
		for (Node<Tree<Type>*>* ptr = children.head(); ptr != nullptr; ptr = ptr->getBack()) {
			s += ptr->getElement()->size();
		}
		return s;
	}

	int height() const{
		int h = 0;
		for (Node<Tree<Type>*>* ptr = children.head(); ptr != nullptr; ptr = ptr->getBack()) {
			h = std::max(h, 1 + ptr->getElement()->height());
		}
		return h;
	}

	void show() const{
		cout << "element: " << this->element << "\theight: " << this->height() << endl;
		for (Node<Tree<Type>*>* ptr = children.head(); ptr != nullptr; ptr = ptr->getBack()) {
			ptr->getElement()->show();
		}
	}

	void clear(){
		while (!children.empty()) {
			Tree<Type>* child = children.pop();
			delete child;
		}
	}
};


//배열 기반 complete 이진 트리
template<class Type>
class CompleteBinaryTree {
private:
	Type* array = nullptr;
	int capacity = 0;
	int size = 0;

	void extend() {
		Type* newArray = new Type[capacity * 2 + 1];
		for (int i = 1; i <= size; i++) newArray[i] = array[i];
		delete[] array;
		capacity = capacity * 2;
		array = newArray;
	}

public:
	CompleteBinaryTree(int n = 5) {
		array = new Type[n + 1];
		capacity = n;
	}
	~CompleteBinaryTree() { delete[] array; }

	void insert(Type const& e) {
		if (size == capacity) extend();
		array[++size] = e;
	}

	Type pop_back() {
		if (size == 0) throw underflow_error("트리가 비어있습니다.\n");
		return array[size--];
	}

	void showBFS() const {
		cout << "elements in BFS order: ";
		for (int i = 0; i <= size; i++) cout << array[i] << " ";
		cout << endl;
	}

	void showDFS(int i = 1) {
		if (i > size) return;
		cout << array[i] << " ";
		showDFS(2 * i);
		showDFS(2 * i + 1);
	}
};

//포인터 기반 BinarySearchTree
template<class Type>
class BinarySearchTree {
private:
	Type element;
	BinarySearchTree<Type>* leftNode = nullptr;
	BinarySearchTree<Type>* rightNode = nullptr;
	int height = 0;
	int balance = 0;
public:
	BinarySearchTree() {}
	BinarySearchTree(Type const& e) :element(e) {}
	~BinarySearchTree() {
		clear();
		cout << "clear:: element " << element << endl;
	}

	Type retrieve() const { return element; }
	bool is_leaf() const { return leftNode == nullptr && rightNode == nullptr; }
	int size() const {
		int s = 1;
		if (this->leftNode != nullptr) s += leftNode->size();
		if (this->rightNode != nullptr) s += rightNode->size();
		return s;
	}
	int getHeight() const { return height; }

	void update() {
		if (leftNode) leftNode->update();
		if (rightNode) rightNode->update();

		int left = (leftNode != nullptr) ? leftNode->height : -1;
		int right = (rightNode != nullptr) ? rightNode->height : -1;

		height = std::max(left, right) + 1;
		balance = left - right;
	}

	void clear() {
		if (leftNode != nullptr) delete leftNode;
		if (rightNode != nullptr) delete rightNode;
		leftNode = rightNode = nullptr;
	}

	void showDFS() {
		if (leftNode) leftNode->showDFS();
		if (rightNode) rightNode->showDFS();
		cout << "element: " << this->element << "\theight: " << this->height << endl;;
	}

	void insert(Type const& value) {
		if (this->element < value) {
			if (this->rightNode == nullptr)
				this->rightNode = new BinarySearchTree(value);
			else this->rightNode->insert(value);
		}
		else {
			if (this->leftNode == nullptr)
				this->leftNode = new BinarySearchTree(value);
			else this->leftNode->insert(value);
		}
		update();
	}

	bool search(const Type& value) const {
		BinarySearchTree<Type>* ptr = this;
		while (ptr != nullptr) {
			if (ptr->element == value) return true;
			else if (ptr->element < value) ptr = ptr->rightNode;
			else ptr = ptr->leftNode;
		}
		return false;
	}

	BinarySearchTree* remove(Type x) {
		if (x < this->element) {
			if (this->leftNode) this->leftNode = this->leftNode->remove(x);
		}
		else if (x > this->element) {
			if (this->rightNode) this->rightNode = this->rightNode->remove(x);
		}
		else {
			// 삭제 대상 발견

			// Case 1 & 2
			if (!this->leftNode) {
				BinarySearchTree* r = this->rightNode;
				delete this;
				return r;
			}
			if (!this->rightNode) {
				BinarySearchTree* l = this->leftNode;
				delete this;
				return l;
			}

			// Case 3
			Type succ = this->rightNode->front();
			this->element = succ;
			this->rightNode = this->rightNode->remove(succ);
		}
		return this;
	}


	Type front() const{
		BinarySearchTree<Type>* ptr = this;
		while (ptr->leftNode != nullptr) ptr = ptr->leftNode;
		return ptr->element;
	}

	Type back() const {
		BinarySearchTree<Type>* ptr = this;
		while (ptr->rightNode != nullptr) ptr = ptr->rightNode;
		return ptr->element;
	}

	Type next(Type const& value) const {
		BinarySearchTree<Type>* ptr = (BinarySearchTree<Type>*)this;
		BinarySearchTree<Type>* next = nullptr;

		while (ptr) {
			if (ptr->element > value) {
				next = ptr;
				ptr = ptr->leftNode;
			}
			else {
				ptr = ptr->rightNode;
			}
		}

		if (next) return next->element;
		else return value;
	}

	Type at(int k) const { //0번부터 시작
		if (k < 0 || k >= this->size())
			throw underflow_error("index out of range");
		
		int leftsize = (this->leftNode == nullptr) ? 0 : this->leftNode->size();
		
		if (leftsize == k) return this->retrieve();
		else if (leftsize < k) return this->rightNode->at(k - leftsize - 1);
		else return this->leftNode->at(k);
	}
};


//포인터 기반 AVL Tree
template<class Type>
class AVLtree {
private:
	Type key;
	AVLtree<Type>* left = nullptr;
	AVLtree<Type>* right = nullptr;
	int height = 0;
	int balance = 0;
public:
	AVLtree(Type const& value):key(value) {}
	~AVLtree() {
		clear();
		cout << "clear:: element " << key << endl;;
	}

	int getHeight() { return height; } //height 반환

	void update() { //height, balance 갱신
		int leftheight = (left) ? left->height : -1;
		int rightheight = (right) ? right->height : -1;
		height = std::max(leftheight, rightheight) + 1;
		balance = leftheight - rightheight;
	}

	AVLtree<Type>* rotateCase1() { //일렬 : LL, RR 처리
		AVLtree<Type>* A, *B, *C, *keep;
		if (this->balance > 0) { //LL
			A = this;
			B = A->left;
			C = B->left;
			keep = B->right;
			B->right = A;
			A->left = keep;
		}
		else { //RR
			A = this;
			B = A->right;
			C = B->right;
			keep = B->left;
			B->left = A;
			A->right = keep;
		}
		A->update();
		B->update();
		return B;
	}

	AVLtree<Type>* rotateCase2() { //꺾임 : RL, LR 처리
		AVLtree<Type>* A, * B, * C, * keepL, * keepR;
		if (balance < 0) { //LR
			A = this;
			B = A->left;
			C = B->right;
			keepL = C->left;
			keepR = C->right;
			A->left = keepR;
			B->right = keepL;
			C->left = B;
			C->right = A;
		}
		else {
			A = this;
			B = A->right;
			C = B->left;
			keepL = C->left;
			keepR = C->right;
			A->right = keepR;
			B->left = keepL;
			C->right = B;
			C->left = A;
		}
		A->update();
		B->update();
		C->update();
		return C;
	}

	AVLtree<Type>* balanceNode() { //balance 조정 : rotate 함수 호출
		if (balance > 1 || balance < -1) {
			int balance1 = this->balance;
			int balance2 = (balance < 0) ? right->balance : left->balance;
			int shape = balance1 * balance2;
			if (shape < 0) return rotateCase2();
			else return rotateCase1();
		}
		update();
		return this;
	}

	AVLtree<Type>* insert(Type const& value) {
		if (key < value) {
			if (right) right = right->insert(value);
			else right = new AVLtree(value);
		}
		else {
			if (left) left = left->insert(value);
			else left = new AVLtree(value);
		}
		update();
		return balanceNode();
	}

	void showDFS() {
		cout << "element: " << key << "\theight: " << height << endl;
		if(left) left->showDFS();
		if(right) right->showDFS();
	}
	//void showBFS();

	void clear(){
		if (left) delete left;
		if (right) delete right;
	}
};
