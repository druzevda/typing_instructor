#ifndef FIND_BETTER_TEXT_HXX_INCLUDED
#define FIND_BETTER_TEXT_HXX_INCLUDED
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

#endif  // FIND_BETTER_TEXT_HXX_INCLUDED
