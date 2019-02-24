#pragma once
#include "Neuron.h"

enum class Layer_Type
{
	Input,
	Hidden,
	Output
};

class Layer
{
private:
	Layer_Type type;
	Neuron *layer = nullptr;
	size_t layer_size = 0;
	double *inputs = nullptr;
	size_t input_size = 0;
	double **weights = nullptr;  // x -layer_size ; y - input_size
	bool bias = true;
	Layer *left = nullptr;
public:
	Layer() = delete;
	Layer & operator=(Layer &l) = delete;
	Layer(Layer &val) = delete;

	Layer(const Layer_Type type, 
		  const Activation_Func_Type neuron_act, 
		  const size_t layer_size, 
		  const bool enable_biases = true);
	void Set_Left(Layer &l);
	void Activate();
	void Set_Weights(const double **w, const size_t index, const size_t priv_layer_count);
	double *Get_Neuron_Weights(const size_t index);
	size_t Get_Neurons_Count() { return layer_size; }
	double operator[] (size_t index);

	~Layer();
};

