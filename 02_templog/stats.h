//
// Created by alex1 on 06.09.2026.
//

#ifndef CPPONE_STATS_H
#define CPPONE_STATS_H

#include <vector>

double Min(const std::vector<double> &readings);
double Max(const std::vector<double> &readings);
double Mean(const std::vector<double> &readings);
double Median(const std::vector<double> &readings);

#endif //CPPONE_STATS_H
