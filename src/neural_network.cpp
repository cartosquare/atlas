#include "neural_network.hpp"
#include "cost_functions.hpp"
#include <fstream>

namespace atlas {
    NeuralNetwork::NeuralNetwork(std::vector<int> sizes) : nlayers_(sizes.size()), sizes_(sizes) {
        random_gen_ = boost::mt11213b(time(0));
        
        // 高斯分布生成器
        boost::normal_distribution<> nd(0.0, 1.0);
        boost::variate_generator<boost::mt11213b&, boost::normal_distribution<>> var_gen(random_gen_, nd);
        
        // 初始化基向量
        for (size_t i = 1; i < sizes_.size(); ++i) {
            // 每一层都有一个基向量，向量中的元素对应这一层的每一个神经元
            Vector biases(sizes_[i]);
            for (int j = 0; j < sizes_[i]; ++j) {
                biases(j) = var_gen();
            }
            biases_.push_back(biases);
        }
        
        // 初始化权重向量
        for (size_t i = 0; i < sizes_.size() - 1; ++i) {
            // 相邻两个层之间都有一个权重矩阵，如果第 i 层和第 i + 1 层分别有 m 和 n 个神经元，
            // 那么两层之间的权重矩阵的维度为 m * n
            Matrix weights(sizes_[i + 1], sizes_[i]);
            for (int row = 0; row < sizes_[i + 1]; ++row) {
                for (int col = 0; col < sizes_[i]; ++ col) {
                    weights(row, col) = var_gen();
                }
            }
            weights_.push_back(weights);
        }
        
        if (biases_.size() != weights_.size()) {
            std::cout << "Biases and weights size not equal!";
        }
    }
    
    NeuralNetwork::NeuralNetwork(std::string model) {
        std::ifstream ifs(model.c_str());
        if (ifs.is_open()) {
            ifs >> nlayers_;
            
            sizes_.resize(nlayers_);
            for (int i = 0; i < nlayers_; ++i) {
                ifs >> sizes_[i];
            }
            
            // biases
            biases_.resize(sizes_.size() - 1);
            for (size_t i = 0; i < biases_.size(); ++i) {
                ifs >> biases_[i];
            }
            
            // weights
            weights_.resize(sizes_.size() - 1);
            for (size_t i = 0; i < weights_.size(); ++i) {
                ifs >> weights_[i];
            }
            
            ifs.close();
            
            if (biases_.size() != weights_.size()) {
                std::cout << "Biases and weights size not equal!";
            }
        }
    }
    
    void NeuralNetwork::save_model(std::string filename) {
        std::ofstream ofs(filename.c_str());
        if (ofs.is_open()) {
            ofs << nlayers_ << std::endl;
            for (size_t i = 0; i < sizes_.size(); ++i) {
                ofs << sizes_[i] << "\t";
            }
            ofs << std::endl;
            
            // biases
            for (size_t i = 0; i < biases_.size(); ++i) {
                ofs << biases_[i] << std::endl;
            }
            
            // weights
            for (size_t i = 0; i < weights_.size() ; ++i) {
                ofs << weights_[i] << std::endl;
            }
            
            ofs.close();
        }
    }
    
    void NeuralNetwork::learning(const std::vector<Vector>& training_data,
                                 const std::vector<Labels>& ground_truth,
                                 const int epochs,
                                 const int mini_batch_size,
                                 double eta,
                                 const std::vector<Vector>& test_data,
                                 const std::vector<Labels>& test_data_ground_truth) {
        
        int test_data_size = test_data.size();
        for (int i = 0; i < epochs; ++i) {
            // 每次学习场景之前，对训练向量进行随机排序
            // 每一次场景都会进行多次抽样学习，直到所有的训练样本在一次场景中都被学习过
            std::vector<int> random_order;
            this->shuffle(training_data.size(), random_order);
            
            int training_data_size = training_data.size();
            for (int j = 0; j < training_data_size; j += mini_batch_size) {
                // 确定抽样的样本
                int sample_start = j;
                int sample_end = sample_start + mini_batch_size;
                if (sample_end >= training_data_size) {
                    sample_end = training_data_size;
                }
                
                // 进行一次学习
                this->update_mini_batch(training_data, ground_truth,
                                        random_order, sample_start, sample_end, eta);
                
            }
            // 如果测试集不为空的话，每一次场景学习后都会进行一次测试
            if (test_data_size > 0) {
                std::cout << "Epoch " << i << ": " << this->evaluate(test_data, test_data_ground_truth) << " / " << test_data_size << std::endl;
            }
            
            std::cout << "Epoch " << i << " completed.\n";
            
        }
    }
    
    void NeuralNetwork::shuffle(int size, std::vector<int>& random_order) {
        random_order.clear();
        random_order.push_back(0);
        
        for (int i = 1; i < size; ++i) {
            boost::random::uniform_int_distribution<> dist(0, i - 1);
            int idx = dist(random_gen_);
            int tmp = random_order[idx];
            random_order[idx] = i;
            random_order.push_back(tmp);
        }
    }
    
    void NeuralNetwork::update_mini_batch(const std::vector<Vector>& training_data,
                                          const std::vector<Labels>& ground_truth,
                                          const std::vector<int>& sample_idx,
                                          const int sample_start, const int sample_end,
                                          double learning_rate) {
        std::vector<Vector> nabla_b = biases_;
        for (size_t i = 0; i < biases_.size(); ++i) {
            for (size_t j = 0; j < biases_[i].size(); ++j) {
                nabla_b[i](j) = 0;
            }
        }
        
        std::vector<Matrix> nabla_w = weights_;
        
        for (size_t i = 0; i < weights_.size(); ++i) {
            for (size_t m = 0; m < weights_[i].size1(); ++m) {
                for (size_t n = 0; n < weights_[i].size2(); ++n) {
                    nabla_w[i](m, n) = 0;
                }
            }
        }
        
        
        // 计算每一个样本的偏导
        for (int i = sample_start; i < sample_end; ++i) {
            std::vector<Vector> delta_nabla_b; // 基的偏导
            std::vector<Matrix> delta_nabla_w; // 权重的偏导
            this->backprop(training_data[sample_idx[i]], ground_truth[sample_idx[i]], delta_nabla_b, delta_nabla_w);
            
            for (size_t j = 0; j < nabla_b.size(); ++j) {
                nabla_b[j] += delta_nabla_b[j];
                nabla_w[j] += delta_nabla_w[j];
            }
        }
        
        // 更新基和权重；使用所有子集的偏导的平均。
        int sample_size = (sample_end - sample_start);
        for (size_t i = 0; i < nabla_b.size(); ++i) {
            weights_[i] = weights_[i] - (learning_rate / sample_size) * nabla_w[i];
            
            biases_[i] = biases_[i] - (learning_rate / sample_size) * nabla_b[i];
            
        }
    }
    
    void NeuralNetwork::backprop(const Vector& sample, const Labels& label,
                                 std::vector<Vector>& delta_nabla_b,
                                 std::vector<Matrix>& delta_nabla_w) {
        delta_nabla_b = biases_;
        delta_nabla_w = weights_;
        for (size_t i = 0; i < biases_.size(); ++i) {
            for (size_t j = 0; j < biases_[i].size(); ++j) {
                delta_nabla_b[i](j) = 0;
            }
        }
        for (size_t i = 0; i < weights_.size(); ++i) {
            for (size_t m = 0; m < weights_[i].size1(); ++m) {
                for (size_t n = 0; n < weights_[i].size2(); ++n) {
                    delta_nabla_w[i](m, n) = 0;
                }
            }
        }
        
        
        // feedforward: 前向求加权输入和激活输出
        Vector activation = sample;
        
        // 所有层的激活输出
        std::vector<Vector> activations = { activation };
        // 所有层的加权输入
        std::vector<Vector> zs;
        
        for (size_t i = 0; i < biases_.size(); ++i) {
            // 计算加权输入
            Vector z = boost::numeric::ublas::prod(weights_[i], activation) + biases_[i];
            zs.emplace_back(z);
            
            // 计算激活输出
            Vector new_activation(z.size());
            for (size_t j = 0; j < z.size(); ++j) {
                new_activation(j) = sigmoid(z(j));
            }
            activations.emplace_back(new_activation);
            activation  = new_activation;
        }
        
        // backward pass: 后向传播，计算偏导
        //int layers = nlayers_ - 1;
        
        // 首先计算输出层的偏导
        Vector derivatives = this->cost_derivative(activations[activations.size() - 1], label);
        
        Vector primes(zs[zs.size() - 1].size());
        for (size_t j = 0; j < zs[zs.size() - 1].size(); ++j) {
            primes(j) = sigmoid_prime(zs[zs.size() - 1][j]);
        }
        // 先算出中间值 delta
        Vector delta = this->hadamard_product(derivatives, primes);
        
        // 输出层的基的偏导
        delta_nabla_b[delta_nabla_b.size() - 1] = delta;
        // 输出层的权重的偏导
        delta_nabla_w[delta_nabla_w.size() - 1] = boost::numeric::ublas::prod(to_matrix(delta, false), to_matrix(activations[activations.size() - 2], true));
        
        for (int i = 2; i < nlayers_; ++i) {
            // 先算出中间值 delta
            Vector primes(zs[zs.size() - i].size());
            for (size_t j = 0; j < zs[zs.size() - i].size(); ++j) {
                primes(j) = sigmoid_prime(zs[zs.size() - i][j]);
            }
            
            Matrix weight_transpose = boost::numeric::ublas::trans(weights_[weights_.size() - i + 1]);
            delta = this->hadamard_product(boost::numeric::ublas::prod(weight_transpose, delta), primes);
            
            // 输出层的基和权重的偏导
            delta_nabla_b[delta_nabla_b.size() - i] = delta;
            delta_nabla_w[delta_nabla_w.size() - i] = boost::numeric::ublas::prod(to_matrix(delta, false), to_matrix(activations[activations.size() - i - 1], true));
        }
    }
    
    int NeuralNetwork::evaluate(const std::vector<Vector>& test_data,
                const std::vector<Labels>& test_data_ground_truth) {
        int success = 0;
        for (size_t i = 0; i < test_data.size(); ++i) {
            int label = this->argmarx(this->feed_forward(test_data[i]));
            int truth = this->argmarx(test_data_ground_truth[i]);
            if(label == truth) {
                ++success;
            }
        }
        return success;
    }
    
    Vector NeuralNetwork::feed_forward(const Vector& input) {
        Vector ouput = input;
        for (size_t i = 0; i < biases_.size(); ++i) {
            ouput = boost::numeric::ublas::prod(weights_[i], ouput) + biases_[i];
            for (size_t j = 0; j < ouput.size(); ++j) {
                ouput(j) = sigmoid(ouput(j));
            }
        }
        return ouput;
    }
    
    void NeuralNetwork::print_info() {
        std::cout << "biases: \n";
        for (size_t i = 0; i < biases_.size(); ++i) {
            std::cout << biases_[i] << std::endl;
        }
        
        std::cout << "weights: \n";
        for (size_t i = 0; i < weights_.size(); ++i) {
            std::cout << weights_[i] << std::endl;
        }
    }
}
