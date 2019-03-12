#include "Layer.h"
#include <exception>
#include <string.h>
#include <random>
#include <time.h>
#include "math_func.h"

Layer::Layer(Layer & l)
{
  l_type = l.l_type;
  l_size = l_size;
  input_size = l.input_size;
  bias = l.bias;
  if (weights != nullptr)
  {
    for (size_t i = 0; i < l_size; ++i)
    {
      delete[] weights[i];
    }
    delete[] weights;
  }
  if (layer != nullptr)
    delete[] layer;
  layer = new Neuron[l_size];
  weights = new double *[l_size];
  for (size_t i = 0; i < l_size; ++i)
  {
    layer[i] = l[i];
    weights[i] = new double[input_size];
  }

  SetWeights(l.GetWeights(), l_size, input_size);
}

Layer::Layer(const Layer_Type type, const Activation_Func_Type n_type, const size_t l_size, const size_t inp_size)
{
  l_type = type;
  this->l_size = l_size;
  input_size = inp_size;
  if (n_type == Activation_Func_Type::Bias)
    throw std::exception("Layer: wrong Neurons type.");
  if (l_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: too small layer size.");
  if (input_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: wrong layer type or input size.");
  std::srand(time(nullptr));

  layer = new Neuron[l_size]; // last neuron is bias
  weights = new double *[l_size];
  input = new double[input_size];
  memset(input, 0, input_size);

  for (size_t i = 0; i < l_size; ++i)
  {
    layer[i] = Neuron(n_type);
    weights[i] = new double[input_size];
    for (size_t j = 0; j < input_size; ++j)
    {
      weights[i][j] = double(std::rand()) / (double(RAND_MAX) + 1.0);
    }
  }
}

Neuron & Layer::operator[](const size_t index)
{
  if (layer == nullptr)
    throw std::exception("Layer: layer is empty.");
  if (index >= l_size)
    throw std::exception("Layer: index too big.");
  return layer[index];
}

void Layer::SetWeights(const double ** w, const size_t l, const size_t i)
{
  if (i != input_size || l != l_size)
    throw std::exception("Layer: different sizes.");

  memcpy(weights, w, l_size * input_size * sizeof(double));
}

void Layer::SetNeuronType(const size_t index, const Activation_Func_Type n_type)
{
  if (index >= l_size)
    throw std::exception("Layer: index too big.");

  layer[index].SetType(n_type);
}

void Layer::SetInput(const double *data, const size_t len)
{
  if (len != input_size)
    throw std::exception("Layer: wrong input size.");
  if (input_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: wrong layer type or input size.");

  memcpy(input, data, input_size * sizeof(double));
}

double ** Layer::GetWeights()
{
  return weights;
}

void Layer::GetResult(double *ret, size_t &i)
{
  if (i != l_size)
    throw std::exception("Layer: wrong input size");

  for (size_t j = 0; j < l_size; ++j)
  {
    ret[j] = layer[j].GetResult();
  }
}

void Layer::Calculate()
{
  if (l_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: layer size is less then 2.");
  if (input_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: input size too small.");
  if (weights == nullptr || layer == nullptr || input == nullptr)
    throw std::exception("Layer: empty array.");

  for (size_t i = 0; i < l_size; ++i)
  {
    layer[i].Activate(weighted_sum(input, weights[i], input_size));
  }
}

void Layer::UseBias(const bool use)
{
  if (l_size < MINIMAL_LAYER_SIZE)
    throw std::exception("Layer: layer size is less then 2.");
  bias = use;
  layer[l_size - 1].SetType(use ? Activation_Func_Type::Bias : layer[l_size - 2].GetType() );
}

Layer::~Layer()
{
  delete[] layer;
  for (size_t i = 0; i < l_size; ++i)
  {
    delete[] weights[i];
  }
  delete[] weights;
}
