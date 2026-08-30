#include <algorithm>
#include <iostream>
#include <vector>

void printResults(const std::vector<double> &readings, double max, double min, double avg, double median) {
    std::cout << "count: " << readings.size() << "\n";
    std::cout << "min: " << min << "\n";
    std::cout << "max: " << max << "\n";
    std::cout << "average: " << avg << "\n";
    std::cout << "median: " << median << "\n";
}

// expects sorted vector
double calculateMedian(const std::vector<double> &readings) {
    double median = 0;
    if (!readings.empty()) {
        if (readings.size() % 2 == 1) {
            median = readings[readings.size() / 2];
        }else {
            median = (readings[readings.size() / 2] + readings[readings.size() / 2 - 1])
                / 2;
        }
    }

    return median;
}

int main() {
    std::vector<double> readings;

    double max = 0;
    double min = 0;
    double summ = 0;

    double reading;
    while (std::cin >> reading) {
        readings.push_back(reading);
        if (reading < -40 || reading > 85) {
            std::cout << "reading outside the range: " << reading << ", position: " << readings.size() - 1 << "\n";
        }

        summ = summ + reading;
        if (readings.size() == 1) {
            max = reading;
            min = reading;
        } else if (reading > max) {
            max = reading;
        } else if (reading < min) {
            min = reading;
        }
    }

    if (std::cin.fail() && !std::cin.eof()) {
        std::cout << "stream failed on corrupted input" << "\n";
    }


    double avg = 0;
    double median = 0;
    if (!readings.empty()) {
        avg = summ / static_cast<double>(readings.size());
        std::ranges::sort(readings);
        median = calculateMedian(readings);
    }

    printResults(readings, max, min, avg, median);
}
