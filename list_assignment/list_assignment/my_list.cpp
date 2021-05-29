// TODO: define your my_list class here
#include "my_list.h"
#include <exception>


my_list::my_list() : frontNode(nullptr), backNode(nullptr), size(static_cast<int>(construct::initSize)){

}

my_list::my_list(const my_list& list) : frontNode(nullptr), backNode(nullptr), size(static_cast<int>(construct::initSize)) {
	ListNode* currNode = list.frontNode;
	while (currNode != nullptr) {
		this->push_back(currNode->getValue());
		currNode = currNode->getNext();
	}
};

my_list& my_list::operator=(const my_list& list) {

	if (&list != this) {
		this->clear();
		ListNode* currNode = list.frontNode;
		while (currNode != nullptr) {
			this->push_back(currNode->getValue());
			currNode = currNode->getNext();
		}
	}
	return *this;
};

my_list::~my_list() {
	clear();
}

unsigned int my_list::get_size() {
	return size;
};

int& my_list::front() {
	if (frontNode != nullptr) {
		return frontNode->getValue();
	}
	else {
		throw std::exception();
	}
};

int& my_list::back() {
	if (backNode != nullptr) {
		return backNode->getValue();
	}
	else {
		throw std::exception();
	}
};

void my_list::push_back(int val) {
	if (backNode != nullptr) {
		ListNode* newNode = new ListNode(nullptr, backNode, val);
		backNode->setNext(newNode);
		backNode = newNode;
	}
	else {
		ListNode* newNode = new ListNode(nullptr, nullptr, val);
		backNode = newNode;
		frontNode = newNode;
	}
	size++;
};

void my_list::push_front(int val) {
	if (frontNode != nullptr) {
		ListNode* newNode = new ListNode(frontNode, nullptr, val);
		frontNode->setPrevious(newNode);
		frontNode = newNode;
	}
	else {
		ListNode* newNode = new ListNode(nullptr, nullptr, val);
		backNode = newNode;
		frontNode = newNode;
	}
	size++;
};

void my_list::pop_back() {
	if (backNode != nullptr && size>1) {
		ListNode* newBack = backNode->getPrevious();
		backNode->setPrevious(nullptr);
		newBack->setNext(nullptr);
		delete backNode;
		backNode = newBack;
		size--;
	}
	else if (backNode != nullptr && size == 1) {
		delete backNode;
		backNode = nullptr;
		frontNode = nullptr;
		size=0;
	}
	else {
		throw std::exception();
	}
};


void my_list::pop_front() {
	if (frontNode != nullptr && size > 1) {
		ListNode* newFront = frontNode->getNext();
		frontNode->setNext(nullptr);
		newFront->setPrevious(nullptr);
		delete frontNode;
		frontNode = newFront;
		size--;
	}
	else if (frontNode != nullptr && size == 1) {
		delete frontNode;
		frontNode = nullptr;
		backNode = nullptr;
		size=0;
	}
	else {
		throw std::exception();
	}
};

void my_list::clear() {
	while (size > 1) {
		ListNode* current = frontNode;
		ListNode* next = current->getNext();
		current->setNext(nullptr);
		next->setPrevious(nullptr);
		delete current;
		frontNode = next;
		size--;
	}
	delete frontNode;
	frontNode = nullptr;
	backNode = nullptr;
	size = 0;
};

ListNode* my_list::get_first() {
	return frontNode;
};

ListNode* my_list::get_last() {
	return backNode;
};

my_list_iterator my_list::begin() {
	if (size < 1) {
		my_list_iterator* iter = new my_list_iterator(this, true);
		return *iter;
	}
	else {
		my_list_iterator* iter = new my_list_iterator(this, false);
		return *iter;
	}
};

my_list_iterator my_list::end() {
	my_list_iterator* iter = new my_list_iterator(this, true);
	return *iter;
};

my_list_iterator my_list::insert(my_list_iterator iter, int val) {
	if (size < 1) {
		ListNode* newNode = new ListNode(nullptr, nullptr, val);
		backNode = newNode;
		frontNode = newNode;
		size++;
		my_list_iterator iterNew =this->begin();
		return iterNew;
	}
	else if (iter.get_mem() == frontNode) {
		ListNode* newNode = new ListNode(iter.get_mem(), nullptr, val);
		iter.get_mem()->setPrevious(newNode);
		frontNode = newNode;
		size++;
		--iter;
		return iter;
	}
	else if (iter.is_end()) {
		ListNode* newNode = new ListNode(nullptr, backNode, val);
		backNode->setNext(newNode);
		backNode = newNode;
		size++;
		--iter;
		return iter;
	}
	else {
		ListNode* newNode = new ListNode(iter.get_mem(), iter.get_mem()->getPrevious(), val);
		iter.get_mem()->getPrevious()->setNext(newNode);
		iter.get_mem()->setPrevious(newNode);
		size++;
		--iter;
		return iter;
	}
};
my_list_iterator my_list::erase(my_list_iterator iter) {
	if (iter.is_end() || iter.getList() != this) {
		throw std::exception();
	}

	else if (size == 1) {
		ListNode* toDelete = iter.get_mem();
		frontNode = nullptr;
		backNode = nullptr;
		size--;
		++iter;
		delete toDelete;
		return iter;

	}
	else if (iter.get_mem() == backNode) {
		iter.get_mem()->getPrevious()->setNext(nullptr);
		backNode = iter.get_mem()->getPrevious();
		iter.get_mem()->setPrevious(nullptr);
		delete iter.get_mem();
		size--;
		my_list_iterator iterNew = this->end();
		return iterNew;
	}
	else if (iter.get_mem() == frontNode) {
		ListNode* toDelete = iter.get_mem();
		iter.get_mem()->getNext()->setPrevious(nullptr);
		frontNode = iter.get_mem()->getNext();
		++iter;
		toDelete->setNext(nullptr);
		delete toDelete;
		size--;
		return iter;
	}
	else {
		ListNode* toDelete = iter.get_mem();
		iter.get_mem()->getNext()->setPrevious(iter.get_mem()->getPrevious());
		iter.get_mem()->getPrevious()->setNext(iter.get_mem()->getNext());
		++iter;
		toDelete->setPrevious(nullptr);
		toDelete->setNext(nullptr);
		delete toDelete;
		size--;
		return iter;
	}
};