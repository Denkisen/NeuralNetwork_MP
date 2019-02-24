#include "activation_functions.h"



double ReLu(double x)
{
	return x <= 0 ? 0 : x;
}

double Derivative_ReLu(double x)
{
	return x;
}

double Leaky_ReLu(double x, double a = 0.01)
{
	return x < 0 ? x * a : x;
}

double Derivative_Leaky_ReLu(double x)
{
	return x;
}