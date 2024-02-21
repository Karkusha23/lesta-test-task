#pragma once
#include <iostream>

// ����������� ����������

// ���������� �������� � ����������� ����������. ������ ���� �������� ����� 2
const int RADIXSORT_ITERATIONS = 4;

// ���������� ���, �� ������� �� ������ �������� ����������� ���������� ����������� ������� 
const int RADIXSORT_BITBLOCK = sizeof(int) * 8 / RADIXSORT_ITERATIONS;

// ���������� ������ � ����������� ����������
const int RADIXSORT_BASKETCOUNT = 1 << RADIXSORT_BITBLOCK;

// ����� ��� ����� � ����������� ����������
const int RADIXSORT_MASK = (1 << RADIXSORT_BITBLOCK) - 1;

void radix_sort(int*& arr, int size)
{
	int baskets[RADIXSORT_BASKETCOUNT];

	int* arr2 = new int[size];

	for (int k = 0; k < RADIXSORT_ITERATIONS; ++k)
	{
		for (int i = 0; i < RADIXSORT_BASKETCOUNT; ++i)
		{
			baskets[i] = 0;
		}

		for (int i = 0; i < size; ++i)
		{
			++baskets[RADIXSORT_MASK & (arr[i] >> (k * RADIXSORT_BITBLOCK))];
		}

		int count = 0;
		for (int i = 0; i < RADIXSORT_BASKETCOUNT; ++i)
		{
			int tmp = baskets[i];
			baskets[i] = count;
			count += tmp;
		}

		for (int i = 0; i < size; ++i)
		{
			arr2[baskets[RADIXSORT_MASK & (arr[i] >> (k * RADIXSORT_BITBLOCK))]++] = arr[i];
		}

		std::swap(arr, arr2);
	}

	delete[] arr2;
}