#pragma once
#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator(int min, int max)
        : engine_(std::random_device{}()),
        distribution_(min, max) {}
    
    int operator()() { return distribution_(engine_); }

    ~RandomNumberGenerator() {};

private:
    std::mt19937 engine_;
    std::uniform_int_distribution<> distribution_;
};
