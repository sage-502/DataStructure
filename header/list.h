//list.h
#pragma once
#include<iostream>
#include <stdexcept>
using namespace std;

template<class Type>
class SinglyLinkedList;

template<class Type>
class Tree;

template<class Type>
class Node {
private:
	Type element; //Type = TNode*
	Node<Type>* front_node=nullptr;
	Node<Type>* back_node=nullptr;
public:
	Node(Type e, Node<Type>* f = 0, Node<Type>* b = 0):element(e), front_node(f), back_node(b){}

	Type getElement() { return element; }
	Node<Type>* getFront() { return front_node; }
	Node<Type>* getBack() { return back_node; }
	friend class SinglyLinkedList<Type>;
	friend class Tree<Type>;
};


template<class Type>
class SinglyLinkedList {
private:
	Node<Type>* list_head = nullptr;
	Node<Type>* list_tail = nullptr;
	int node_count = 0;
public:
	SinglyLinkedList() { }
	~SinglyLinkedList() {
		while (!empty()) pop();
	}

	bool empty() const { return list_head == nullptr; }

	Node<Type>* head() const { return list_head; }

	Type front() const { 
		if (empty()) throw underflow_error("리스트가 비어 있습니다.");
		return list_head->element; 
	}

	bool member(Type e) const {
		for (Node<Type>* ptr = list_head; ptr != 0; ptr = ptr->back_node) {
			if (ptr->element == e) return true;
		}
		return false;
	}

	Type pop(){
		if (empty()) throw underflow_error("pop할 노드가 없습니다.");
		Node<Type>* temp = list_head;
		Type e = temp->element;
		list_head = temp->back_node;
		if (list_head == nullptr) list_tail = nullptr;
		delete temp;
		node_count--;
		return e;
	}

	bool remove(Type e) {
		if (empty()) return false;
		if (list_head->element == e) {
			pop();
			return true;
		}

		for (Node<Type> *pre = list_head, *ptr = list_head->back_node;
			ptr != 0; 
			pre = ptr, ptr = ptr->back_node) {
			if (ptr->element == e) {
				pre->back_node = ptr->back_node;
				if (ptr == list_tail) list_tail = pre;
				delete ptr;
				node_count--;
				return true;
			}
		}
		return false;
	}
	
	void push_front(Type e) {
		list_head = new Node<Type>(e, 0, list_head);
		if (node_count == 0) list_tail = list_head;
		node_count++;
	}

	void push_back(Type e) {
		if (empty()) list_head = list_tail = new Node<Type>(e);
		else {
			list_tail->back_node = new Node<Type>(e);
			list_tail = list_tail->back_node;
		}
		node_count++;
	}

	int count() const { return node_count; }
};
