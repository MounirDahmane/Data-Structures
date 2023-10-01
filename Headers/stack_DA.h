#pragma once

#include <iostream>

// stack implementation with dynamic arrays : it has some issues when dealing with strings but it works fine with const char* instead

template <typename T>
class stack_DA
{
public:
	stack_DA() = default;
	stack_DA(T data) : c_size(1), MaxSize(3)
	{
		this->_ptr = new T[MaxSize];
		this->_ptr[0] = data;
		this->_top = data;
	}
	explicit stack_DA(T data, int reserve) : c_size(1), MaxSize(reserve)
	{
		if (reserve <= 0) { std::cout << "INDEX_ERROR : CURRENT_RESERVE = 1" << std::endl; MaxSize = 1; }
		this->_ptr = new T[MaxSize];
		this->_ptr[0] = data;
		this->_top = data;
	}
	stack_DA(const stack_DA& other) : _top(other._top), c_size(other.c_size), MaxSize(other.MaxSize)
	{
		this->_ptr = new T[MaxSize];
		std::memcpy(this->_ptr, other._ptr, sizeof(T) * this->c_size);
	}
	stack_DA(stack_DA&& other) noexcept : _top(other._top), c_size(other.c_size), MaxSize(other.MaxSize), _ptr(other._ptr)
	{
		other._ptr = nullptr;
		other._top = NULL;
		other.c_size = NULL;
		other.MaxSize = NULL;
	}
	~stack_DA()
	{
		delete[] this->_ptr;
	}

	void push(T data)
	{
		if (!this->_ptr)
		{
			if (this->MaxSize == 0)
				this->MaxSize++;
			this->_ptr = new T[MaxSize];
		}
		if (this->c_size > this->MaxSize - 1)
		{
			this->MaxSize += this->MaxSize;
			T* newPtr = new T[MaxSize];
			std::memcpy(newPtr, this->_ptr, sizeof(T) * this->c_size);
			delete[] this->_ptr;
			this->_ptr = newPtr;
			this->_ptr[this->c_size] = data;
		}
		else
			this->_ptr[this->c_size] = data;

		this->c_size++;
		this->_top = data;
	}
	void pop()
	{
		if (this->_ptr == nullptr || this->c_size == 0)
		{
			std::cout << "THE_LIST_IS_EMPTY!" << std::endl;
			return;
		}
		if (this->c_size == 1)
		{
			delete[] this->_ptr;
			this->_ptr = nullptr;
			this->c_size--;
			return;
		}

		T* newPtr = new T[(this->c_size - 1)];
		std::memcpy(newPtr, this->_ptr, sizeof(T) * (this->c_size - 1));
		delete[] this->_ptr;
		this->_ptr = newPtr;
		this->c_size--;
		this->_top = this->_ptr[this->c_size - 1];
	}
	void reverse()
	{
		//another way is commented :
		//stack_DA<T> temp(*this);

		stack_DA<T> temp;
		for (std::size_t i = 0; i < this->c_size; i++)
			temp.push(this->_ptr[i]);
		for (std::size_t i = 0; i < this->c_size; i++)
		{
			this->_ptr[i] = temp.top();
			temp.pop();
		}
		//this->_top = hold._top;
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
		if (index < 0 || index > this->c_size - 1)
		{
			std::cout << "INDEX_ERROR! | MAX_INDEX_IS----->" << this->c_size - 1 << std::endl; index;
		}
		// or to invert the indexing :
		// int data = (this->c_size - 1) - index; 
		//return this->_ptr[data];
		return this->_ptr[index];
	}
	T& operator[](int index) const
	{
		if (index<0 || index > this->c_size - 1)
		{
			std::cout << "INDEX_ERROR! | MAX_INDEX_IS----->" << this->c_size - 1 << std::endl; return;
		}
		// or to invert the indexing :
		// int data = (this->c_size - 1) - index; 
		//return this->_ptr[data];
		return this->_ptr[index];
	}

	friend std::ostream& operator<<(std::ostream& os, const stack_DA& other)
	{
		os << "TOP : \n   |\n   v\n";
		for (std::size_t i = other.size(); i > 0; i--)
		{
			os << "[" << i - 1 << "]" << " : " << (other.PtrToFirst())[i - 1] << "\n   |\n   v\n";
		}
		std::cout << "BOTTOM" << std::endl;
		return os;
	}

	stack_DA& operator=(const stack_DA& other)
	{
		if (this == &other)
		{
			std::cout << "YOU_ARE_COPYING_THE_SAME_OBJ!" << std::endl;
			return *this;
		}
		delete[] this->_ptr;
		this->c_size = other.c_size;
		this->MaxSize = other.MaxSize;
		this->_top = other._top;

		this->_ptr = new T[MaxSize];
		std::memcpy(this->_ptr, other._ptr, sizeof(T) * this->c_size);
		return *this;
	}
	stack_DA& operator=(stack_DA&& other) noexcept
	{
		if (this == &other)
		{
			std::cout << "YOU_ARE_MOVING_THE_SAME_OBJ!" << std::endl;
			return *this;
		}

		delete[] this->_ptr;

		this->c_size = other.c_size;
		this->MaxSize = other.MaxSize;
		this->_top = other._top;
		this->_ptr = other._ptr;

		other._ptr = nullptr;
		other._top = NULL;
		other.c_size = NULL;
		other.MaxSize = NULL;

		return *this;
	}

protected:
	T* PtrToFirst() const { return this->_ptr; }
private:
	int c_size = 0;
	T* _ptr = nullptr;
	T _top;
	int MaxSize = 0;
};
