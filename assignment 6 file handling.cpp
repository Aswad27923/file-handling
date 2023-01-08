#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
  cout << "Enter the name of the first file: ";
  string file1Name;
  getline(cin, file1Name);

  cout << "Enter the name of the second file: ";
  string file2Name;
  getline(cin, file2Name);

  ifstream file1(file1Name);
  ifstream file2(file2Name);

  
  if (!file1.is_open()) {
    cerr << "Error: could not open file " << file1Name << endl;
    return 1;
  }
  if (!file2.is_open()) {
    cerr << "Error: could not open file " << file2Name << endl;
    return 1;
  }

  
  unordered_map<string, int> file1WordCounts;
  unordered_map<string, int> file2WordCounts;

  
  string word;
  while (file1 >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    file1WordCounts[word]++;
  }
  while (file2 >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    file2WordCounts[word]++;
  }

 
  file1.close();
  file2.close();


  int file1TotalWords = 0;
  for (const auto& kv : file1WordCounts) {
    file1TotalWords += kv.second;
  }
  int file2TotalWords = 0;
  for (const auto& kv : file2WordCounts) {
    file2TotalWords += kv.second;
  }
  cout << "Total words in " << file1Name << ": " << file1TotalWords << endl;
  cout << "Total words in " << file2Name << ": " << file2TotalWords << endl;
  int commonWords = 0;
  for (const auto& kv : file1WordCounts) {
    if (file2WordCounts.count(kv.first) > 0) {
      commonWords += min(kv.second, file2WordCounts[kv.first]);
    }
  }
  double similarity = (double)commonWords / (file1TotalWords + file2TotalWords - commonWords);
  cout << "Similarity: " << similarity * 100 << "%" << endl;

  return 0;
}