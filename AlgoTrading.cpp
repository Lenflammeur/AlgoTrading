#include <vector>
#include <iostream>
#include <stdexcept>

// Calculate a moving average
double calculateMovingAverage(const std::vector<double>& data, int start, int end) {
    if (start < 0 || end > data.size() || start >= end) {
        throw std::invalid_argument("Invalid start or end for moving average calculation.");
    }
    double sum = 0;
    for (int i = start; i < end; i++) {
        sum += data[i];
    }
    return sum / (end - start);
}

// Identify when to buy or sell
std::vector<std::pair<int, std::string>> identifySignals(const std::vector<double>& data, int shortTermDays, int longTermDays) {
    if (data.size() < longTermDays || shortTermDays <= 0 || longTermDays <= 0) {
        throw std::invalid_argument("Invalid parameters for identifySignals function.");
    }

    std::vector<std::pair<int, std::string>> signals;
    for (int i = longTermDays; i < data.size(); i++) {
        double shortTermMA = calculateMovingAverage(data, i - shortTermDays, i);
        double longTermMA = calculateMovingAverage(data, i - longTermDays, i);

        if (shortTermMA > longTermMA) {
            signals.push_back({ i, "Buy" });
        }
        else if (shortTermMA < longTermMA) {
            signals.push_back({ i, "Sell" });
        }
    }
    return signals;
}

int main() {
    // Test data
    std::vector<double> testData = { /* your data */ };

    try {
        // Test the function
        std::vector<std::pair<int, std::string>> signals = identifySignals(testData, 50, 200);

        // Print the signals
        for (const auto& signal : signals) {
            std::cout << signal.second << " signal at day " << signal.first << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
