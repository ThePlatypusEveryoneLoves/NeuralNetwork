#include "Layer.h"
#include <numeric>
#include <algorithm>
#include <span>
#include <random>

//!Private:
void Layer::CheckNonJagged(const Matrix2D& input1, const Matrix1D& input2) {
    OutputSize = input1.size();
    InputSize = input1[0].size();
    for (int i = 1; i < input1.size(); i++) {
        if (InputSize != input1[i].size()) {
            throw std::length_error("Vectors are jagged");
        }
    }
    if (OutputSize != input2.size()) {
        throw std::length_error("Bias is not the same as output size");
    }
}
void Layer::InnerCalculateOutputs(Matrix1D& input){
    // todo:Make the weights turned 90 degrees
    std::vector<double> Temp(OutputSize);
    auto WeightInput = weights.begin();
    for (int i = 0; i < OutputSize; i++) {

        Temp[i] = ReLU(std::inner_product(input.begin(), input.end(), WeightInput, bias[i]));
        WeightInput += InputSize;

    }

    input = Temp;
}

void Layer::InnerCalculateOutputs(Matrix1D& input, LayerInfo& output) {

    auto WeightInput = weights.begin();
    for (int i = 0; i < OutputSize; i++) {
        output.Activations[i] = ReLU((output.WeightedInputs[i] = std::inner_product(input.begin(), input.end(), WeightInput, 0.0)) + bias[i]);
        WeightInput += InputSize;

    }

    input = output.Activations;
}
Matrix1D Layer::Flatten(const Matrix2D& input){
    Matrix1D temp;
    for (auto i : input)
    {
        temp.insert(temp.end(), i.begin(), i.end());
    }
    return temp;
    
}
//!Public:

Layer::Layer(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
    CheckNonJagged(WeightIn, BiasIn);
    weights = Flatten(WeightIn);
    bias = BiasIn;
}

Layer::Layer(size_t IInputSize, size_t IOutputSize) {
    if (IInputSize < 1 || IOutputSize < 1) {
        throw std::domain_error("Layer size must be above zero");
    }
    InputSize = IInputSize;
    OutputSize = IOutputSize;
    weights.resize(OutputSize * InputSize);
    bias.resize(OutputSize);
}

void Layer::SetAll(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
    CheckNonJagged(WeightIn, BiasIn);
    weights = Flatten(WeightIn);
    bias = BiasIn;
}

void Layer::CalculateOutputs(Matrix1D& input) {
    if (input.size() != InputSize) {

        throw std::length_error("Length of input isn't as specified in constructor");
    }

    InnerCalculateOutputs(input);
}

void Layer::Randomize(){
    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> uniform_dist(-1.0 ,1.0);
    for (auto &i : weights){
        i = uniform_dist(e1);
    }
    for (auto &i : bias){
        i = uniform_dist(e1);
    }
}

Layer::Layer(Matrix1D IWeights, Matrix1D IBias, size_t IInputSize, size_t IOutputSize){
    InputSize = IInputSize;
    OutputSize == IOutputSize;

    if (!(IWeights.size() == (InputSize * OutputSize))){
        throw std::length_error("Length of weights isn't as specified in argument (#3 * #4)"); 
    }
    weights = IWeights;

    if (!(IBias.size() == OutputSize)){
        throw std::length_error("Length of bias isn't as specified in argument (#4)"); 
    }
    bias = IBias;
}