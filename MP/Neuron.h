#pragma once

#include "Activation_Functions/activation_functions.h"

enum class Activation_Func_Type
{
	ReLU,
	LeakyReLu,
	Tanh,
	Bias
};

class Neuron
{
private:
	Activation_Func_Type type;
	double value = 0;
	double result = 0;
	double a = 0.01;
public:
	Neuron() {}
	Neuron(const Activation_Func_Type act);
	double GetResult() { return result; }
	void Activate(const double x);
	void SetType(const Activation_Func_Type t) { type = t; }
	void SetAlpha(const double a) { this->a = a; }
	Activation_Func_Type GetType() { return type; }
	double GetDerivative();
	~Neuron();
};

