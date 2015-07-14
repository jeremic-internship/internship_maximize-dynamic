#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

bool getBit(int* arr, int bit) {
	int pos = bit / 32;
	return (arr[pos] >> (bit % 32)) & 1;
}

void setBit(int* arr, bool val, int bit) {
	int pos = bit / 32;
	arr[pos] = arr[pos] | ((val ? 1 : 0) << (bit % 32));
}

void reset(int** arr, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			arr[i][j] = 0;
		}
	}
}

int knapsack(int* values, int* weights, int numItems, int maxWeight)
{
	std::vector<std::pair<int, std::vector<int>>> currentRow;
	std::vector<std::pair<int, std::vector<int>>> lastRow;

	currentRow.resize(maxWeight);
	lastRow.resize(maxWeight);

	std::pair<int, std::vector<int>> empty(0, std::vector<int>());

	for (int i = 0; i < maxWeight; i++) {
		currentRow[i] = empty;
		lastRow[i] = empty;
	}

	for (int i = 0; i < numItems; i++) {
		for (int j = 1; j <= maxWeight; j++) {
			auto top = lastRow[j];
			auto& entry = currentRow[j];

			if (j >= weights[i]) {
				if (j > weights[i] && std::find(currentRow[j - weights[i] - 1].second.begin(),
				                     currentRow[j - weights[i] - 1].second.end(), 
				                     i)
				                     == currentRow[j - weights[i] - 1].second.end()) {
					entry.first = currentRow[j - weights[i] - 1].first + values[i];
					entry.second = currentRow[j - weights[i] - 1].second;
					entry.second.push_back(i);
				}
				else if (j == weights[i]) {
					entry.first = values[i];
					entry.second.push_back(i);
				}
			}

			if (top.first > entry.first) {
				entry.first = top.first;
				entry.second = top.second;
			}
		}
		lastRow = currentRow;
		for (int i = 0; i < maxWeight; i++) {
			currentRow[i] = empty;
		}
	}

	return currentRow[maxWeight - 1].first;
}

int main() {
	int v[] = {4, 5, 8};
	int w[] = {3, 6, 9};
	std::cout << knapsack(&v[0], &w[0], 3, 9) << std::endl;
}