#pragma once
#include <iostream>

// Поразрядная сортировка

bool is_sorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}

	return true;
}

void radix_sort(int*& arr, int size)
{
	if (is_sorted(arr, size))
	{
		return;
	}

	// Количество итераций в поразрядной сортировке. Должно быть степенью числа 2
	int RADIXSORT_ITERATIONS = size < 50000 ? 4 : 2;

	// Количество бит, по которым на каждой итерации поразрядной сортировки формируются корзины 
	int RADIXSORT_BITBLOCK = sizeof(int) * 8 / RADIXSORT_ITERATIONS;

	// Количество корзин в поразрядной сортировке
	int RADIXSORT_BASKETCOUNT = 1 << RADIXSORT_BITBLOCK;

	// Маска для чисел в поразрядной сортировке
	int RADIXSORT_MASK = (1 << RADIXSORT_BITBLOCK) - 1;

	int* baskets = new int[RADIXSORT_BASKETCOUNT];

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

	delete[] baskets;
	delete[] arr2;
}