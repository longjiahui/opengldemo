#include "util.hpp"
#include <fstream>

using namespace std;

string huige::readFile(const char *path) {
  ifstream vertexFile(path, ios_base::in);
  auto ret = string(istreambuf_iterator<char>(vertexFile),
                    istreambuf_iterator<char>());
  vertexFile.close();
  return ret;
}