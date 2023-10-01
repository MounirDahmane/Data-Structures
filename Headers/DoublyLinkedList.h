#pragma once

#include<iostream>

enum{BACKWARD = 0, FORWARD, HEAD = 999};
// pay attention to HEAD, i put it 999 because it would lead to problems if it was 2 or some other small number
// but feel free to modify it as it suits your logic

template <typename T>
class Doubly_LL
{
protected:
	struct node
	{
		node* prev;
		T data;
		node* next;
	};
public:
	Doubly_LL(T data) : numElements(0)
	{
		node* first = new node;
		first->prev = nullptr;
		first->data = data;
		first->next = nullptr;
		this->TrackerToHead = first;
		this->numElements++;
	}
	Doubly_LL() : numElements(0), TrackerToHead(nullptr)
	{
	}
	Doubly_LL(const Doubly_LL& other) : numElements(0)
	{
		node* current = other.TrackerToHead;
		while (current)
		{
			this->PushBack(current->data);
			current = current->next;
		}
	}
	Doubly_LL(Doubly_LL&& other) noexcept : numElements(other.numElements), TrackerToHead(other.TrackerToHead)
	{
		other.TrackerToHead = NULL;
		other.numElements = 0;
	}
	~Doubly_LL()
	{
		this->clean();
	}
	int GetSize() const { return this->numElements; }
	void print(int _MannerOfPrinting)
	{
		node* current = this->TrackerToHead;
		int i = -1;
		if (_MannerOfPrinting == FORWARD)
		{
			std::cout << "FORWARD : ";
			while (current)
			{
				std::cout << "[" << ++i << "]" << ":" << current->data << "-->";
				current = current->next;
			}
		}
		else if (_MannerOfPrinting == BACKWARD)
		{
			while (current->next)
			{ 
				current = current->next;
				++i;
			}
			++i;
			std::cout << "BACKWARD : ";
			while (current)
			{
				std::cout << "[" << i-- << "]" << ":" << current->data << "-->";
				current = current->prev;
			}
		}
		std::cout << "NULL" << std::endl;
	}
	void PushBack(T data)
	{
		if (!this->numElements) // this->numElements == 0
		{
			node* element = new node;
			element->prev = nullptr;
			element->data = data;
			element->next = nullptr;
			this->TrackerToHead = element;
		}
		else
		{
			node* current = this->TrackerToHead;
			while(current->next) // current != nullptr
			{
				current = current->next;
			}
			node* element = new node;
			element->prev = current;
			element->data = data;
			element->next = nullptr;
			current->next = element;
		}
		this->numElements++;
	}
	void PopBack()
	{
		if (!this->numElements) // this->numElements == 0 || this->TrackerToHead == nullptr
		{
			this->exception("THE_LIST_IS_EMPTY!"); 
			// you can use throw here but after using clean()
			std::cout << std::endl;
			return;
		}
		else
		{
			node* current = this->TrackerToHead;
			while (current->next->next)
			{
				current = current->next;
			}
			current->next->prev = nullptr;
			delete current->next;
			current->next = nullptr;
		}
		this->numElements--;
	}
	void insert(int index, T data)
	{
		if (index < 0 || index > this->numElements)
		{
			this->exception("INDEX_ERROR : INDEX_OUT_OF_RANGE\n\tMAX_INDEX_IS----->"); 
			// you can use throw here but after using clean()
			std::cout << this->GetSize() << " | THE_INDEX_WAS ----->" << index << std::endl;
			return;
		}
		node* newElement = new node;
		newElement->data = data;
		if (!index || index == HEAD) // index == 0
		{
			newElement->next = nullptr;
			newElement->prev = nullptr;
			this->TrackerToHead = newElement;
			this->numElements++;
			return;
		}

		node* current = this->TrackerToHead;
		for (std::size_t i = 0; i < index - 1; i++)
			current = current->next;

		node* next = current->next;
		newElement->prev = current;
		current->next = newElement;
		if (!next)
		{
			newElement->next = nullptr;
		}
		else if (next)
		{
			newElement->next = next;
			next->prev = newElement;
		}
		this->numElements++;
	}
	void remove(int index)
	{
		if (index < 0 || index >= this->numElements)
		{
			this->exception("INDEX_ERROR : INDEX_OUT_OF_RANGE\n\tMAX_INDEX_IS----->");
			// you can use throw here but after using clean()
			std::cout << this->GetSize() - 1<< " | THE_INDEX_WAS ----->" << index << std::endl;
			return;
		}
		node* current = this->TrackerToHead;
		if (!index || index == HEAD)
		{
			current = current->next; //second element
			current->prev = nullptr;
			this->TrackerToHead->next = nullptr;
			delete this->TrackerToHead;
			this->TrackerToHead = current;
			this->numElements--;
			return;
		}
		for (std::size_t i = 0; i < index - 1; i++)
			current = current->next;
		node* elementToDelete = current->next;
		current->next = elementToDelete->next;
		elementToDelete->prev = nullptr;
		if (elementToDelete->next)
		{
			(elementToDelete->next)->prev = current;
			elementToDelete->next = nullptr;
		}
		delete elementToDelete;
		this->numElements--;
	}
	node* CurrentPointerToHead() const {return this->TrackerToHead;}
	
	int& operator[](int index)
	{
		if (index < 0 || index > this->numElements - 1)
		{
			this->exception("INDEX_ERROR : INDEX_OUT_OF_RANGE\n\tMAX_INDEX_IS----->");
			// you can use throw here but after using clean()
			std::cout << this->GetSize() << " | THE_INDEX_WAS ----->" << index << std::endl;
			this->clean();
			throw;
		}
		node* current = this->TrackerToHead;
		for (std::size_t i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->data;
	}
	int& operator[](int index) const
	{
		if (index < 0 || index > this->numElements - 1)
		{
			this->exception("INDEX_ERROR : INDEX_OUT_OF_RANGE\n\tMAX_INDEX_IS----->");
			// you can use throw here but after using clean()
			std::cout << this->GetSize() << " | THE_INDEX_WAS ----->" << index << std::endl;
			this->clean();
			throw;
		}
		node* current = this->TrackerToHead;
		for (std::size_t i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->data;
	}

	Doubly_LL& operator=(const Doubly_LL& other)
	{
		if (this == &other)
			return *this;

		this->clean();

		node* current = other.TrackerToHead;
		while (current)
		{
			this->PushBack(current->data);
			current = current->next;
		}
		return *this;
	}
	Doubly_LL& operator=(Doubly_LL&& other) noexcept
	{
		if (this == &other)
		{
			std::cout << "YOU_ARE_TRYING_TO_MOVE_THE_SAME_OBJECT!" << std::endl;
			return *this;
		}
		this->clean();

		this->TrackerToHead = other.TrackerToHead;
		this->numElements = other.numElements;

		other.TrackerToHead = nullptr;
		other.numElements = 0;

		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Doubly_LL& other) {
		node* current = other.CurrentPointerToHead();
		while (current) {
			os << current->data << " -> ";
			current = current->next;
		}
		os << "nullptr" << std::endl;
		return os;
	}
private:
	node* TrackerToHead;// a ptr to the first element
	int numElements;;
	void clean()
	{
		if (!this->TrackerToHead) // this->TrackToHead == nullptr
			return;
		node* current = this->TrackerToHead;
		node* prev = current;
		current = current->next;
		while (current)
		{
			delete prev;
			prev = current;
			current = current->next;
		}
		if (prev)
			delete prev;
		current = nullptr;
		prev = nullptr;
		this->TrackerToHead = nullptr;
	}
	void exception(const char* message)
	{
		try { throw std::out_of_range(message); }
		catch (std::out_of_range& e) { std::cout << e.what(); }
	}
};