#include <iostream>
#include <vector>

int main() {
    int N=0;
    std::vector<double> readings;

    std::cin >> N;
    readings.resize(N);

    double max=0;
    double min=0;
    double summ=0;

    for (int i=0;i<N;i++) {
        double reading;
        std::cin >> reading;
        readings[i] = reading;

        if (reading < -40 || reading > 85) {
            std::cout << "reading outside the range!\n";
        }

        summ = summ + reading;
        if (i==0) {
            max = readings[0];
            min = readings[0];
        } else if (reading > max) {
            max = reading;
        } else if (reading < min) {
            min = reading;
        }
    }

    double avg = summ/N;

    std::cout << min << "\n";
    std::cout << max << "\n";
    std::cout << avg << "\n";
}
