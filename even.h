﻿#pragma once

// С применением взятия остатка
// Плюсы: простота, читаемость
// Минусы: дорогая операция деления
bool isEven_mod(int value)
{
	return value % 2 == 0;
}

// С применением побитового and
// Плюсы: быстрая побитовая операция, проверяем только последний бит числа
// Минусы: таким образом можно проверить только делимость на степень числа 2
bool isEven_bit(int value)
{
	return (value & 1) == 0;
}