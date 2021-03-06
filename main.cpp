#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <sstream>

// Returns total weight, total value, list of items
std::tuple<int, int, std::vector<int>> knapsack(std::vector<std::pair<int, int>> objects, int maxWeight)
{
  std::vector<std::pair<int, std::vector<int>>> currentRow;
  std::vector<std::pair<int, std::vector<int>>> lastRow;

  currentRow.resize(maxWeight + 1);
  lastRow.resize(maxWeight + 1);

  std::pair<int, std::vector<int>> empty(0, std::vector<int>());

  for (int i = 0; i < maxWeight; i++)
  {
	currentRow[i] = empty;
	lastRow[i] = empty;
  }

  for (int i = 0; i < objects.size(); i++)
  {
	for (int j = 1; j <= maxWeight; j++)
	{
	  auto top = lastRow[j];
	  auto entry = currentRow[j];

	  if (j >= objects[i].first)
	  {
	  	entry.second = lastRow[j - objects[i].first].second;
	  	entry.first = lastRow[j - objects[i].first].first;
	  	entry.first += objects[i].second;
	  	entry.second.push_back(i);
	  }

	  if (top.first >= entry.first)
	  {
		entry.first = top.first;
		entry.second.clear();
		entry.second = top.second;
	  }

	  currentRow[j] = entry;
	  std::cout << entry.first << '\t';
	}

	lastRow = currentRow;
	for (int i = 0; i < maxWeight; i++)
	{
	  currentRow[i] = empty;
	}

	std::cout << std::endl;
  }

  int totalWeight;
  for (int i : currentRow[maxWeight].second)
  {
	totalWeight += objects[i].first;
  }

  return std::make_tuple(totalWeight, currentRow[maxWeight].first, currentRow[maxWeight].second);
}

std::tuple<int, std::vector<std::pair<int, int>>> parseValues(std::string filename)
{
  std::vector<std::pair<int, int>> objects;
  std::ifstream file(filename);

  int objectCount;
  file >> objectCount;

  int w, v;
  while (file >> w >> v)
  {
	objects.push_back(std::make_pair(w, v));
  }

  return std::make_tuple(w, objects);
}

void writeResult(std::string filename, std::vector<int> indices, std::vector<std::pair<int, int>> objects, int maxWeight, int totalWeight,
                 int totalValue)
{
  std::stringstream weights;
  std::stringstream values;

  int totalW = 0;

  for (int i : indices)
  {
  	totalW += objects[i].first;
	weights << objects[i].first;
	values << objects[i].second;

	int wlen = std::to_string(objects[i].first).length();
	int vlen = std::to_string(objects[i].second).length();

	for (int i = 0; i < wlen; i++)
	{
	  values << ' ';
	}
	for (int i = 0; i < vlen; i++)
	{
	  weights << ' ';
	}
  }

  weights << " -> " << totalW;
  values << " -> " << totalValue;

  std::ofstream file(filename);
  file << maxWeight << '\n' << weights.str() << '\n' << values.str() << '\n';
}

int main()
{
  std::vector<std::pair<int, int>> objects;
  int weight;
  std::tie(weight, objects) = parseValues("data.dat");

  int actualW, actualV;
  std::vector<int> itemIndexes;
  std::tie(actualW, actualV, itemIndexes) = knapsack(objects, weight);
  writeResult("subset.res", itemIndexes, objects, weight, actualW, actualV);
  return 0;
}
