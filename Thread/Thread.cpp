#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>

constexpr int num_threads = 4;

void computeSum(std::vector<int>& data, int start, int end, long long& result) {
    for (int i = start; i < end; ++i) {
        data[i] = rand() % 100;
    }
    result = std::accumulate(data.begin() + start, data.begin() + end, 0LL);
}

int main() {
    std::vector<int> data(1000000000);

    std::thread threads[num_threads];

    long long results[num_threads] = { 0 };

    auto start = std::chrono::steady_clock::now();

    int chunk_size = data.size() / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(computeSum, std::ref(data), i * chunk_size, (i + 1) * chunk_size, std::ref(results[i]));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    long long total_sum = 0;
    for (int i = 0; i < num_threads; ++i) {
        total_sum += results[i];
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "Total sum: " << total_sum << std::endl;
    std::cout << "Execution time: " << std::chrono::duration<double>(end - start).count() << " seconds" << std::endl;

    return 0;
}
