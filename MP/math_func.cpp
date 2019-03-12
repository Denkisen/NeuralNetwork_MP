#pragma once
#include <exception>
#include "math_func.h"

double weighted_sum(const double *data, const double *weights, size_t len)
{
	if (data == nullptr || weights == nullptr)
		throw std::exception("weighted_sum: array is empty.");

	double ret = 0;
	for (size_t i = 0; i < len; ++i)
	{
		ret += data[i] * weights[i];
	}
	return ret;
}