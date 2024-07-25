#include <iostream>
#include <map>

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

int main() {
  std::multimap<std::string, int> queue;
  std::string operation;
  std::cout << "Input surname or\n";
  std::cout << "To exit, input \"exit\"\n";
  std::cout << "To call the next one in line, input \"next\"\n";

  for (int i = 0; lower_case(operation) != "exit";) {
    std::cout << "Input operation: ";
    std::cin >> operation;
    if (lower_case(operation) == "exit") continue;

    if (lower_case(operation) == "next") {
      if (!queue.empty()) {
        std::cout << queue.begin()->first << "\n";
        queue.erase(queue.begin());

        continue;
      } else {
        std::cout << "Operation not possible\n";
        continue;
      }
    } else {
      queue.insert({operation, i});
      i++;
    }
  }
}