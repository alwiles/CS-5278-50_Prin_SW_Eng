#include<algorithm>
#include <iostream> //aw test
#include "GeoDB.h"
#include "GeoHash.h"

GeoDB::GeoDB(int bitsOfPrecision)
{
	m_bitsOfPrecision = bitsOfPrecision;
	m_geoHashGenerator = GeoHash();
}

void GeoDB::InsertLocation(double lat, double lon)
{
	char outGeohashString[32] = { 0 };
	uint32_t hashedValue = m_geoHashGenerator.GetGeohashInteger(lat, lon, m_bitsOfPrecision);
	m_geoHashGenerator.GetGeohashString(lat, lon, m_bitsOfPrecision, outGeohashString); //aw tests
	struct Node_s* newNode = (struct Node_s*)malloc(sizeof(struct Node_s));
	newNode->nodeValue = hashedValue;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->isDeleted = false;
	newNode->latitude = lat;
	newNode->longitude = lon;

	if (m_rootNode == NULL)
	{
		m_rootNode = newNode;
		std::cout << "Created root node: " + newNode->nodeValue; //aw test
	}
	else
	{
		struct Node_s* currentNode = m_rootNode;
		while (1)
		{
			if (hashedValue < currentNode->nodeValue)
			{
				if (currentNode->leftChild == NULL)
				{
					currentNode->leftChild = newNode;
					std::cout << "Created left node: " + newNode->nodeValue << std::endl; //aw test
					break;
				}
				else
				{
					currentNode = currentNode->leftChild;
				}
			}
			else if (hashedValue > currentNode->nodeValue)
			{
				if (currentNode->rightChild == NULL)
				{
					currentNode->rightChild = newNode;
					std::cout << "Created right node: " + newNode->nodeValue << std::endl; //aw test
					break;
				}
				else
				{
					currentNode = currentNode->rightChild;
				}
			}
			else
			{
				currentNode->isDeleted = false;
				
				//node already exists; overwrite
				currentNode->latitude = lat;
				currentNode->longitude = lon;
				std::cout << "Revived node" << std::endl; //aw test

				free(newNode);
				break;
			}
		}
	}
}

bool GeoDB::DeleteLocation(double lat, double lon)
{
	uint32_t valueToDelete = m_geoHashGenerator.GetGeohashInteger(lat, lon, m_bitsOfPrecision);
	return deleteNodes(m_rootNode, valueToDelete);
}

std::vector<std::pair<double, double>> GeoDB::DeleteAll(double lat, double lon, int bitsOfPrecision)
{
	if (bitsOfPrecision == 0)
	{
		std::vector<std::pair<double, double>> results = getAll();
		clearTree();
		return results;
	}
	std::vector<std::pair<double, double>> results;
	uint32_t compareValue = m_geoHashGenerator.GetGeohashInteger(lat, lon, bitsOfPrecision);
	uint32_t mask = (1 << bitsOfPrecision) - 1;

	//aw test
	struct Node_s* currentRoot = m_rootNode;
	while (currentRoot != NULL)
	{
		uint32_t currentValue = currentRoot->nodeValue;
		bool isMatch = ((currentValue & mask) == (compareValue & mask));
		int val1 = (currentValue & mask);
		int val2 = (compareValue & mask);
		if (((currentValue & mask) == (compareValue & mask)) && !currentRoot->isDeleted)
		{
			std::pair<double, double> coordinates;
			coordinates.first = currentRoot->latitude;
			coordinates.second = currentRoot->longitude;
			currentRoot->isDeleted = true;
			results.push_back(coordinates);

			currentRoot = currentRoot->rightChild; //matches can't be less than the compare value
		}
		else
		{
			if (val1 > val2) // matches will only be found in greater than, equal to compare value
			{
				currentRoot = currentRoot->leftChild;
			}
			else
			{
				currentRoot = currentRoot->rightChild;
			}
		}

	}

	return results;
}

bool GeoDB::ContainsLocation(double lat, double lon, int bitsOfPrecision)
{
	uint32_t compareValue = m_geoHashGenerator.GetGeohashInteger(lat, lon, bitsOfPrecision);	
	uint32_t mask = (1 << bitsOfPrecision) - 1;

	//aw test
	struct Node_s* currentRoot = m_rootNode;
	while (currentRoot != NULL)
	{
		uint32_t currentValue = currentRoot->nodeValue;
		int val1 = (currentValue & mask);
		int val2 = (compareValue & mask);
		if (((currentValue & mask) == (compareValue & mask)) && !currentRoot->isDeleted)
		{
			return true;
		}
		if (val1 > val2)
		{
			currentRoot = currentRoot->leftChild;
		}
		else
		{
			currentRoot = currentRoot->rightChild;
		}
	}
	return false;
}

std::vector<std::pair<double, double>> GeoDB::NearbyLocations(double lat, double lon, int bitsOfPrecision)
{
	if (bitsOfPrecision == 0)
	{
		return getAll();
	}
	std::vector<std::pair<double, double>> results;
	uint32_t compareValue = m_geoHashGenerator.GetGeohashInteger(lat, lon, bitsOfPrecision);
	uint32_t mask = (1 << bitsOfPrecision) - 1;

	//aw test
	struct Node_s* currentRoot = m_rootNode;
	while (currentRoot != NULL)
	{
		uint32_t currentValue = currentRoot->nodeValue;
		bool isMatch = ((currentValue & mask) == (compareValue & mask));
		int val1 = (currentValue & mask);
		int val2 = (compareValue & mask);
		if (((currentValue & mask) == (compareValue & mask)) && !currentRoot->isDeleted)
		{
			std::pair<double, double> coordinates;
			coordinates.first = currentRoot->latitude;
			coordinates.second = currentRoot->longitude;
			results.push_back(coordinates);

			currentRoot = currentRoot->rightChild; //matches can't be less than the compare value
		}
		else
		{
			if (val1 > val2) // matches will only be found in greater than, equal to compare value
			{
				currentRoot = currentRoot->leftChild;
			}
			else
			{
				currentRoot = currentRoot->rightChild;
			}
		}
		
	}
	
	return results;
}

std::vector<std::pair<double, double>> GeoDB::getAll()
{
	return traverseEntireTree();
}

bool GeoDB::deleteNodes(struct Node_s* targetNode, uint32_t valueToDelete)
{
	bool deleted = false;
	
	if (targetNode == NULL)
		return false;
	if (targetNode->nodeValue == valueToDelete)
	{
		//delete and reassign
		targetNode->isDeleted = true; //aw test
		deleted = true;
	}

	// left side recursion
	deleteNodes(targetNode->leftChild, valueToDelete);

	if (targetNode->nodeValue == valueToDelete)
	{
		//delete and reassign
		targetNode->isDeleted = true; //aw test
		deleted = true;
	}

	// right side recursion
	deleteNodes(targetNode->rightChild, valueToDelete);

	return deleted;
}

std::vector<std::pair<double, double>> GeoDB::traverseEntireTree() {
	std::vector<std::pair<double, double>> result;
	treeTraversal(m_rootNode, result);
	return result;
}

void GeoDB::treeTraversal(struct Node_s* node, std::vector<std::pair<double, double>>& visited) {
	if (node != nullptr) {
		treeTraversal(node->leftChild, visited);
		treeTraversal(node->rightChild, visited);
		if (!node->isDeleted)
		{
			std::pair<double, double> newValue;
			newValue.first = node->latitude;
			newValue.second = node->longitude;
			visited.push_back(newValue);
		}
	}
}

void GeoDB::clearTree() {
	std::vector<std::pair<double, double>> result;
	clearTree(m_rootNode);
	return;
}

void GeoDB::clearTree(struct Node_s* node) {
	if (node != nullptr) {
		clearTree(node->leftChild);
		clearTree(node->rightChild);
		node->isDeleted = true;
	}
}
