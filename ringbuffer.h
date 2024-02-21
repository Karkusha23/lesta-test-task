#pragma once

// Абстрактный класс для кольцевого буфера

template<typename T>
class AbstractRingBuffer
{
public:

	// Доступ к элементу по индексу
	virtual T& operator[](int index) = 0;
	virtual T operator[](int index) const = 0;

	// Добавить элемент в буфер
	virtual void push(const T& val) = 0;

	// Удалить самый старый элемент из буфера
	virtual T pop() = 0;

	// Размер буфера
	virtual int size() const = 0;

	// Количество элементов в буфере
	virtual int count() const = 0;

	// Изменить размер буфера
	virtual void resize(int newSize) = 0;
};