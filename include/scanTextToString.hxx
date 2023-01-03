#ifndef SCAN_TEXT_TO_STRING____HXX___INCLUDED
#define SCAN_TEXT_TO_STRING____HXX___INCLUDED
#include <string>
#include <fstream>
std::string scanTextToString(const std::string& currentTextName){
  std::string result;
  char buff[3000];

  std::ifstream file(textsFolder + currentTextName);
  if(!file.bad()){
    file.getline(buff,3000);
    result = std::string(buff);
  }
  return result;
}
std::vector<std::string> scanWordsToString(const std::string& currentTextName){
  std::string buff;
  std::ifstream file(textsFolder + currentTextName);
  std::vector<std::string> result;
  if(!file.bad()){
    while(file >> buff){
      result.push_back(buff);
    }
  }
  return result;
}
#endif //  SCAN_TEXT_TO_STRING____HXX___INCLUDED
