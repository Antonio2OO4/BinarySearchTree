#pragma once
#include <iostream>

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual void enQueue(const T& e) = 0;
	virtual const T deQueue() = 0;
	virtual bool isEmpty() = 0;

	class QueueException 
	{
		public:
			std::string getMessage() const;

		private:
			std::string message_;
	};
};

template <class T>
class QueueArray : public Queue<T>
{
	private:
		T* array_;
		size_t top_;
		size_t bot_;
		size_t size_;
		size_t count_;
		void swap(QueueArray<T>& src);

	public:
		QueueArray(size_t size = 100);
		QueueArray(const QueueArray<T>& src);
		QueueArray(QueueArray<T>&& src) = delete;
		QueueArray& operator=(const QueueArray<T>& src) = delete;
		QueueArray& operator=(QueueArray<T>&& src) = delete;
		~QueueArray() = default;
		bool isEmpty();
		void enQueue(const T& e);
		const T deQueue();

		class QueueOverflow : public Queue<T>::QueueException 
		{
			public:
				QueueOverflow(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};

		class QueueUnderflow : public Queue<T>::QueueException 
		{
			public:
				QueueUnderflow(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};

		class WrongQueueSize : public Queue<T>::QueueException 
		{
			public:
				WrongQueueSize(const std::string& message);
				std::string getMessage() const;

			private:
				std::string message_;
		};
};

template <class T>
QueueArray<T>::QueueUnderflow::QueueUnderflow(const std::string& message) : message_(message) {}
template <class T>
std::string QueueArray<T>::QueueUnderflow::getMessage() const 
{ 
	return message_; 
}

template <class T>
QueueArray<T>::QueueOverflow::QueueOverflow(const std::string& message) : message_(message) {}
template <class T>
std::string QueueArray<T>::QueueOverflow::getMessage() const 
{ 
	return message_; 
}

template <class T>
QueueArray<T>::WrongQueueSize::WrongQueueSize(const std::string& message) : message_(message) {}
template <class T>
std::string QueueArray<T>::WrongQueueSize::getMessage() const 
{ 
	return message_; 
}

template <class T>
QueueArray<T>::QueueArray(const QueueArray<T>& src) : size_(src.size_), top_(src.top_), count_(src.count_) {
	try 
	{
		array_ = new T[src.size_ + 1]; 
	}
	catch (const QueueArray<T>::WrongQueueSize& err) 
	{
		std::cerr << "Error: " << err.getMessage() << std::endl;
		exit(1);
	}

	for (size_t i = 1; i < src.top_; i++) 
	{
		array_[i] = src.array_[i];
	}
}

template <class T>
QueueArray<T>::QueueArray(size_t size) : size_(size), top_(0), bot_(0), count_(0) {
	try 
	{
		array_ = new T[size + 1];
	}
	catch (const QueueArray<T>::WrongQueueSize& err) 
	{
		std::cerr << "Error: " << err.getMessage() << std::endl;
		exit(1);
	}
}

template <class T>
void QueueArray<T>::swap(QueueArray<T>& src) {
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
bool QueueArray<T>::isEmpty() 
{ 
	return top_ == bot_; 
}

template <class T>
void QueueArray<T>::enQueue(const T& e) 
{
	if (count_ == size_) 
	{ 
		throw QueueOverflow("No space in the queue!"); 
	}
	array_[(++top_) % (size_ + 1) + (top_ / size_)] = e;
	count_++;
}

template <class T>
const T QueueArray<T>::deQueue() {
	if (isEmpty()) 
	{ 
		throw QueueUnderflow("Not enough elements in the queue!");
	}
	count_--;
	return array_[(++bot_) % (size_ + 1) + (bot_ / size_)];
}