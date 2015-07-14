#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

std::pair<int, std::vector<int>>
knapsack(std::vector<std::pair<int, int>> objects, int maxWeight) {
  std::vector<std::pair<int, std::vector<int>>> currentRow;
  std::vector<std::pair<int, std::vector<int>>> lastRow;

  currentRow.resize(maxWeight + 1);
  lastRow.resize(maxWeight + 1);

  std::pair<int, std::vector<int>> empty(0, std::vector<int>());

  for (int i = 0; i < maxWeight; i++) {
    currentRow[i] = empty;
    lastRow[i] = empty;
  }

  for (int i = 0; i < objects.size(); i++) {
    for (int j = 1; j <= maxWeight; j++) {
      auto top = lastRow[j];
      auto entry = currentRow[j];

      if (j >= objects[i].first) {
        if (j >= objects[i].first) {
          entry.second = currentRow[j - objects[i].first].second;
          entry.first = currentRow[j - objects[i].first].first;
          if (std::find(entry.second.begin(), entry.second.end(), i) ==
              entry.second.end()) {
            entry.first += objects[i].second;
            entry.second.push_back(i);
          }
        }
      }

      if (top.first >= entry.first) {
        entry.first = top.first;
        entry.second.clear();
        entry.second = top.second;
      }

      currentRow[j] = entry;

      std::cout << currentRow[j].first << ":" << objects[0].second;
      for (int k = 1; k < entry.second.size(); k++) {
        std::cout << "," << objects[currentRow[j].second[k]].first;
      }
      std::cout << '\t';
    }

    lastRow = currentRow;
    for (int i = 0; i < maxWeight; i++) {
      currentRow[i] = empty;
    }

    std::cout << std::endl;
  }

  return currentRow[maxWeight];
}

int main() {
  std::vector<std::pair<int, int>> v = {
      std::make_pair(3, 5), std::make_pair(7, 8), std::make_pair(1, 2)};

  auto ans = knapsack(v, 9);
}
