#include "Neuron.h"
#include "Activation_Functions/activation_functions.h"
#include <assert.h>


Neuron::Neuron(const Activation_Func_Type act)
{
  type = act;
}

void Neuron::Activate(const double x)
{
  switch (type)
  {
  case Activation_Func_Type::ReLU:
    result = ReLu(x);
  case Activation_Func_Type::LeakyReLu:
    result = Leaky_ReLu(x, a);
  case Activation_Func_Type::Tanh:
    result = Tanh(x, a);
  case Activation_Func_Type::Bias:
    result = x;
    break;
  default:
    assert(false);
    break;
  }
}

double Neuron::GetDerivative()
{
  switch (type)
  {
    case Activation_Func_Type::ReLU:
      return Derivative_ReLu(result);
    case Activation_Func_Type::LeakyReLu:
      return Derivative_Leaky_ReLu(result);
    case Activation_Func_Type::Tanh:
      return Derivative_Tanh(result, a);
    case Activation_Func_Type::Bias:
      assert(false);
      break;
    default:
      assert(false);
      break;
  }
  return 0.0;
}


Neuron::~Neuron()
{
}
