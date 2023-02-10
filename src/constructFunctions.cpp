#include "constructFunctions.hxx"

#include "weighMaster.hxx"
#include "config.hxx"

#include <random>
#include <map>
#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>

int findBetterText(const std::vector<double>& userWeighs, const std::vector<std::string>& texts){
  std::fprintf(logfile,"in findBetterText\n");
  char buff[3000];
  weighMaster weights(symbolsAmount);
  int bestText = 0;
  double bestValue = -1;

  for(uint32_t textCount = 0; textCount < texts.size(); ++textCount){
    const std::string& currentTextName = texts[textCount];
    const std::string fullPathToText = textsFolder+currentTextName;
    std::ifstream file{fullPathToText};
    if(file.bad()){
      std::fprintf(logfile,"fileNotOpen ->%s<- \n",fullPathToText.c_str());
      throw std::runtime_error{"uncorrect filename"};
    }
    while(file.getline(buff,3000)){
      const int len = strlen(buff);
      char prevIndex = 0;// SPACE index
      for(int symbolCount = 0; symbolCount < len; ++symbolCount){
          const char curSymbol = std::tolower(buff[symbolCount]);
          const int curIndex = symbolsMap[curSymbol];

          weights.makeSample(prevIndex,curIndex);

          prevIndex = curIndex;
      }
    }
    double weightForThisText = 0.0;
    const auto weightsForThisText = weights.getWeights();
    for(uint32_t i = 0; i < userWeighs.size(); ++i){
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
  weighMaster weights(symbolsAmount);
  std::multimap<double,int,std::greater<double>> wordsMap;
  for(uint32_t wordsCount = 0; wordsCount < words.size(); ++wordsCount){ const std::string& curWord = words[wordsCount];
    const uint32_t curWordSize = curWord.size();
    char prevIndex = 0;// SPACE index
    for(uint32_t symbolCount = 0; symbolCount < curWordSize; ++symbolCount){
      const char curSymbol = std::tolower(curWord[symbolCount]);
      const int curIndex = symbolsMap[curSymbol];

      weights.makeSample(prevIndex,curIndex);

      prevIndex = curIndex;
    }
    double weightForThisText = 0.0;
    const auto weightsForThisText = weights.getWeights();
    for(uint32_t i = 0; i < userWeighs.size(); ++i){
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

std::string constructTextFromWords(const std::vector<std::string>& buff){

  std::fprintf(logfile,"in constructTextFromWords\n");
  std::mt19937 mersene(std::random_device{}());
  std::uniform_int_distribution<> unif(0,buff.size());
  std::string result{};

  auto findGoodWord = [&mersene,&unif,&buff](){
    while(true){
      const int wordNum = unif(mersene);
      const std::string& word = buff[wordNum];
      if(isAcceptWord(word)){
        return word;
      }
    }
  };

  while(result.size() <= maxTextFromWordsSize){
    const auto word = findGoodWord();
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
std::string constructTextFromWord(const std::string& word){
  std::fprintf(logfile,"in constructTextFromWord word=%s\n",word.c_str());
  std::string result{};
  while(result.size() <= maxTextFromWordsSize){
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
  weighMaster weights(symbolsAmount);
  std::multimap<double,int,std::greater<double>> wordsMap;
  for(uint32_t wordsCount = 0; wordsCount < words.size(); ++wordsCount){ const std::string& curWord = words[wordsCount];
    const uint32_t curWordSize = curWord.size();
    char prevIndex = 0; // SPACE index
    for(uint32_t symbolCount = 0; symbolCount < curWordSize; ++symbolCount){
      const char curSymbol = std::tolower(curWord[symbolCount]);
      const int curIndex = symbolsMap[curSymbol];

      weights.makeSample(prevIndex,curIndex);

      prevIndex = curIndex;
    }
    double weightForThisText = 0.0;
    const auto weightsForThisText = weights.getWeights();
    //const auto weightsForThisText = weights.getNormalizedWeights();
    for(uint32_t i = 0; i < userWeighs.size(); ++i){
      weightForThisText+=userWeighs[i]*weightsForThisText[i];
    }
    weights.clear();
    wordsMap.insert({weightForThisText,wordsCount});
  }

  for(const auto& [currWordWeigh,currWordPlace] : wordsMap){
    const std::string& currWord = words[currWordPlace];
    if(currWord.size() >= minWordSize_forOneWordText){
      std::fprintf(logfile,"best word =%s weigh=%lf\n",currWord.c_str(),currWordWeigh);
      fflush(logfile);
      return currWord;
    }
  }
  std::fprintf(logfile,"error dosnt have word with more symbols\n");
  fflush(logfile);
  return std::string{"specialWord"};
}
std::string constructRandomLettersText(){

  std::fprintf(logfile,"in constructRandomLettersText \n");

  std::mt19937 mersene{std::random_device{}()};
  std::uniform_int_distribution<> unif(0,lettersAmount-1);

  std::string result{};
  result.reserve(maxTextFromWordsSize);

  while(result.size() < maxTextFromWordsSize){
    const auto randomLetterNum = unif(mersene);
    const auto randomLetter = letters[randomLetterNum];
    result.push_back(randomLetter);
  }

  fflush(logfile);
  return result;
}

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
