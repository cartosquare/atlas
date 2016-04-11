#ifndef __neural__network__hpp__
#define __neural__network__hpp__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/random.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <vector>

typedef boost::numeric::ublas::vector<double> Vector;
typedef boost::numeric::ublas::vector<int> Labels;
typedef boost::numeric::ublas::matrix<double> Matrix;

namespace atlas {
    class NeuralNetwork {
    public:
        // 输入每一层的神经元的个数来初始化神经网络
        // 如，sizes = { 2, 3, 1}
        // 表示 神经元网络有三层，每层的神经元个数分别是2， 3， 1个
        NeuralNetwork(std::vector<int> sizes);
        
        NeuralNetwork(std::string model);
        
        ~NeuralNetwork() {}
        
        // 学习
        void learning(const std::vector<Vector>& training_data,         // 训练样本
                      const std::vector<Labels>& ground_truth,          // 训练样本的标签
                      const int epochs,                                 // 迭代次数
                      const int mini_batch_size,                        // 最小采样大小
                      double eta,                                       // 学习速率
                      const std::vector<Vector>& test_data,
                      const std::vector<Labels>& test_data_ground_truth
                      );
        
        
        // 使用采样的样本集更新训练参数
        void update_mini_batch(const std::vector<Vector>& training_data,
                               const std::vector<Labels>& ground_truth,
                               const std::vector<int>& sample_idx,
                               const int sample_start,
                               const int sample_end,
                               double learning_rate);
        
        // 后向传播计算每个训练参数的偏导
        void backprop(const Vector& sample,                                 // 采样样本
                      const Labels& label,                                      // 采样样本的标签
                      std::vector<Vector>& delta_nabla_b,                   // b 的偏导
                      std::vector<Matrix>& delta_nabla_w                    // w 的偏导
                      );
        
        // 代价函数相对于神经元输出的导数
        inline Vector cost_derivative(const Vector& activations, const Labels& labels) {
            return (activations - labels);
        }
        
        void shuffle(int size, std::vector<int>& random_order);
        
        int evaluate(const std::vector<Vector>& test_data,
                    const std::vector<Labels>& test_data_ground_truth);
        
        Vector feed_forward(const Vector& input);
        
        void print_info();
        
        void save_model(std::string filename);
    private:
        // 两个向量的 hadamard product
        inline Vector hadamard_product(const Vector& v1, const Vector& v2) {
            if (v1.size() != v2.size()) {
                std::cout << "inconsist!\n";
            }
            Vector v(v1.size());
            for (size_t i = 0; i < v1.size(); ++i) {
                v(i) = v1(i) * v2(i);
            }
            return v;
        }
        
        // 向量转换为矩阵
        inline Matrix to_matrix(const Vector& v, bool row_vector) {
            if (row_vector) {
                // 行向量
                Matrix matrix(1, v.size());
                for (size_t i = 0; i < v.size(); ++i) {
                    matrix(0, i) = v(i);
                }
                return matrix;
            } else {
                // 列向量
                Matrix matrix(v.size(), 1);
                for (size_t i = 0; i < v.size(); ++i) {
                    matrix(i, 0) = v(i);
                }
                return matrix;
            }
        }
        
        inline int argmarx(const Vector& v) {
            double max = v(0);
            int max_index = 0;
            for (size_t i = 1; i < v.size(); ++i) {
                if (max < v(i)) {
                    max = v(i);
                    max_index = i;
                }
            }
            return max_index;
        }
        
        inline int argmarx(const Labels& v) {
            double max = v(0);
            int max_index = 0;
            for (size_t i = 1; i < v.size(); ++i) {
                if (max < v(i)) {
                    max = v(i);
                    max_index = i;
                }
            }
            return max_index;
        }
        
    private:
        // boost::mt19937 random_gen_;
        boost::mt11213b random_gen_;
        
        int nlayers_;
        std::vector<int> sizes_;
        std::vector<Vector> biases_;
        std::vector<Matrix> weights_;
    };
}
#endif