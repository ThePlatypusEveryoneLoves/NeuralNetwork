#include<stdexcept>
#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include <cassert>
struct Layer {
private:
	using Matrix2D = std::vector<std::vector<double>>;
	using Matrix1D = std::vector<double>;
	Matrix2D weights;

	std::vector<double> bias;

	size_t OutputSize;
	size_t InputSize;

	void CheckNonJagged(const Matrix2D& input1, const Matrix1D& input2) {
		OutputSize = input1[0].size();
		InputSize = input1.size();
		for (int i = 1; i < input1.size(); i++) {
			if (OutputSize != input1[i].size()) {
				throw std::length_error("Vectors are jagged");
			}
		}
		if (OutputSize != input2.size()) {
			throw std::length_error("Bias is not the same as output size");
		}
	}

public:
	Layer() = default;
	Layer(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
		CheckNonJagged(WeightIn, BiasIn);
		weights = WeightIn;
		bias = BiasIn;
	}

	Layer(size_t IInputSize, size_t IOutputSize) {
		if (IInputSize < 1 || IOutputSize < 1) {
			throw std::domain_error("Layer size must be above zero");
		}
		InputSize = IInputSize;
		OutputSize = IOutputSize;
		weights.resize(InputSize, std::vector<double>(OutputSize));
		bias.resize(OutputSize);
	}

	void SetAll(const Matrix2D& WeightIn, const Matrix1D& BiasIn) {
		CheckNonJagged(WeightIn, BiasIn);
		weights = WeightIn;
		bias = BiasIn;
	}

	void CalculateOutputs(Matrix1D& input) {



		if (input.size() != InputSize) {

			throw std::length_error("Length of input isn't as specified in constructor");
		}


		auto extract_column = [](const Matrix2D& matrix, int col_idx) {
			std::vector<double> result;
			for (const auto& row : matrix) {
				result.push_back(row[col_idx]);
			}
			return result;
		};

		std::vector<double> ColumnTemp;
		std::vector<double> Temp(OutputSize);

		for (int i = 0; i < OutputSize; i++) {
			ColumnTemp = extract_column(weights, i);
			assert(input.size() == ColumnTemp.size());
			Temp[i] = (std::inner_product(input.begin(), input.end(), ColumnTemp.begin(), bias[i]));

		}

		input = Temp;
	}
};



