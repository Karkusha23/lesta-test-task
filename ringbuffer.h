#pragma once

// ����������� ����� ��� ���������� ������

template<typename T>
class AbstractRingBuffer
{
public:

	// ������ � �������� �� �������
	virtual T& operator[](int index) = 0;
	virtual T operator[](int index) const = 0;

	// �������� ������� � �����
	virtual void push(const T& val) = 0;

	// ������� ����� ������ ������� �� ������
	virtual T pop() = 0;

	// ������ ������
	virtual int size() const = 0;

	// ���������� ��������� � ������
	virtual int count() const = 0;

	// �������� ������ ������
	virtual void resize(int newSize) = 0;
};