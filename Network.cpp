#include "Network.h"
#include <vector>
#include <algorithm>

template<size_t start, size_t middle, size_t... ending>
NeuralNetwork<start,middle,ending...>::NeuralNetwork(){
    for (size_t i = 0; i < LayerSizes.size() - 1; i++) {
		Layers[i] = Layer(LayerSizes[i],LayerSizes[i + 1]);
	}
}

template<size_t start, size_t middle, size_t... ending>
void NeuralNetwork<start,middle,ending...>::CalculateOutputs(Matrix1D& Input) {
    if (Input.size() != InputSize) {
        throw std::length_error("Input size is not as declared");
    }
    Input.resize(*std::max_element(LayerSizes.begin(),LayerSizes.end()));
    std::cout<<Input.size()<<"\n";

    for (Layer x : Layers) {
        x.InnerCalculateOutputs(Input);
    }
    Input.resize(LayerSizes.back());

}

template<size_t start, size_t middle, size_t... ending>
Layer& NeuralNetwork<start,middle,ending...>::GetLayer(size_t index) {
    if (index > Layers.size()) {
        throw std::out_of_range("Outside of layer range");
    }
    else {
        return Layers[index];
    }
}