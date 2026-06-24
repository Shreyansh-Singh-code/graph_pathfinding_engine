#pragma once

#include <string>

struct AlgoStats
{
    double totalTime = 0.0;

    long long totalExpanded = 0;

    double totalDistance = 0.0;

    int successfulQueries = 0;
};

void printStats(
    const std::string& name,
    const AlgoStats& stats
);