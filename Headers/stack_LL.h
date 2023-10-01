#pragma once

#include<iostream>

// stack implementation with Linked List : it has some issues when dealing with the strings but it work fine with the const char*

template <typename T>
class stack_LL
{
public:
	
	stack_LL(T data) : c_size(1)
	{
		node* first = new node;
		first->data = data;
		first->next = NULL;

		this->head = first;
		this->_ptrToHead = this->head;
	}
	stack_LL() {}
	stack_LL(const stack_LL& other) : c_size(0)
	{
		this->_ptrToHead = this->head;
		node* hold = other.head;

		while (hold != NULL)
		{
			this->push(hold->data);
			hold = hold->next;
		}
	}
	stack_LL(stack_LL&& other) noexcept
	{
		std::swap(this->head, other.head);
		std::swap(this->_top, other._top);
		std::swap(this->_ptrToHead, other._ptrToHead);
		std::swap(this->c_size, other.c_size);
	}
	~stack_LL()
	{
		clean();
	}

	void push(T data)
	{
		if (!this->head)
		{
			this->head = new node;
			this->head->data = data;
			this->head->next = NULL;
			this->_top = this->head->data;
			this->c_size++;
			this->_ptrToHead = this->head;
			return;
		}
		node* temp = this->head;
		while (temp->next)
			temp = temp->next;
		node* newElement = new node;
		newElement->data = data;
		newElement->next = NULL;
		temp->next = newElement;
		this->_top = data;
		this->c_size++;
	}
	void pop()
	{
		if (this->c_size == 0)
		{
			std::cout << "LIST_IS_EMPTY!" << std::endl;
			return;
		}
		if (this->c_size == 1)
		{
			delete this->head;
			this->head = NULL;
			this->_ptrToHead = this->head;
			this->_top = NULL;
		}
		else
		{
			node* temp = this->head;
			while (temp->next->next)
				temp = temp->next;
			delete temp->next;
			temp->next = NULL;
			this->_top = temp->data;
		}
		this->c_size--;
	}
	void reverse()
	{
		if (!this->head || !this->head->next)	
			return;
		stack_LL<node*> temp;
		node* hold = this->head;
		while (hold->next)
		{
			temp.push(hold->next);
			hold = hold->next;
		}
		this->head = temp.top();
		temp.pop();
		while (!temp.empty())
		{
			hold->next = temp.top();
			hold = hold->next;
			temp.pop();
		}
		hold->next = this->_ptrToHead;
		this->_ptrToHead->next = NULL;
		this->_ptrToHead = this->head;
	}

	T top() const { return this->_top; }
	inline bool empty() const
	{
		if (this->c_size)
			return false;
		return true;
	}
	int size() const { return this->c_size; }

	T& operator[](int index)
	{
		if (index > c_size - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		if (index == 0)
			return head->data;
		node* hold = this->head->next;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	T& operator[](int index) const
	{
		if (index > c_size - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		if (index == 0)
			return head->data;
		node* hold = this->head->next;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	stack_LL& operator=(const stack_LL& other)
	{
		if (this == &other)
			return *this;

		this->clean();

		this->c_size = 0;

		node* hold = other.head;

		while (hold != NULL)
		{
			this->push(hold->data);
			hold = hold->next;
		}
		return *this;
	}
	stack_LL& operator=(stack_LL&& other) noexcept
	{
		if (this != &other)
		{
			this->clean();

			this->head = other.head;
			this->c_size = other.c_size;
			this->_ptrToHead = other._ptrToHead;
			this->_top = other._top;

			other.c_size = 0;
			other.head = nullptr;
			other._top = NULL;
			other._ptrToHead = nullptr;

			return *this;
		}
		std::cout << "YOU_ARE_TRYING_TO_MOVE_THE_SAME_OBJ\n" << std::endl;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const stack_LL& list) {

		node* current = list.PtrToFirst();
		std::cout << "BOTTOM ->";
		while (current) {
			os << current->data << " -> ";
			current = current->next;
		}
		os << " TOP" << std::endl;
		return os;
	}

protected:
	auto PtrToFirst() const { return this->_ptrToHead; }
private:
	void clean()
	{
		node* prev = this->head;
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
		this->head = NULL;
	}
	struct node
	{
		T data;
		node* next;
	};
	int c_size = 0;
	node* head = nullptr;
	node* _ptrToHead = nullptr;
	T _top = NULL;
};
