#ifndef FIND_BETTER_TEXT_HXX_INCLUDED
#define FIND_BETTER_TEXT_HXX_INCLUDED
#include <map>
#include "config.hxx"
#include <iostream>
#include <fstream>
#include "weighMaster.hxx"
int findBetterText(const std::vector<double>& userWeighs, const std::vector<std::string>& texts){
  std::fprintf(logfile,"in findBetterText\n");
  char buff[3000];
  weighMaster weights(lettersAmount);
  int bestText = 0;
  double bestValue = -1;

  for(int textCount = 0; textCount < texts.size(); ++textCount){
    const std::string& currentTextName = texts[textCount];
    const std::string fullPathToText = textsFolder+currentTextName;
    std::ifstream file{fullPathToText};
    if(file.bad()){
      std::fprintf(logfile,"fileNotOpen ->%s<- \n",fullPathToText.c_str());
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
    std::fprintf(logfile,"->%s<- weigh = %lf\n",fullPathToText.c_str(),weightForThisText);
    if(weightForThisText > bestValue){
      bestText = textCount;
      bestValue = weightForThisText;
    }
  }
  std::fprintf(logfile,"bettertext->%s<- weigh = %lf\n\n\n",texts[bestText].c_str(),bestValue);
  fflush(logfile);
  return bestText;
}
std::string constructBetterWords(const std::vector<double>& userWeighs, const std::vector<std::string>& words){
  std::fprintf(logfile,"in constructBetterWords\n");
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
      const std::string& goodWord=words[wordNum];
      result += goodWord;
      std::fprintf(logfile,"word->%s weigh->%lf\n",goodWord.c_str(),weigh);
      if(result.size() < maxTextFromWordsSize)
        result += " ";
    }else{
      break;
    }
  }
  fflush(logfile);
  return result;
}

std::string constructTextFromWord(const std::string& word){
  std::fprintf(logfile,"in constructTextFromWord word=%s\n",word.c_str());
  std::string result{};
  while(result.size() < maxTextFromWordsSize){
    result += word;
    if(result.size()>= maxTextFromWordsSize){
      break;
    }else{
      result+= " ";
    }
  }
  fflush(logfile);
  return result;
}

std::string findBetterWord(const std::vector<double>& userWeighs, const std::vector<std::string>& words){
  std::fprintf(logfile,"in findBetterWord\n");
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
  const auto bestWordPlace = (*wordsMap.begin()).second;
  const auto bestWordWeigh = (*wordsMap.begin()).first;
  const std::string& bestWord = words[bestWordPlace];

  std::fprintf(logfile,"best word =%s weigh=%lf\n",bestWord.c_str(),bestWordWeigh);

  fflush(logfile);
  return bestWord;
}
#endif  // FIND_BETTER_TEXT_HXX_INCLUDED
