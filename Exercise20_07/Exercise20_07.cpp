/**
* Class: CSCI2490 C++ Programming
* Instructor: Y. Daniel Liang
* Description: Linked list operations. 
* Due: 11/28/2016
* @author Shaun C. Dobbs
* @version 1.0

* I pledge by honor that I have completed the programming assignment independently.
* I have not copied the code from a student or any source.
* I have not given my code to any student.

Sign here: Shaun C. Dobbs
*/

#include <iostream>
#include <string> 
#include <stdexcept>
#include <vector>
#include <iterator>
using namespace std;

template<typename T>
class Node
{
public:
	T element;  // Element contained in the node
	Node<T> *next; // Pointer to the next node

	Node() // No-arg constructor
	{
		next = NULL;
	}

	Node(T element) // Constructor
	{
		this->element = element;
		next = NULL;
	}
};

template<typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
	Iterator() {

	};
	Iterator(Node<T>* p)
	{
		current = p;
	};

	Iterator operator++(int dummy)
	{
		current = current->next;
		return *this;
	}

	T& operator*()
	{
		return current->element;
	}


	bool operator==(const Iterator<T> &iterator)
	{
		return current == iterator.current;
	}

	bool operator!=(const Iterator<T> &iterator)
	{
		return current != iterator.current;
	}


private:
	Node<T>* current;
};


template<typename T>
class LinkedList
{
public:
	LinkedList();
	void addFirst(T element);
	void addLast(T element);
	T getFirst() const;
	T getLast() const;
	T removeFirst() throw (runtime_error);
	T removeLast();
	//void removeAll(const LinkedList<T>& otherList);
	void removeAll(LinkedList<T> otherList);
	void retainAll(LinkedList<T> otherList);
	void addAll(const LinkedList<T>& otherList);
	void add(T element);
	void add(int index, T element);
	void LinkedList<T>::clear();
	bool contains(T element);
	T get(int index) const;
	int indexOf(T element) const;
	bool isEmpty() const;
	int lastIndexOf(T element) const;
	bool remove(T element);
	int getSize() const;
	T remove(int index);
	T set(int index, T element);

	const LinkedList<T>& operator=(const LinkedList &list);
	// Define function operators
	T& operator[](int index);

	Iterator < T > begin() const
	{
		return Iterator<T>(head);
	};

	Iterator < T > end() const
	{
		return Iterator < T >(tail->next);
	};

	template<typename T> LinkedList<T> operator+();
	template<typename T> LinkedList<T> operator-();

private:
	Node<T> *head, *tail;
	int size;
};



template<typename T>
const LinkedList<T>& LinkedList<T>::operator = (const LinkedList &list) {
	LinkedList<T> temp;
	temp.addAll(list);
	head = temp.head;
	size = temp.size;
	tail = temp.tail;
	return *this;

}

template<typename T>
LinkedList<T> operator+(LinkedList<T>& firstlist, const LinkedList<T>& secondList) {
	firstlist.addAll(secondList);
	return firstlist;
}

template<typename T>
LinkedList<T> operator-(LinkedList<T>& firstlist, const LinkedList<T>& secondList) {
	firstlist.removeAll(secondList);
	return firstlist;
}

template<typename T>
LinkedList<T> operator^(LinkedList<T>& firstlist, const LinkedList<T>& secondList) {
	firstlist.retainAll(secondList);
	return firstlist;
}


template<typename T>
// Remove all the elements in otherList from this list
void LinkedList<T>::removeAll(LinkedList<T> otherList)
{
	Iterator<T> current = otherList.begin();
	while (current != otherList.end()) {
		remove(*current);
		current++;
	}
}

template<typename T>
// Retain all elements in this list if they are also in otherList
void LinkedList<T>::retainAll(LinkedList<T> otherList)
{
	Iterator<T> current = begin();
	while (current != end()) {
		if (!otherList.contains(*current))
			remove(*current);
		current++;
	}
}

template<typename T>
void LinkedList<T>::addAll(const LinkedList<T>& otherList)
{
	Iterator<T> current = otherList.begin();
	while (current != otherList.end())
	{
		//if (!contains(*current))
		add(*current);
		current++;
	}

}




template<typename T>
LinkedList<T>::LinkedList()
{
	head = tail = NULL;
	size = 0;
}

template<typename T>
void LinkedList<T>::addFirst(T element)
{
	Node<T> *newNode = new Node<T>(element);
	newNode->next = head;
	head = newNode;
	size++;

	if (tail == NULL)
		tail = head;
}

template<typename T>
void LinkedList<T>::addLast(T element)
{
	if (tail == NULL)
	{
		head = tail = new Node<T>(element);
	}
	else {
		tail->next = new Node<T>(element);
		tail = tail->next;
	}

	size++;
}

template<typename T>
T LinkedList<T>::getFirst() const
{
	if (size == 0)
		throw runtime_error("Index out of range");
	else
		return head->element;
}

template<typename T>
T LinkedList<T>::getLast() const
{
	if (size == 0)
		throw runtime_error("Index out of range");
	else
		return tail->element;
}

template<typename T>
T LinkedList<T>::removeFirst() throw (runtime_error)
{
	if (size == 0)
		throw runtime_error("No elements in the list");
	else
	{
		Node<T> *temp = head;
		head = head->next;
		size--;
		T element = temp->element;
		delete temp;
		return element;
	}
}

template<typename T>
T LinkedList<T>::removeLast()
{
	if (size == 0)
		throw runtime_error("No elements in the list");
	else if (size == 1)
	{
		Node<T> *temp = head;
		head = tail = NULL;
		size = 0;
		T element = temp->element;
		delete temp;
		return element;
	}
	else
	{
		Node<T> *current = head;

		for (int i = 0; i < size - 2; i++)
			current = current->next;

		Node<T> *temp = tail;
		tail = current;
		tail->next = NULL;
		size--;
		T element = temp->element;
		delete temp;
		return element;
	}
}



template<typename T>
void LinkedList<T>::add(T element)
{
	addLast(element);
}

template<typename T>
void LinkedList<T>::add(int index, T element)
{
	if (index == 0)
		addFirst(element);
	else if (index >= size)
		addLast(element);
	else
	{
		Node<T> *current = head;
		for (int i = 1; i < index; i++)
			current = current->next;
		Node<T> *temp = current->next;
		current->next = new Node<T>(element);
		(current->next)->next = temp;
		size++;
	}
}

template<typename T>
void LinkedList<T>::clear()
{
	while (head != NULL)
	{
		Node<T> *temp = head;
		delete temp;
		head = head->next;
	}

	tail = NULL;
}

template<typename T>
T LinkedList<T>::get(int index) const
{
	if (index < 0 || index > size - 1)
		throw runtime_error("Index out of range");

	Node<T> *current = head;
	for (int i = 0; i < index; i++)
		current = current->next;

	return current->element;
}

template<typename T>
int LinkedList<T>::indexOf(T element) const
{
	// Implement it in this exercise
	Node<T> *current = head;
	for (int i = 0; i < size; i++)
	{
		if (current->element == element)
			return i;
		current = current->next;
	}

	return -1;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return head == NULL;
}

template<typename T>
int LinkedList<T>::getSize() const
{
	return size;
}

template<typename T>
T LinkedList<T>::remove(int index)
{
	if (index < 0 || index >= size)
		throw runtime_error("Index out of range");
	else if (index == 0)
		return removeFirst();
	else if (index == size - 1)
		return removeLast();
	else {
		Node<T> *previous = head;

		for (int i = 1; i < index; i++)
		{
			previous = previous->next;
		}

		Node<T> *current = previous->next;
		previous->next = current->next;
		size--;
		T element = current->element;
		delete current;
		return element;
	}
}
template<typename T>
bool LinkedList<T>::remove(T element)
{
	Node<T> *previous = head;
	Node<T> *current;

	if (head != NULL)
	{
		if (element == head->element)
		{
			head = head->next;
			size--;
			return true;
		}
		else
		{
			current = head->next;
		}
	}
	else
		return false;

	for (int i = 0; i < size - 1; i++)
	{
		if (element == current->element) {
			previous->next = current->next; // Remove the current element
			size--;
			return true;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}

	return false;
}

template<typename T>
int LinkedList<T>::lastIndexOf(T element) const
{
	int lastIndex = -1;
	Node<T> *current = head;
	for (int i = 0; i < size; i++)
	{
		if (current->element == element)
			lastIndex = i;
		current = current->next;
	}

	return lastIndex;
}

template<typename T>
bool LinkedList<T>::contains(T element)
{
	return (indexOf(element) != -1);
}

template<typename T>
T LinkedList<T>::set(int index, T element)
{
	if (index < 0 || index >= size)
		throw runtime_error("Index out of range");

	Node<T> *current = head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	T oldElement = current->element;
	current->element = element;
	return oldElement;
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
	Node<T> *temp = head;
	for (int i = 0; i < index; i++)
		temp = temp->next;

	return temp->element;
}

template<typename T> void printList(const LinkedList<T>& list) {
	Iterator<T> current = list.begin();
	while (current != list.end()) {
		cout << *current << " ";
		current++;
	}
	cout << endl;
}

int main() {

	// Create a list for strings
	LinkedList < string > list;
	list.add("Beijing");
	list.add("Tokyo");
	list.add("New York");
	list.add("London");
	list.add("Paris");

	// Create a list for strings
	LinkedList < string > list2;
	list2.add("Beijing");
	list2.add("Shanghai");
	list2.add("Paris");
	list2.add("Berlin");
	list2.add("Rome");

	LinkedList<string> list1(list);
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	printList(list2);

	list1.addAll(list2);
	cout << "list is : ";
	printList(list);
	cout << "After list1.addAll(list2), list1 is ";
	printList(list1);

	list1 = list;
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	printList(list2);
	list1.removeAll(list2);
	cout << "After list1.removeAll(list2), list1 is ";
	printList(list1);

	list1 = list;
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	printList(list2);
	list1.retainAll(list2);
	cout << "After list1.retainAll(list2), list1 is ";
	printList(list1);

	list1 = list;
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	printList(list2);
	list1 = list1 + list2;
	cout << "After list1 = list1 + list2, list1 is ";
	printList(list1);

	list1 = list;
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	printList(list2);
	list1 = list1 - list2;
	cout << "After list1 = list1 - list2, list1 is ";
	printList(list1);

	list1 = list;
	cout << "list1: ";
	printList(list1);
	cout << "list2: ";
	list1 = list1 ^ list2;
	cout << "After list1 = list1 ^ list2, list1 is ";

	printList(list1);

	list1 = list;
	cout << list1[0] << endl;
	list1[0] = "Paris";
	cout << list1[0] << endl;


	return 0;
}
