#pragma once

#include<iostream>

template <typename T>
class Queue
{
public:

	Queue(T data) : _size(1)
	{
		node* temp = new node;
		temp->data = data;
		temp->next = NULL;

		this->_front = temp;
		this->_rear = temp;

		this->_ptrTo_front = this->_front;
	}
	Queue() {}
	Queue(const Queue& other) : _size(0)
	{
		node* hold = other._front;

		while (hold != NULL)
		{
			this->Enqueue(hold->data);
			hold = hold->next;
		}
	}
	Queue(Queue&& other) noexcept
	{
		std::swap(this->_front, other._front);
		std::swap(this->_ptrTo_front, other._ptrTo_front);
		std::swap(this->_size, other._size);
		std::swap(this->_rear, other._rear);
	}
	~Queue()
	{
		clean();
	}

	void Enqueue(T data)
	{
		if (!this->_front)
		{
			this->_front = new node;
			this->_rear = this->_front;

			this->_front->data = data;
			this->_front->next = NULL;

			this->_size++;
			this->_ptrTo_front = this->_front;
			return;
		}

		node* newElement = new node;
		newElement->data = data;
		newElement->next = NULL;

		this->_rear->next = newElement;
		this->_rear = newElement;

		this->_size++;
	}
	void Dequeue()
	{
		if (this->_size == 0)
		{
			std::cout << "LIST_IS_EMPTY!" << std::endl;
			return;
		}
		if (this->_front == this->_rear)
		{
			delete this->_front;
			this->_front = NULL;
			this->_rear = NULL;

			this->_ptrTo_front = this->_front;
		}
		else
		{
			this->_front = this->_front->next;
			this->_ptrTo_front->next = NULL;

			delete this->_ptrTo_front;
			this->_ptrTo_front = this->_front;
		}
		this->_size--;
	}

	T Front() const { return this->_front->data; }
	inline bool empty() const
	{
		if (this->_size)
			return false;
		return true;
	}
	int size() const { return this->_size; }

	T& operator[](int index)
	{
		if (index > _size - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		if (index == 0)
			return _front->data;
		node* hold = this->_front->next;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	T& operator[](int index) const
	{
		if (index > _size - 1)
		{
			throw std::out_of_range("INDEX_ERROR"); this->clean();
		}
		if (index == 0)
			return _front->data;
		node* hold = this->_front->next;
		for (int i = 0; i < index - 1; i++)
		{
			hold = hold->next;
		}
		return hold->data;
	}
	Queue& operator=(const Queue& other)
	{
		if (this == &other)
			return *this;

		this->clean();

		this->_size = 0;

		node* hold = other._front;

		while (hold != NULL)
		{
			this->Enqueue(hold->data);
			hold = hold->next;
		}
		return *this;
	}
	Queue& operator=(Queue&& other) noexcept
	{
		if (this != &other)
		{
			this->clean();

			this->_front = other._front;
			this->_size = other._size;
			this->_ptrTo_front = other._ptrTo_front;
			this->_rear = other._rear;

			other._size = 0;
			other._front = nullptr;
			other._ptrTo_front = nullptr;
			other._rear = nullptr;

			return *this;
		}
		std::cout << "YOU_ARE_TRYING_TO_MOVE_THE_SAME_OBJ\n" << std::endl;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Queue& list) {

		node* current = list.PtrToFirst();
		os << "front -> ";
		while (current) {
			os << current->data << " -> ";
			current = current->next;
		}
		os << "rear" << std::endl;
		return os;
	}

protected:
	auto PtrToFirst() const { return this->_ptrTo_front; }
private:
	void clean()
	{
		node* prev = this->_front;
		if (this->_front == NULL)
			return;
		while (this->_front->next != NULL)
		{
			this->_front = this->_front->next;
			delete prev;
			prev = _front;
		}
		if (prev != NULL)
			delete prev;
		this->_front = NULL;
		this->_rear = NULL;
		this->_ptrTo_front = this->_front;
		this->_size = NULL;
	}
	struct node
	{
		T data;
		node* next;
	};
	int _size = 0;
	node* _ptrTo_front = nullptr;
	node* _rear = nullptr;
	node* _front = nullptr;
};