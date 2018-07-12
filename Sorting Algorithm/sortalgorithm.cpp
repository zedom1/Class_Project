#include "sortalgorithm.h"

SortAlgorithm * SortAlgorithm::algorithm = nullptr;

SortAlgorithm::SortAlgorithm()
{
}

void SortAlgorithm::setAlgorithm(SortAlgorithm* algo)
{
    algorithm = algo;
}

SortAlgorithm* SortAlgorithm::getInstance()
{
    return algorithm;
}
