#include <fstream>
#include <iostream>
#include <vector>

#include "text_diff.h"

// Function to read the content of a file into a vector of strings
std::vector<std::string> read_file(const std::string &filename) {
  std::ifstream file(filename);
  std::vector<std::string> lines;
  std::string line;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
  }

  return lines;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <file_a> <file_b>" << std::endl;
    return 1;
  }

  std::vector<std::string> file_a = read_file(argv[1]);
  std::vector<std::string> file_b = read_file(argv[2]);

  print_differences(file_a, file_b);
  return 0;
}