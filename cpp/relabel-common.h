#pragma  once

#include <vector>

#include "GraphBLAS.h"

uint64_t fasthash(uint64_t value);

std::vector<GrB_Index> getVertexIds(uint64_t numberOfVertices);

std::vector<GrB_Index> getListOfIds(const std::vector<GrB_Index>& vertexIds, uint64_t multiplier, uint64_t numberOfIndices, uint64_t numberOfThreads);

void saveToFile(const std::vector<GrB_Index> &toSave, const std::string &filename);

std::vector<GrB_Index> readFromFile(const std::string &filename);