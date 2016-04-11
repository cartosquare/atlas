#include "catch.hpp"
#include "neural_network.hpp"
#include "cost_functions.hpp"
#include <boost/numeric/ublas/io.hpp>
#include <fstream>
#include <stdlib.h>

TEST_CASE("neural network", "[neural network]") {
    SECTION("initialize") {
        std::vector<int> sizes = {2, 3, 1};
        atlas::NeuralNetwork network(sizes);
        network.print_info();
    }
    
    SECTION("sigmoid function") {
        std::cout << atlas::sigmoid(-1000) << std::endl;
        std::cout << atlas::sigmoid(0) << std::endl;
        std::cout << atlas::sigmoid(1000) << std::endl;
    }
    
    SECTION("transpose matrix") {
        Matrix m(2, 2);
        m(0, 0) = 0;
        m(0, 1) = 1;
        m(1, 0) = 2;
        m(1, 1) = 3;
        std::cout << m << std::endl;
        
        Matrix n = boost::numeric::ublas::trans(m);
        std::cout << m << std::endl;
        std::cout << n << std::endl;
    }
    SECTION("shuffle") {
        std::vector<int> sizes = {2, 3, 1};
        atlas::NeuralNetwork network(sizes);
        
        std::vector<int> random_order;
        network.shuffle(10, random_order);
        std::copy(random_order.begin(), random_order.end(), std::ostream_iterator<int>(std::cout, ","));
        network.shuffle(10, random_order);
        std::copy(random_order.begin(), random_order.end(), std::ostream_iterator<int>(std::cout, ","));
        network.shuffle(10, random_order);
        std::copy(random_order.begin(), random_order.end(), std::ostream_iterator<int>(std::cout, ","));
        
    }
    
    SECTION("feed forward") {
        std::vector<int> sizes = {2, 3, 1};
        atlas::NeuralNetwork network(sizes);
        network.print_info();
        
        Vector v(2);
        v(0) = 1; v(1) = 2;
        
        Vector result = network.feed_forward(v);
        std::cout << "network output = " << result << std::endl;
    }
    
    SECTION("save and load model") {
        std::vector<int> sizes = {2, 3, 1};
        atlas::NeuralNetwork network(sizes);
        network.save_model("test.model");
        network.print_info();
        
        atlas::NeuralNetwork network2("test.model");
        network2.print_info();
    }
#if 0
    
#define use_model 1
    
    SECTION("training") {
        int input = 28 * 28;
        int hiddens = 100;
        int output = 10;
        
        std::vector<int> sizes = { input, hiddens, hiddens, hiddens, output };
#if use_model
        std::cout << "use model ...\n";
        atlas::NeuralNetwork network("handwriting.model");
#else
        std::cout << "not use model ...\n";
        atlas::NeuralNetwork network(sizes);
#endif
        std::vector<Vector> training_data, test_data;
        std::vector<Labels> ground_truth, test_data_ground_truth;
        
        int eopchs = 3000;
        int mini_batch_size = 10;
        double eta = 0.1;
        
        std::vector<std::string> filenames = {"data0.txt", "data1.txt", "data2.txt", "data3.txt", "data4.txt",  "data5.txt", "data6.txt", "data7.txt", "data8.txt", "data9.txt"};
    
        // load training and test data
        for (int i = 0; i < 10; ++i) {
            std::cout << "reading file: " << filenames[i] << std::endl;
            int count = 0;
            std::ifstream file_handle(filenames[i].c_str(), std::ios::in | std::ios::binary);
            if (!file_handle) {
                std::cout << "open file fail!\n";
            } else {
                // load training data
                for (int j = 0; j < 1000; ++j) {
                //while (!file_handle.eof()) {
                    char buffer[input];
                    if (!file_handle.read(buffer, input)) {
                        std::cout << "read data fail!\n";
                        
                    } else {
                        //std::cout << count++ << std::endl;
                        bool error = false;
                        Vector t(input);
                        for (int k = 0; k < input; ++k) {
                            t(k) = atoi(&buffer[k]);
                            if (t(k) < 0 || t(k) > 255) {
                                error = true;
                            }
                            //t(k) /= 255.0;
                        }
                        
                        Labels l(output);
                        for (int k = 0; k < output; ++k) {
                            l(k) = 0;
                        }
                        l(i) = 1;
                        
                        if (!error) {
                                training_data.push_back(t);
                                ground_truth.push_back(l);
                           if (j > 500) {
                                test_data.push_back(t);
                                test_data_ground_truth.push_back(l);
                            }
                        }
                        
                    }
                }
                file_handle.close();
            }
            
            //
            
        }
        std::cout << "training size: " << training_data.size() << std::endl;
        std::cout << "training label size: " << ground_truth.size() << std::endl;
        std::cout << "testing size: " << test_data.size() << std::endl;
        std::cout << "testing label size: " << test_data_ground_truth.size() << std::endl;
        
        network.learning(training_data, ground_truth, eopchs, mini_batch_size, eta, test_data, test_data_ground_truth);
        
        network.save_model("handwriting.model");
    }
#endif
}


