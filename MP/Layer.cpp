#include "Layer.h"
#include <assert.h>
#include <string.h>


Layer::Layer(const Layer_Type type, const Activation_Func_Type neuron_act, const size_t layer_size, const bool enable_biases)
{
	assert(layer_size > 0);
	this->type = type;
	this->layer_size = layer_size;
	this->bias = enable_biases;
	layer = new Neuron[layer_size]();
	for (size_t i = 0; i < layer_size; ++i)
		layer[i] = Neuron(neuron_act);
}

void Layer::Set_Left(Layer & l)
{
	assert(l.Get_Neurons_Count() > 0);
	if (weights != nullptr && l.Get_Neurons_Count() != input_size)
		assert(false);
	input_size = l.Get_Neurons_Count();
	left = &l;
	if (inputs != nullptr)
		delete[] inputs;
	inputs = new double[input_size];
}

void Layer::Activate()
{
	assert(weights != nullptr);
	assert(inputs != nullptr);
	assert(left != nullptr);

	for (size_t i = 0; i < input_size; ++i)
	{
		inputs[i] = left->layer[i].Get_Result();
	}
	double tmp = 0;
	for (size_t i = 0; i < layer_size; ++i)
	{
		tmp = 0;
		for (size_t j = 0; j < input_size; ++j)
		{
			tmp += inputs[j] * weights[i][j];
		}
		layer[i].Activate(tmp);
	}

}

void Layer::Set_Weights(const double ** w, const size_t layer_size, const size_t input_size)
{
	assert(w != nullptr);
	assert(layer_size == this->layer_size);
	assert(input_size > 0);
	
	if (weights != nullptr)
	{
		if (input_size != this->input_size)
		{
			for (size_t i = 0; i < layer_size; ++i)
				delete[] weights[i];
			delete[] weights;

			this->input_size = input_size;
			weights = new double*[layer_size];
			for (size_t i = 0; i < layer_size; ++i)
			{
				weights[i] = new double[input_size];
			}
		}
	} 
	else
	{
		this->input_size = input_size;
		weights = new double*[layer_size];
		for (size_t i = 0; i < layer_size; ++i)
		{
			weights[i] = new double[input_size];
		}
	}

	memcpy_s(weights, sizeof(double) * this->layer_size * this->input_size, w, sizeof(double) * layer_size * input_size);
}

double * Layer::Get_Neuron_Weights(const size_t index)
{
	assert(index < layer_size);
	return weights[index];
}

double Layer::operator[](size_t index)
{
	assert(index < layer_size);
	return layer[index].Get_Result();
}


Layer::~Layer()
{
	if (weights != nullptr)
	{
		for (size_t i = 0; i < layer_size; ++i)
			delete[] weights[i];
		delete[] weights;
	}
	if (layer != nullptr)
		delete[] layer;
	if (inputs != nullptr)
		delete[] inputs;
}
