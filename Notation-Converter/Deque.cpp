#include "Deque.h"
#include "DLinkedList.h"
//n - size of the list, D is an empty list

LinkedDeque::LinkedDeque()
	: D(), n(0) {}

//LinkedDeque::~LinkedDeque() {}

int LinkedDeque::size() const {
	return n;
}

bool LinkedDeque::empty() const { // is the deque empty?
	return n == 0;
}

const string& LinkedDeque::front() const {
	return D.front();
}// first element

const string& LinkedDeque::back() const {
	return D.back();
}// last element

void LinkedDeque::insertFront(const string& e) {
	D.addFront(e);
	n++;
}// insert new first element
void LinkedDeque::insertBack(const string& e) {
	D.addBack(e);
	n++;
}// insert new last element
void LinkedDeque::removeFront() {
	D.removeFront();
	n--;
}// remove first element
void LinkedDeque::removeBack() {
	D.removeBack();
	n--;

}