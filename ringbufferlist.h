#pragma once
#include "ringbuffer.h"

// Реализация кольцевого буфера через замкнутый односвязный список
// Плюсы: быстрое изменение размера буфера, не нужно выделять память под все size элементов
// Минусы: медленный доступ к элементам, дорогостоящий переход по указателю в разные участки памяти, дополнительные расход памяти для узла списка

template<typename T>
class RingBuffer_List : public AbstractRingBuffer<T>
{
	struct Node
	{
		T val_;
		Node* next_;

		Node(const T& val, Node* next) : val_(val), next_(next) { }
	};

	Node* oldest_;
	Node* newest_;

	int size_;
	int count_;

public:

	RingBuffer_List(int size) : size_(size), oldest_(nullptr), newest_(nullptr), count_(0)
	{
		if (size <= 0)
		{
			throw "Invalid ring buffer size";
		}
	}

	~RingBuffer_List()
	{
		if (oldest_ == nullptr)
		{
			return;
		}

		Node* now = oldest_;
		Node* next;

		do
		{
			next = now->next_;
			delete now;
			now = next;
		} while (now != oldest_);
	}

	RingBuffer_List(const RingBuffer_List&) = delete;
	RingBuffer_List(RingBuffer_List&&) = delete;
	RingBuffer_List& operator=(const RingBuffer_List&) = delete;
	RingBuffer_List& operator=(RingBuffer_List&&) = delete;

	T& operator[](int index) override
	{
		if (!count_)
		{
			throw "No elements in ring buffer";
		}

		if (index < 0)
		{
			throw "Invalid index";
		}

		index %= count_;

		Node* now = oldest_;

		for (int i = 0; i < index; ++i)
		{
			now = now->next_;
		}

		return now->val_;
	}

	T operator[](int index) const override
	{
		if (!count_)
		{
			throw "No elements in ring buffer";
		}

		if (index < 0)
		{
			throw "Invalid index";
		}

		index %= count_;

		Node* now = oldest_;

		for (int i = 0; i < index; ++i)
		{
			now = now->next_;
		}

		return now->val_;
	}

	void push(const T& val) override
	{
		if (!count_)
		{
			oldest_ = newest_ = new Node(val, nullptr);
			oldest_->next_ = oldest_;
			++count_;
			return;
		}

		if (count_ < size_)
		{
			newest_->next_ = new Node(val, oldest_);
			newest_ = newest_->next_;
			++count_;
			return;
		}

		oldest_->val_ = val;
		newest_ = oldest_;
		oldest_ = oldest_->next_;
	}

	T pop() override
	{
		if (!count_)
		{
			throw "No elements in ring buffer";
		}

		if (count_ == 1)
		{
			T val = oldest_->val_;
			delete oldest_;
			oldest_ = newest_ = nullptr;
			count_ = 0;
			return val;
		}

		Node* to_delete = oldest_;
		T val = to_delete->val_;

		oldest_ = oldest_->next_;
		newest_->next_ = oldest_;

		--count_;

		delete to_delete;

		return val;
	}

	int size() const override
	{
		return size_;
	}

	int count() const override
	{
		return count_;
	}

	void resize(int newSize) override
	{
		if (newSize <= 0)
		{
			throw "Invalid ring buffer size";
		}

		if (newSize >= count_)
		{
			size_ = newSize;
			return;
		}

		int to_delete_count = count_ - newSize;
		Node* now = oldest_;
		Node* next;

		for (int i = 0; i < to_delete_count; ++i)
		{
			next = now->next_;
			delete now;
			now = next;
		}

		oldest_ = now;
		newest_->next_ = oldest_;
	}
};