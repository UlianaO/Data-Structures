#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <string>
//#include "DLinkedList.cpp"

using namespace std;
//keyword Elem = string, generalized class 

class DNode {
private:
	std::string elem;
	DNode* prev;
	DNode* next;
	friend class DLinkedList;
};

class DLinkedList { 
public:
	DLinkedList(); // constructor
	~DLinkedList(); // destructor
	bool empty() const; // is list empty?
	const string& front() const; // get front element
	const string& back() const; // get back element
	void addFront(const string& e); // add to front of list
	void addBack(const string& e); // add to back of list
	void removeFront(); // remove from front
	void removeBack(); // remove from back
private:// local type definitions   
	DNode* header; // list sentinels   
	DNode* trailer;
protected:// local utilities
	void add(DNode* v, const string& e); //insert new node before v
	void remove(DNode* v); // remove node v 
};

#endif