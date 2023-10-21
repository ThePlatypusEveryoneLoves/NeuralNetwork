#include <stdexcept>
#include <vector>
#include <algorithm>

using Matrix1D = std::vector<double>;
using Matrix2D = std::vector<Matrix1D>;
struct LayerInfo{
	std::vector<double> WeightedInputs;
	std::vector<double> Activations;
};
struct Layer {
private:
	
	Matrix1D weights;
	Matrix1D WeightedInputs;
	Matrix1D bias;
	size_t OutputSize;
	size_t InputSize;

	double inline ReLU(double x){
		return std::max<double>(0,x);
	}
	Matrix1D Flatten(const Matrix2D&);
	void CheckNonJagged(const Matrix2D&, const Matrix1D&);
	void InnerCalculateOutputs(Matrix1D&);
	void InnerCalculateOutputs(Matrix1D&, LayerInfo&);
	template<size_t start, size_t middle, size_t... ending>
	friend class NeuralNetwork;
public:
	Layer() = default;
	Layer(const Matrix2D&, const Matrix1D&);
	Layer(size_t, size_t);
	Layer(Matrix1D, Matrix1D, size_t, size_t);
	void SetAll(const Matrix2D&, const Matrix1D&);
	void CalculateOutputs(Matrix1D&);
	void CalculateOutputs(Matrix1D&, LayerInfo&);
	void Randomize();
};



