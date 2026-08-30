#include <iostream>
#include <vector>

int main() {
    double max=0;
    double min=0;
    double summ=0;
    int N = 0;

    double reading;
    while (std::cin >> reading) {
        if (reading < -40 || reading > 85) {
            std::cout << "reading outside the range!\n";
        }

        summ = summ + reading;
        if (N==0) {
            max = reading;
            min = reading;
        } else if (reading > max) {
            max = reading;
        } else if (reading < min) {
            min = reading;
        }

        N++;
    }

    double avg = summ/N;

    std::cout << min << "\n";
    std::cout << max << "\n";
    std::cout << avg << "\n";
}