#ifndef FIND_BETTER_TEXT_HXX_INCLUDED
#define FIND_BETTER_TEXT_HXX_INCLUDED
#include <map>
#include "config.hxx"
#include <iostream>
#include <fstream>
#include "weighMaster.hxx"
int findBetterText(const std::vector<double>& userWeighs, const std::vector<std::string>& texts){
  char buff[3000];
  weighMaster weights(lettersAmount);
  int bestText = -1;
  double bestValue = -1;

  for(int textCount = 0; textCount < texts.size(); ++textCount){
    const std::string& currentTextName = texts[textCount];
    const std::string fullPathToText = textsFolder+currentTextName;
    std::ifstream file{fullPathToText};
    if(file.bad()){
      throw std::runtime_error{"uncorrect filename"};
    }
    while(file.getline(buff,3000)){
      const int len = strlen(buff);
      char prevSymbol = ' ';
      char prevIndex = 0;
      for(int symbolCount = 0; symbolCount < len; ++symbolCount){
          const char& curSymbol = buff[symbolCount];
          const int curIndex = lettersMap[curSymbol];

          weights.makeSample(prevIndex,curIndex);

          prevSymbol = curSymbol;
          prevIndex = curIndex;
      }
    }
    weights.normalize();
    double weightForThisText = 0.0;
    const std::vector<double>& weightsForThisText = weights.getWeights();
    for(int i = 0; i < userWeighs.size(); ++i){
      weightForThisText+=userWeighs[i]*weightsForThisText[i];
    }

    weights.clear();

    std::cout << weightForThisText << std::endl;
    if(weightForThisText > bestValue){
      bestText = textCount;
      bestValue = weightForThisText;
    }
  }
  return bestText;
}
std::string constructBetterWords(const std::vector<double>& userWeighs, const std::vector<std::string>& words){
  weighMaster weights(lettersAmount);
  std::multimap<double,int,std::greater<double>> wordsMap;
  for(uint32_t wordsCount = 0; wordsCount < words.size(); ++wordsCount){ const std::string& curWord = words[wordsCount];
    const uint32_t curWordSize = curWord.size();
    char prevSymbol = ' ';
    char prevIndex = 0;
    for(int symbolCount = 0; symbolCount < curWordSize; ++symbolCount){
      const char& curSymbol = curWord[symbolCount];
      const int curIndex = lettersMap[curSymbol];

      weights.makeSample(prevIndex,curIndex);

      prevSymbol = curSymbol;
      prevIndex = curIndex;
    }
    weights.normalize();
    double weightForThisText = 0.0;
    const std::vector<double>& weightsForThisText = weights.getWeights();
    for(int i = 0; i < userWeighs.size(); ++i){
      weightForThisText+=userWeighs[i]*weightsForThisText[i];
    }
    weights.clear();
    wordsMap.insert({weightForThisText,wordsCount});
  }
  std::string result{};
  for(const auto& [weigh,wordNum] : wordsMap){
    if(result.size() < maxTextFromWordsSize){
      result += words[wordNum];
      if(result.size() < maxTextFromWordsSize)
        result += " ";
    }else{
      break;
    }
  }
  return result;
}

#endif  // FIND_BETTER_TEXT_HXX_INCLUDED
