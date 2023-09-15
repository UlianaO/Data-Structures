#include <string>
#include "DLinkedList.h"


//constructor
DLinkedList::DLinkedList() {
	header = new DNode;
	trailer = new DNode;
	header->next = trailer;
	trailer->prev = header;
}

DLinkedList::~DLinkedList() {
	while (!empty())
		removeFront();
	delete header;
	delete trailer;
}

bool DLinkedList::empty() const {
	return (header->next == trailer); //if header points to trailer its empty
}

const string& DLinkedList::front() const {
	//return header->next->elem;
	return header->elem;
}

const string& DLinkedList::back() const {
	return trailer->prev->elem;
}

void DLinkedList::add(DNode* v, const string& e) {
	DNode* new_n = new DNode;
	new_n->elem = e;
	new_n->next = v;
	new_n->prev = v->prev;
	v->prev->next = new_n;
	v->prev = new_n;
}

void DLinkedList::addFront(const string& e) {
	add(header->next, e);
}

void DLinkedList::addBack(const string& e) {
	add(trailer, e);
}

void DLinkedList::remove(DNode* v) { // remove node v
	if (!empty()) {
		DNode* u = v->prev; // predecessor
		DNode* w = v->next; // successor
		u->next = w; // unlink v from list
		w->prev = u;
		delete v;
	}
}

// remove from font
void DLinkedList::removeFront() {
	remove(header->next);
}
// remove from back
void DLinkedList::removeBack() {
	remove(trailer->prev);
}
