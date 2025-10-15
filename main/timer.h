#pragma once
#include "mylib.h"


class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string label;
    inline static std::vector<std::pair<std::string, double>> results; 

public:
    Timer(const std::string& name = "") 
        : start{std::chrono::high_resolution_clock::now()}, label{name} {}

    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        return std::chrono::duration<double, std::milli>(
            std::chrono::high_resolution_clock::now() - start
        ).count();
    }

    
    void save() {
        results.push_back({label, elapsed()});
    }

    
    void print() const {
        std::cout << label << ": " << elapsed() << " ms" << std::endl;
    }

    
    static void showAll() {
        std::cout << "\n--- Laiko matavimų santrauka ---\n";
        for (const auto& [name, time] : results)
            std::cout << std::left << std::setw(30) << name 
                      << ": " << std::fixed << std::setprecision(3)
                      << time << " ms" << std::endl;
        std::cout << "---------------------------------\n";
    }

    static void clear() { results.clear(); }
};