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

void learningByErrorsTextes_mode(weighMaster& personMaster){
  fprintf(logfile,"in learning by errors TEXTES mode\n");

  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  while(true){
    switch(code){
      case EXITCODE_TS::ALL_GOOD:
      case EXITCODE_TS::RERUN_THIS_MODE:
        break;
      case EXITCODE_TS::TO_MENU:
          return;
        break;
    }
    const int betterText = findBetterText(personMaster.getNormalizedWeights(),texts);
    const std::string newText = scanTextToString(texts[betterText]);
    fprintf(logfile,"better texts is [%d] [%s] \n",betterText,newText.c_str());

    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end learning by errors Textes mode\n\n");
}

void learningByErrorsWords_mode(weighMaster& personMaster){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in learning by errors WORDS mode\n");

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
    const std::string newText = constructBetterWords(personMaster.getNormalizedWeights(), buff);
    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end learning by errors WORDS mode\n\n");
}

void randomWords_mode(weighMaster& personMaster){
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
    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end random WORD mode\n\n");
}
void randomText_mode(weighMaster& personMaster){
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

    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end learning by errors Textes mode\n\n");
}
void randomLetters_mode(weighMaster& personMaster){
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
    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end random LETTERS mode\n\n");
}
void randomWord_mode(weighMaster& personMaster){
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
    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end random WORD mode\n\n");
}

void learningByErrorsOneWord_mode(weighMaster& personMaster){
  EXITCODE_TS code = EXITCODE_TS::ALL_GOOD;
  fprintf(logfile,"in learnign by errors WORD mode");

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
    const std::string bestWord = findBetterWord(personMaster.getNormalizedWeights(), buff);
    const std::string& realyBest = bestWord;
    const std::string newText = constructTextFromWord(realyBest);
    typingSample(newText,code,personMaster);
  }

  fprintf(logfile,"end learnign by errors WORD mode\n\n");
}
