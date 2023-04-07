#pragma once
#include <iostream>

template <class T>
class Stack 
{
	public:
		virtual ~Stack() {}
		virtual void push(const T& e) = 0;
		virtual const T& pop() = 0;
		virtual bool isEmpty() = 0;

		class StackException 
		{
			public:
				std::string getMessage() const;

			private:
				std::string message_;
		};
};

template <class T>
class StackArray : public Stack<T>
{
	private:
		T* array_;
		size_t top_;
		size_t size_;
		void swap(StackArray<T>& src);

	public:
		StackArray(size_t size = 100);
		StackArray(const StackArray<T>& src);
		StackArray(StackArray<T>&& src) = delete;
		StackArray& operator=(const StackArray<T>& src) = delete;
		StackArray& operator=(StackArray<T>&& src) = delete;
		virtual ~StackArray() = default;
		void push(const T& e);
		const T& pop();
		bool isEmpty();

		class StackOverflow : public Stack<T>::StackException 
		{
			public:
				StackOverflow(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};

		class StackUnderflow : public Stack<T>::StackException 
		{
			public:
				StackUnderflow(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};

		class WrongStackSize : public Stack<T>::StackException 
		{
			public:
				WrongStackSize(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};
};

template <class T>
StackArray<T>::StackUnderflow::StackUnderflow(const std::string& message) : message_(message) {}
template <class T>
std::string StackArray<T>::StackUnderflow::getMessage() const 
{ 
	return message_; 
}

template <class T>
StackArray<T>::StackOverflow::StackOverflow(const std::string& message) : message_(message) {}
template <class T>
std::string StackArray<T>::StackOverflow::getMessage() const 
{
	return message_; 
}

template <class T>
StackArray<T>::WrongStackSize::WrongStackSize(const std::string& message) : message_(message) {}
template <class T>
std::string StackArray<T>::WrongStackSize::getMessage() const 
{ 
	return message_; 
}

template <class T>
StackArray<T>::StackArray(const StackArray<T>& src) :
	size_(src.size_),
	top_(src.top_)
{
	try 
	{
		array_ = new T[src.size_ + 1];
	}
	catch (const StackArray<T>::WrongStackSize& err) 
	{
		std::cout << "Error: " << err.getMessage() << std::endl;
		exit(1);
	}
	
	for (size_t i = 1; i < src.top_; i++) 
	{
		array_[i] = src.array_[i];
	}
}

template <class T>
StackArray<T>::StackArray(size_t size) : size_(size), top_(0)
{
	try 
	{
		array_ = new T[size + 1];
	}
	catch (const StackArray<T>::WrongStackSize& err) 
	{
		std::cerr << "Error: " << err.getMessage() << std::endl;
		exit(1);
	}
}

template <class T>
void StackArray<T>::swap(StackArray<T>& src) 
{
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
bool StackArray<T>::isEmpty() 
{ 
	return top_ == 0; 
}

template <class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_) 
	{
		throw StackOverflow("Too much elements!!!");
	}
	array_[++top_] = e;
}

template <class T>
const T& StackArray<T>::pop()
{
	if (isEmpty()) 
	{
		throw StackUnderflow("Not enough elements!!!");
	}
	return array_[top_--];
}