#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> readings;

    double max = 0;
    double min = 0;
    double summ = 0;

    double reading;
    while (std::cin >> reading) {
        readings.push_back(reading);
        if (reading < -40 || reading > 85) {
            std::cout << "reading outside the range!\n";
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

    double avg = 0;
    double median = 0;
    if (!readings.empty()) {
        avg = summ / static_cast<double>(readings.size());
        std::ranges::sort(readings);

        if (readings.size() % 2 == 1) {
            median = readings[readings.size() / 2];
        }else {
            median = (readings[readings.size() / 2] + readings[readings.size() / 2 - 1])
                / 2;
        }
    }

    std::cout << min << "\n";
    std::cout << max << "\n";
    std::cout << avg << "\n";
    std::cout << median << "\n";
}
