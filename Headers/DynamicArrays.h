#pragma once

#include <iostream>

// it does not works correctly with strings ,but instead it works properly with const char*

template <typename T>

class DynamicArrays
{
public:
	DynamicArrays() : MaxSize(6), currentSize(0)
	{
		if (MaxSize > 0)
			ptr = new T[MaxSize];
	}
	DynamicArrays(T data) : MaxSize(6), currentSize(0)
	{
		if (MaxSize > 0)
			ptr = new T[MaxSize];
		ptr[this->currentSize] = data;
		this->currentSize++;
	}
	explicit DynamicArrays(int InitialSize) : MaxSize(InitialSize), currentSize(0)
	{
		if (MaxSize > 0)
			ptr = new T[MaxSize];
		else
		{
			throw std::out_of_range("SIZE_MUST_BE_GREATER_THEN_0 !");
		}
	}
	DynamicArrays(const DynamicArrays<T>& other) : MaxSize(other.MaxSize), currentSize(other.currentSize)
	{
		ptr = new T[MaxSize];
		std::memcpy(ptr, other.ptr, currentSize * sizeof(T)); // if the data is complex : std::copy is a better approach
	}
	DynamicArrays(DynamicArrays<T>&& other) noexcept : MaxSize(other.MaxSize), currentSize(other.currentSize), ptr(other.ptr)
	{
		other.MaxSize = 0;
		other.currentSize = 0;
		other.ptr = nullptr;
	}
	~DynamicArrays()
	{
		delete[] this->ptr;
	}

	int size() const
	{
		return currentSize;
	}
	void insert(T data, int index)
	{
		if (index > currentSize || index < 0)
		{
			delete[] this->ptr;
			throw std::out_of_range("INDEX_ERROR_OUT_OF_RANGE");
		}
		if (currentSize >= MaxSize)
			_GrowSize();

		if (this->currentSize == index && index == 0)
		{
			ptr[this->currentSize] = data;
			currentSize++;
			return;
		}
		if (index == this->currentSize)
		{
			this->PushBack(data);
			return;
		}

		try
		{
			T* Handler = new T[currentSize];
			std::memcpy(Handler, ptr, currentSize * sizeof(T));
			for (std::size_t i = 0; i < currentSize; i++)
			{
				if (i == index)
					ptr[i] = std::move(data);
				else if (i > index)
					ptr[i] = std::move(Handler[i - 1]);
			}
			int Last = currentSize - 1;
			currentSize++;
			ptr[currentSize - 1] = std::move(Handler[Last]);
			delete[] Handler;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "EXCEPTION :" << e.what() << std::endl;
			throw;
		}
	}
	//if the InLine argument is set to be true, the elements will be printed in one line, i thought that would be helpful when dealing with the char or string data types
	void PrintElement(bool InLine) const
	{
		if (InLine) {
			for (std::size_t i = 0; i < currentSize; i++)
				std::cout << ptr[i];
		}
		else {
			for (std::size_t i = 0; i < currentSize; i++)
				std::cout << ptr[i] << std::endl;
		}
	}
	void PushBack(T data)
	{
		if (currentSize < MaxSize)
		{
			ptr[currentSize] = data;
			currentSize++;
		}
		else
		{
			_GrowSize();
			ptr[currentSize] = data;
			currentSize++;
		}
	}
	void PopBack()
	{
		if (currentSize == 0)
		{ 
			throw std::out_of_range("ARRAY_IS_EMPTY");
			delete[] this->ptr;
		}
			
		else
		{
			T* newPtr = new T[currentSize - 1];
			std::memcpy(newPtr, this->ptr, (currentSize - 1) * sizeof(T));
			delete[] this->ptr;
			ptr = newPtr;
			currentSize--;
		}
	}
	void remove(int index)
	{
		if (index > currentSize || index < 0)
		{
			delete[] this->ptr;
			throw std::out_of_range("INDEX_ERROR_OUT_OF_RANGE");
		}
		if (currentSize >= 0)
		{
			if (this->currentSize == index)
			{
				this->PopBack();
				return;
			}
			try
			{
				T* Handler = new T[currentSize];
				std::memcpy(Handler, ptr, currentSize * sizeof(T));
				for (std::size_t i = 0; i < currentSize - 1; i++)
				{
					if (i >= index)
						ptr[i] = std::move(Handler[i + 1]);
				}
				delete[] Handler;
				currentSize--;
			}
			catch (const std::out_of_range& e)
			{
				std::cout << "EXCEPTION :" << e.what() << std::endl;
				throw;
			}
		}
		else
		{
			std::cout << "ARRAY_IS_EMPTY" << std::endl;
		}
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= currentSize)
			throw std::out_of_range("INDEX_ERROR");
		return ptr[index];
	}
	const T& operator[](int index) const
	{
		if (index < 0 || index >= currentSize)
			throw std::out_of_range("INDEX_ERROR");
		return ptr[index];
	}
	DynamicArrays<T>& operator=(DynamicArrays<T>&& other)
	{
		if (this->ptr != other.ptr) // this != &other
		{
			delete[] ptr;

			this->currentSize = other.currentSize;
			this->MaxSize = other.MaxSize;
			this->ptr = other.ptr;

			other.currentSize = 0;
			other.MaxSize = 0;
			other.ptr = nullptr;
		}
		else
		{
			std::cout << "YOU_ARE_TRYING_TO_MOVE_THE_SAME_OBJ\n" << std::endl;
			throw;
		}
		return *this;
	}
	DynamicArrays<T>& operator=(const DynamicArrays<T>& other)
	{
		delete[] this->ptr;

		this->currentSize = other.currentSize;
		this->MaxSize = other.MaxSize;

		this->ptr = new T[this->MaxSize];
		std::memcpy(this->ptr, other.ptr, this->currentSize * sizeof(T));

		return *this;
	}
	friend std::ostream& operator<<(std::ostream& stream, const DynamicArrays<T>& other)
	{
		for (std::size_t i = 0; i < other.size(); i++)
			stream << i << ":" << other[i] << "--->";
		stream << "END" << std::endl;
		return stream;
	}
	
private:

	void _GrowSize()
	{
		MaxSize += MaxSize;
		T* NewPtr = new T[MaxSize];
		std::memcpy(NewPtr, ptr, currentSize * sizeof(T));
		delete[] ptr;
		ptr = NewPtr;
	}
	unsigned int MaxSize;
	T* ptr = nullptr;
	unsigned int currentSize;
};