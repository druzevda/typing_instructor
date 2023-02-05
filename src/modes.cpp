#include "modes.hxx"
#include <vector>
#include <string>
#include "weighMaster.hxx"
#include "typingSample.hxx"
#include "constructFunctions.hxx"
#include <cassert>
#include <random>

#include "config.hxx"
#include "enumCodes.hxx"

void learningByErrorsTextes_mode(){
  fprintf(logfile,"in learning by errors TEXTES mode\n");

  weighMaster personMaster(symbolsAmount);

  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.",code);

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const int betterText = findBetterText(personMaster.getWeights(),texts);
    const std::string newText = scanTextToString(texts[betterText]);

    fprintf(logfile,"better texts is [%d] [%s] \n",betterText,newText.c_str());

    personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end learning by errors Textes mode\n");
}

void learningByErrorsWords_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in learning by errors WORDS mode\n");

  weighMaster personMaster(symbolsAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.",code);
  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const std::string newText = constructBetterWords(personMaster.getWeights(), buff);
    personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end learning by errors WORDS mode\n");
}

void randomWords_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in random WORDS mode\n");

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  assert(buff.size() > 0);

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const std::string newText = constructTextFromWords(buff);
    const auto personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end random WORD mode\n");
}
void randomText_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in random TEXTES mode\n");

  std::mt19937 mersene(std::random_device{}());
  std::uniform_int_distribution<> unif(0,texts.size());

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const int randomText = unif(mersene);
    const std::string newText = scanTextToString(texts[randomText]);

    fprintf(logfile,"random texts is [%d] [%s] \n",randomText,newText.c_str());

    const auto personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end learning by errors Textes mode\n");
}
void randomLetters_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in random LETTERS mode\n");

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const std::string newText = constructRandomLettersText();
    std::fprintf(logfile,"text->%s<-\n",newText.c_str());
    fflush(logfile);
    const auto personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end random LETTERS mode\n");
}
void randomWord_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in random WORD mode\n");

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  std::mt19937 mersene(std::random_device{}());
  std::uniform_int_distribution<> unif(0,buff.size());
  assert(buff.size() > 0);

  auto findGoodWord = [&mersene,&unif,&buff](){
    while(true){
      const int wordNum = unif(mersene);
      const std::string& word = buff[wordNum];
      if(isAcceptWord(word)){
        return word;
      }
    }
  };

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const std::string& word = findGoodWord();

    const std::string newText = constructTextFromWord(word);
    const auto personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end random WORD mode\n");
}

void learningByErrorsOneWord_mode(){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in learnign by errors WORD mode");

  weighMaster personMaster(symbolsAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.",code);

  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  assert(buff.size() > 0);

  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const std::string bestWord = findBetterWord(personMaster.getWeights(), buff);
    const std::string& realyBest = bestWord;
    const std::string newText = constructTextFromWord(realyBest);
    personMaster = typingSample(newText,code);
  }

  fprintf(logfile,"end learnign by errors WORD mode");
}
