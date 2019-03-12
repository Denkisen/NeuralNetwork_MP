#pragma once
#include "Neuron.h"

#define MINIMAL_LAYER_SIZE 3

enum class Layer_Type
{
	Input,
	Hidden,
	Output
};

class Layer
{
protected:
	Layer_Type l_type = Layer_Type::Hidden;
	size_t l_size = 0;
	double **weights = nullptr;
	size_t input_size = 0;
	double *input = nullptr;
	Neuron *layer = nullptr;
	bool bias = true;
public:
	Layer() = delete;
	Layer(Layer &l);
	Layer(const Layer_Type type, 
		const Activation_Func_Type n_type, 
		const size_t l_size, 
		const size_t inp_size);
	~Layer();
	Layer &operator= (const Layer &l) = delete;
	Neuron &operator[] (const size_t index);
	void SetWeights(const double **w,const size_t l,const size_t i);
	void SetNeuronType(const size_t index, const Activation_Func_Type n_type);
	double ** GetWeights();
	void GetResult(double *ret, size_t &i);
	void Calculate();
	void UseBias(const bool use);
};

