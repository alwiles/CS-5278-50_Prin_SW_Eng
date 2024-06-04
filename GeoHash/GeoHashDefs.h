#pragma once
#include <cstdint>
struct Node_s
{
	bool isDeleted;
	double latitude;
	double longitude;
	uint32_t nodeValue;
	struct Node_s* leftChild;
	struct Node_s* rightChild;
};
