// TODO: define your my_list_iterator here
#include "my_list_iterator.h";
#include "my_list.h"

my_list_iterator::my_list_iterator(my_list* currList, bool end): list(currList), node(nullptr), end(end) {
	if (end == false) {
		node = list->get_first();
	}
}

my_list_iterator::my_list_iterator(const my_list_iterator& listCopy): list(listCopy.list), node(listCopy.node), end(listCopy.end) {
}

int& my_list_iterator::operator*() {
	if (node != nullptr) {
		return node->getValue();
	}
	else {
		throw std::exception();
	}
}

bool my_list_iterator::operator==(const my_list_iterator compare_against) const{
	if (compare_against.list != list) {
		throw std::exception();
	}

	if (compare_against.node == node) {
		return true;
	}

	return false;
}

bool my_list_iterator::operator!=(const my_list_iterator compare_against) const {
	if (compare_against.list != list) {
		throw std::exception();
	}

	if (compare_against.node == node) {
		return false;
	}

	return true;
};

my_list_iterator& my_list_iterator::operator++() {
	if (end || this->list->get_size() < 1) {
		throw std::exception();
	}

	if (node == this->list->get_last()) {
		end = true;
		node = nullptr;
		return *this;
	}
	else {
		node = this->node->getNext();
		return *this;
	}
};

my_list_iterator& my_list_iterator::operator--() {
	if (this->node == this->list->get_first()) {
		throw std::exception();
	}

	if (end) {
		end = false;
		node = this->list->get_last();
		return *this;
	}
	else {
		node = this->node->getPrevious();
		return *this;
	}
};

ListNode* my_list_iterator::get_mem() {
	return node;
};

bool my_list_iterator::is_end() {
	if (end) {
		return true;
	}
	else {
		return false;
	}
};

my_list* my_list_iterator::getList() {
	return this->list;
}