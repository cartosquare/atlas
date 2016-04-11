#ifndef __cost__functions__hpp__
#define __cost__functions__hpp__

#include <cmath>

namespace atlas {
    static double sigmoid(double z) {
        return (1.0 / (1.0 + std::exp(-z)));
    }
    
    static double sigmoid_prime(double z) {
        return (sigmoid(z) * (1 - sigmoid(z)));
    }
}

#endif