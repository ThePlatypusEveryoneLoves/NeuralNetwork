#include "Network.h"
#include <cassert>

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