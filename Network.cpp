#include "Layer.cpp"
#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include <concepts>
#include <algorithm>

template<size_t start, size_t middle, size_t... ending>  //!second ending if more then two layers
struct NeuralNetwork {
	using Matrix2D = std::vector<std::vector<double>>;
	using Matrix1D = std::vector<double>;
	friend Layer;
	/*
	!the following line may depend on "smart" compilers
	!that can make the "+2" a constexpr
	TODO: Make a non "smart compiler" version of this
	 */
	std::array<Layer,sizeof...(ending)+1> Layers {}; 
	std::array<size_t,sizeof...(ending)+2> LayerSizes{start, middle, (ending)... };
	size_t InputSize = start;
	size_t OutputSize { };
	NeuralNetwork() {
		
		for (size_t i = 0; i < LayerSizes.size() - 1; i++) {
			Layers[i] = Layer(LayerSizes[i],LayerSizes[i + 1]);
		}
		
	}
	void CalculateOutputs(Matrix1D& Input) {
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
	Layer& GetLayer(size_t index) {
		if (index > Layers.size()) {
			throw std::out_of_range("Outside of layer range");
		}
		else {
			return Layers[index];
		}
	}
	void Backprogration();
};


int main() {
	NeuralNetwork<3,1> network;
	 std::vector<double> l{
		1,2,3 };
	network.CalculateOutputs(l);
	std::cout<<l[0]<<"\n";
	 assert(l == std::vector<double>{0});
	 
	
	// l = {1,1,1};
    /*
	    Layer MyLayer(
	                        {
	                            {1,1,1,1},
	                            {2,2,2,2},
	                            {3,3,3,3}
	                        },
	                        {-1,1,-1,1}
	                    );
	                   
	   
	    MyLayer.CalculateOutputs(l);
	   for(auto x:l){
	        std::cout<<x<<std::endl;
	    }
	
	std::vector<Layer> ll(10, Layer({ {} }, {}));
	ll[0].SetAll({ {1,1,1,1},{2,2,2,2},{3,3,3,3} }, { 0,0,0,0 });
     
	    MyLayer.SetAll(
	                        {
	                            {1,1,1,1},
	                            {2,2,2,2},
	                            {3,3,3,3}
	                        },
	                        {1,-1,1,-1}
	                    );
	                    
	l = { 1,2,3 };
	ll[0].CalculateOutputs(l);
	for (auto x : l) {
		std::cout << x << std::endl;
	}*/
}