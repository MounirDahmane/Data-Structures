#pragma once

#include <iostream>

template <typename T>

struct node
{
	T data;
	node* next;
	node<T> () {}

};

template <typename T>
class LinkedList
{
public:
	node<T>* current_to_head; 
	// is a pointer keep tracking the begining of the node/list (plus head), used to GetHead the begining in the
	// printing functions, i used it rather then head in some points to do some tricks and in order 
	// not complex the logic, but i think i did not succed at that at some point (+_+)

	LinkedList(T data) : numElements(0)
	{
		node<T>* first = new node<T>;
		first->data = data;
		first->next = NULL;
		numElements++;

		head = first;
		current_to_head = head;
	}
	LinkedList() : numElements(0), head(NULL), current_to_head(NULL)
	{
		
	}
	LinkedList(const LinkedList& other) : numElements(0), head(other.head)
	{
		node<T>* hold = this->head;
		current_to_head = this->head;
		while (hold != NULL)
		{
			insert(hold->data, this->numElements);
			hold = hold->next;
		}
	}
	LinkedList(LinkedList&& other) noexcept : numElements(0), head(nullptr), current_to_head(nullptr)
	{
		std::swap(this->head, other.head);
		std::swap(this->numElements, other.numElements);
		std::swap(this->current_to_head, other.current_to_head);
	}
	~LinkedList()
	{
		clean();
	}

	// the head here define the first index to print from or to stop at, 
	// for functions without it ,it prints from the very begining ---> the functions are commented at the end
	// the InOneLine arg is a choice whether you want to print the elements in one line or not
	// the r denote there is recursion
	void Print(int head, bool InOneLine)  
	{
		auto begin = GetHead(head);
		if (begin == NULL)
		{
			std::cout << "LIST_IS_EMPTY!" << std::endl;
			return;
		}
		while (begin != NULL)
		{
			std::cout << begin->data;
			if(!InOneLine)
				std::cout<< std::endl;
			begin = begin->next;
		}
		std::cout<<std::endl;
	}
	void rPrintFromEnd(int head, bool InOneLine)
	{
		node<T>* hold = GetHead(head);
		if (hold == NULL)
		{
			std::cout << "LIST_IS_EMPTY!" << std::endl;
			return;
		}
		if (this->current_to_head->next == NULL)
			return;
		node<T>* prev = this->current_to_head;
		this->current_to_head = this->current_to_head->next;
		rPrintFromEnd(head, InOneLine);
		if (this->current_to_head == this->head)
			return;
		std::cout << this->current_to_head->data;
		if (!InOneLine)
			std::cout << std::endl;
		if (head != numElements - 1)
			this->current_to_head = prev;
		if (this->current_to_head == hold)
		{
			if (head != numElements - 1)
				std::cout << this->current_to_head->data << std::endl;
			this->current_to_head = this->head;
		}
	}
	int  size() const
	{
		return numElements;
	}
	void insert(T data, int index)
	{
		if (index > numElements || index < 0)
		{
			this->exception();
		}
		if (this->current_to_head == NULL && this->head == NULL )
		{
			this->head = new node<T>;
			this->head->data = data;
			this->head->next = NULL;
			this->current_to_head = this->head;
			this->numElements++;
			return;
		}
		node<T>* temp = new node<T>;
		temp->data = data;
		temp->next = NULL;

		if (index == 0)
		{
			temp->next = this->head;
			this->head = temp;
			this->current_to_head = this->head;
			numElements++;
			return;
		}

		node<T>* hold;
		hold = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			if (hold == NULL)
				break;
			hold = hold->next;
		}
		temp->next = hold->next;
		hold->next = temp;
		if (index == numElements)
			temp->next = NULL;
		numElements++;
		return;
	}
	void push_back(T data)
	{
		if (this->numElements == 0) // this->head == NULL && this->current_to_head == NULL
		{
			this->head = new node<T>;
			this->head->data = data;
			this->head->next = NULL;
			this->current_to_head = this->head;
			this->numElements++;
			return;
		}
		node<T>* current = this->head;
		node<T>* temp = new node<T>;
		temp->data = data;
		temp->next = NULL;
		while(current->next != NULL)
		{
			current = current->next;
		}
		temp->next = current->next;
		current->next = temp;

		this->numElements++;
	}
	void pop_back()
	{
		if (this->numElements == 0)
			throw std::out_of_range("LIST_IS_EMPTY!");
		if (this->numElements == 1)
		{
			delete this->head;
			this->head = nullptr;
			this->current_to_head = nullptr;
		}
		else
		{
			node<T>* current = this->head;
			while (current->next->next)
			{
				current = current->next;
			}
			delete current->next;
			current->next = nullptr;
		}
		this->numElements--;
	}
	void remove(int index)
	{
		if (index > numElements - 1)
		{
			this->exception();
		}
		node<T>* eToDel;
		eToDel = head;
		if (index == 0)
		{
			head = head->next;
			delete eToDel;
			numElements--;
			return;
		}

		for (int i = 0; i < index - 1; i++)
		{
			eToDel = eToDel->next;
		}

		node<T>* hold = eToDel->next;
		eToDel->next = hold->next;

		delete hold;
		numElements--;
	}
	void reverse()
	{
		node<T>* prev = head;
		node<T>* current = head->next;
		node<T>* next = current->next;
		head->next = NULL;
		while (true)
		{
			if (current->next == NULL)
			{
				current->next = prev;
				prev = current;
				break;
			}
			current->next = prev;
			prev = current;
			current = next;
			next = current->next;
		}
		head = prev;
	}
	inline node<T>* rReverse(node<T>* begin)
	{
		if (begin == NULL || begin->next == NULL)
			return begin;

		node<T>* end = rReverse(begin->next);

		node<T>* temp = begin->next;
		temp->next = begin;
		begin->next = NULL;

		this->head = end;
		return end;
	}

	T& operator[](int index)
	{
		if (index > numElements - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		auto hold = this->head->next;
		if (index == 0)
			return head->data;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	T& operator[](int index) const
	{
		if (index > numElements - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		auto hold = this->head->next;
		if (index == 0)
			return head->data;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other)
			return *this;
		this->clean();

		this->head = other.head; // or the copy and swao idiom, using temp copy: std::swap(this->head, other.head)
		this->current_to_head = this->head;
		node<T>* hold = this->head;
		numElements = 0;
		while (hold != NULL)
		{
			insert(hold->data, numElements);
			hold = hold->next;
		}
		return *this;
	}
	LinkedList& operator=(LinkedList&& other) noexcept
	{
		if (this != &other)
		{
			this->clean();

			this->head = other.head;
			this->numElements = other.numElements;
			this->current_to_head = other.current_to_head;

			other.numElements = 0;
			other.head = nullptr;
			other.current_to_head = nullptr;

			return *this;
		}
			std::cout << "YOU_ARE_TRYING_TO_MOVE_THE_SAME_OBJ\n" << std::endl;
			throw;
	}
	friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
		node<T>* current = list.current_to_head;
		while (current) {
			os << current->data << " -> ";
			current = current->next;
		}
		os << "nullptr" << std::endl;
		return os;
	}
	
private:
	node<T>* GetHead(int index)  // a function to get the pointer of the elements that you want to end the printing at or begin from
	{
		// if the list is new and empty in the next if statement, an exception will be thrown so i added this->head != NULL
		if ((index > this->numElements - 1 && this->head != NULL)|| index < 0)
			this->exception();
		if (this->head != NULL && this->current_to_head != NULL) // if the list is not empty, the ptr will be returned for a given pos
		{
			node<T>* hold = this->head->next;
			if (index == 0)
				return head;
			for (int i = 0; i < index - 1; i++)
			{
				hold = hold->next;
			}
			return hold;
		}
		return head; // if the list is empty ,the head will be returned
	} 
	void clean()
	{
		node<T>* prev = this->head;
		if (this->head == NULL)
			return;
		while (this->head->next != NULL)
		{
			this->head = this->head->next;
			delete prev;
			prev = head;
		}
		if (prev != NULL)
			delete prev;
	}
	void exception()
	{
		try { throw std::out_of_range("INDEX_ERROR!"); }
		catch (std::out_of_range& e) { std::cout << e.what() << std::endl; clean(); throw; }
	}
	int numElements; // for keep track of the elements to prevent the index errors
	node<T>* head;   // a pointer to the begining of the list

	/*
	* void rPrintFromEnd(bool InOneLine)
	{
		node<T>* hold = this->current_to_head;
		if (this->current_to_head->next == NULL)
			return;
		this->current_to_head = this->current_to_head->next;
		rPrintFromEnd(InOneLine);
		std::cout << this->current_to_head->data;
		if (!InOneLine)
			std::cout << std::endl;

		this->current_to_head = hold;

		if (this->current_to_head == this->head)
		{
			std::cout << this->current_to_head->data;
			std::cout << std::endl;
		}
	}

		void Print(bool InOneLine) const
	{
		auto hold = this->head;
		while (hold != NULL )
		{
			std::cout << hold->data;
			if (!InOneLine)
				std::cout << std::endl;
			hold = hold->next;
		}
		std::cout << std::endl;
	}
	*/
};
