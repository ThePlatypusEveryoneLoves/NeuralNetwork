#include "Layer.h"
#include <numeric>
#include <algorithm>

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
    std::vector<double> ColumnTemp;
    std::vector<double> Temp(OutputSize);

    for (int i = 0; i < OutputSize; i++) {
        Temp[i] = ReLU(std::inner_product(input.begin(), input.end(), weights[i].begin(), bias[i]));

    }

    input = Temp;
}

void Layer::InnerCalculateOutputs(Matrix1D& input, LayerInfo& output) {
    std::vector<double> ColumnTemp;

    for (int i = 0; i < OutputSize; i++) {
        output.Activations[i] = ReLU((output.WeightedInputs[i] = std::inner_product(input.begin(), input.end(), weights[i].begin(), 0.0)) + bias[i]);

    }

    input = output.Activations;
}

Layer::Layer(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
    CheckNonJagged(WeightIn, BiasIn);
    weights = WeightIn;
    bias = BiasIn;
}

Layer::Layer(size_t IInputSize, size_t IOutputSize) {
    if (IInputSize < 1 || IOutputSize < 1) {
        throw std::domain_error("Layer size must be above zero");
    }
    InputSize = IInputSize;
    OutputSize = IOutputSize;
    weights.resize(OutputSize, std::vector<double>(InputSize));
    bias.resize(OutputSize);
}

void Layer::SetAll(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
    CheckNonJagged(WeightIn, BiasIn);
    weights = WeightIn;
    bias = BiasIn;
}

void Layer::CalculateOutputs(Matrix1D& input) {
    if (input.size() != InputSize) {

        throw std::length_error("Length of input isn't as specified in constructor");
    }

    InnerCalculateOutputs(input);
}