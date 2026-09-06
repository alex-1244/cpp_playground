//
// Created by alex1 on 06.09.2026.
//

#include "stats.h"
#include <vector>

double Min(const std::vector<double> &readings) {
    if (readings.empty())
        return 0;

    std::vector<double>::const_iterator iter;
    double min = *iter;
    for (iter = readings.cbegin(); iter != readings.cend(); ++iter) {
        if (*iter < min) {
            min = *iter;
        }
    }

    return min;
}

double Max(const std::vector<double> &readings) {
    if (readings.empty())
        return 0;

    std::vector<double>::const_iterator iter;
    double max = *iter;
    for (iter = readings.cbegin(); iter != readings.cend(); ++iter) {
        if (*iter > max) {
            max = *iter;
        }
    }

    return max;
}

double Mean(const std::vector<double> &readings) {
    if (readings.empty())
        return 0;

    double summ = 0;
    for (const double reading : readings) {
        summ+=reading;
    }

    return summ/readings.size();
}

double Median(const std::vector<double> &readings) {
    double median = 0;
    if (!readings.empty()) {
        if (readings.size() % 2 == 1) {
            median = readings[readings.size() / 2];
        } else {
            median = (readings[readings.size() / 2] + readings[readings.size() / 2 - 1])
                     / 2;
        }
    }

    return median;
}
