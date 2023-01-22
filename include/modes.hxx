#ifndef MODES_HXX_INCLUDED_________________
#define MODES_HXX_INCLUDED_________________
#include <random>
#include "config.hxx"
void learningByErrorsTextes_mode(){
  fprintf(logfile,"in learning by errors TEXTES mode\n");

  weighMaster personMaster(symbolsAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");

  while(true){
    const int betterText = findBetterText(personMaster.getWeights(),texts);
    const std::string newText = scanTextToString(texts[betterText]);

    fprintf(logfile,"better texts is [%d] [%s] \n",betterText,newText.c_str());

    personMaster = typingSample(newText);
  }

  fprintf(logfile,"end learning by errors Textes mode\n");
}

void learningByErrorsWords_mode(){
  fprintf(logfile,"in learning by errors WORDS mode\n");

  weighMaster personMaster(symbolsAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");
  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  while(true){
    const std::string newText = constructBetterWords(personMaster.getWeights(), buff);
    personMaster = typingSample(newText);
  }

  fprintf(logfile,"end learning by errors WORDS mode\n");
}

void randomWords_mode(){
  fprintf(logfile,"in random WORDS mode\n");

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  assert(buff.size() > 0);

  while(true){
    const std::string newText = constructTextFromWords(buff);
    const auto personMaster = typingSample(newText);
  }

  fprintf(logfile,"end random WORD mode\n");
}
void randomText_mode(){
  fprintf(logfile,"in random TEXTES mode\n");

  std::mt19937 mersene(std::random_device{}());
  std::uniform_int_distribution<> unif(0,texts.size());

  while(true){
    const int randomText = unif(mersene);
    const std::string newText = scanTextToString(texts[randomText]);

    fprintf(logfile,"random texts is [%d] [%s] \n",randomText,newText.c_str());

    const auto personMaster = typingSample(newText);
  }

  fprintf(logfile,"end learning by errors Textes mode\n");
}
void randomWord_mode(){
  fprintf(logfile,"in random WORD mode\n");

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  std::mt19937 mersene(std::random_device{}());
  std::uniform_int_distribution<> unif(0,buff.size());
  assert(buff.size() > 0);

  while(true){
    const int wordNum = unif(mersene);
    const std::string& word = buff[wordNum];

    const std::string newText = constructTextFromWord(word);
    const auto personMaster = typingSample(newText);
  }

  fprintf(logfile,"end random WORD mode\n");
}

void learningByErrorsOneWord_mode(){
  fprintf(logfile,"in learnign by errors WORD mode");

  weighMaster personMaster(symbolsAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  assert(buff.size() > 0);

  while(true){
    const std::string bestWord = findBetterWord(personMaster.getWeights(), buff);
    const std::string& realyBest = bestWord;
    const std::string newText = constructTextFromWord(realyBest);
    personMaster = typingSample(newText);
  }

  fprintf(logfile,"end learnign by errors WORD mode");
}
#endif //  MODES_HXX_INCLUDED_________________
