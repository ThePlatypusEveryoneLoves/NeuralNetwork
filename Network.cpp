#include "Layer.cpp"
#include <vector>

struct NeuralNetwork {
	using Matrix2D = std::vector<std::vector<double>>;
	using Matrix1D = std::vector<double>;
	friend Layer;
	std::vector<Layer> Layers;
	size_t InputSize;
	NeuralNetwork(std::vector<size_t> LayerSizes) {
		if (LayerSizes.size() < 2) {
			throw std::length_error("Must be at least 2 Layers");
		}
		InputSize = LayerSizes[0];

		for (size_t i = 0; i < LayerSizes.size() - 1; i++) {
			Layers.emplace_back(LayerSizes[i], LayerSizes[i + 1]);
		}

	}
	void CalculateOutputs(Matrix1D& Input) {
		if (Input.size() != InputSize) {
			throw std::length_error("Input size is not as declared");
		}

		for (Layer x : Layers) {
			x.CalculateOutputs(Input);
		}

	}
	Layer& GetLayer(size_t index) {
		if (index > Layers.size()) {
			throw std::out_of_range("Outside of layer range");
		}
		else {
			return Layers[index];
		}
	}
};


int main() {
	NeuralNetwork network({ 3,1 });
	std::vector<double> l{ 1,2,3 };
	network.CalculateOutputs(l);
	for (auto x : l) {
		std::cout << x << std::endl;
	}


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
	    }*/

	std::vector<Layer> ll(10, Layer({ {} }, {}));
	ll[0].SetAll({ {1,1,1,1},{2,2,2,2},{3,3,3,3} }, { 0,0,0,0 });
     /*
	    MyLayer.SetAll(
	                        {
	                            {1,1,1,1},
	                            {2,2,2,2},
	                            {3,3,3,3}
	                        },
	                        {1,-1,1,-1}
	                    );
	                    */
	l = { 1,2,3 };
	ll[0].CalculateOutputs(l);
	for (auto x : l) {
		std::cout << x << std::endl;
	}
}