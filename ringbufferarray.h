#pragma once
#include "ringbuffer.h"

// Реализация кольцевого буфера через массив
// Плюсы: быстрый доступ к произвольным элементам буфера, расположение в едином непрерывном участке памяти
// Минусы: дорогостоящая операция изменения размера буфера с перекопированием памяти

template<typename T>
class RingBuffer_Array : public AbstractRingBuffer<T>
{

	T* data_;

	// Размер буфера
	int size_;

	// Индекс самого старого элемента. Если в буфере нет элементов, то равен -1
	int oldest_;

	// Индекс самого нового элемента
	int newest_;

public:

	RingBuffer_Array(int size) : size_(size), oldest_(-1), newest_(-1)
	{
		if (size_ <= 0)
		{
			throw "Invalid ring buffer size";
		}

		data_ = new T[size_];
	}

	~RingBuffer_Array()
	{
		delete[] data_;
	}

	RingBuffer_Array(const RingBuffer_Array&) = delete;
	RingBuffer_Array(RingBuffer_Array&&) = delete;
	RingBuffer_Array& operator=(const RingBuffer_Array&) = delete;
	RingBuffer_Array& operator=(RingBuffer_Array&&) = delete;

	T& operator[](int index) override
	{
		if (!count())
		{
			throw "No elements in ring buffer";
		}

		if (index < 0)
		{
			throw "Invalid index";
		}

		return data_[(oldest_ + (index % count())) % size_];
	}

	T operator[](int index) const override
	{
		if (!count())
		{
			throw "No elements in ring buffer";
		}

		if (index < 0)
		{
			throw "Invalid index";
		}

		return data_[(oldest_ + (index % count())) % size_];
	}

	void push(const T& val) override
	{
		if (!count())
		{
			data_[0] = val;
			oldest_ = newest_ = 0;
			return;
		}

		if (count() < size_)
		{
			newest_ = (newest_ + 1) % size_;
			data_[newest_] = val;
			return;
		}

		data_[oldest_] = val;
		newest_ = oldest_;
		oldest_ = (oldest_ + 1) % size_;
	}

	T pop() override
	{
		if (!count())
		{
			throw "No elements in buffer";
		}

		int index_to_return = oldest_;
		oldest_ = oldest_ != newest_ ? (oldest_ + 1) % size_ : -1;

		return data_[index_to_return];
	}

	int size() const override
	{
		return size_;
	}

	int count() const override
	{
		if (oldest_ < 0)
		{
			return 0;
		}

		return oldest_ <= newest_ ? newest_ - oldest_ + 1 : size_ - oldest_ + newest_ + 1;
	}

	void resize(int newSize) override
	{
		if (newSize <= 0)
		{
			throw "Invalid ring buffer size";
		}

		if (newSize == size_)
		{
			return;
		}

		T* newData = new T[newSize];

		if (newSize < size_)
		{
			for (int i = 0; i < newSize; ++i)
			{
				newData[newSize - 1 - i] = data_[(size_ + newest_ - i) % size_];
			}
			oldest_ = 0;
			newest_ = newSize - 1;
		}
		else
		{
			for (int i = 0; i < count(); ++i)
			{
				newData[i] = data_[(oldest_ + i) % size_];
			}
			oldest_ = 0;
			newest_ = count() - 1;
		}

		delete[] data_;

		size_ = newSize;
		data_ = newData;
	}
};