#ifndef CONFIG_HXX_INCLUDED_______
#define CONFIG_HXX_INCLUDED_______

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <curses.h>

const extern std::string symbols{" abcdefghijklmnopqrstuvwxyz!?\"$\'1234568790"};
const extern uint32_t symbolsAmount = symbols.size();

const extern std::string letters{" abcdefghijklmnopqrstuvwxyz"};
const extern uint32_t lettersAmount = letters.size();

std::unordered_map<char,double> symbolsMap{ };

const extern std::vector<std::string> texts{
  "a_great_summer_vacation.txt",
    "at_school.txt",
    "day_of_the_week.txt",
    "my_day.txt",
    "my_family_at_home.txt",
    "my_name_is_john.txt",
    "my_wonderful_family.txt",
    "numbers.txt",
    "our_vacation.txt",
    "preparing_food.txt",
    "the_city_where_i_live.txt",
    "the_house.txt",
    "the_pet_store.txt"
};
enum class KEYS{
  CTRL_X = 24,
  CTRL_N = 14,
  CTRL_D = 4,
  CTRL_J = 10,
  CTRL_K = 11,
};

constexpr double X_SIZE_SUBWINDOW_MULT  = 3.0 / 5.0;
constexpr double Y_SIZE_SUBWINDOW_MULT  = 3.0 / 5.0;
constexpr double X_POINT_SUBWINDOW_MULT = 1.0 / 5.0;
constexpr double Y_POINT_SUBWINDOW_MULT = 1.0 / 5.0;

int X_POINT_SUBWINDOW =0;
int Y_POINT_SUBWINDOW =0;
int X_SIZE_SUBWINDOW  =0;
int Y_SIZE_SUBWINDOW  =0;

const extern std::string textsFolder{"./texts/"};
const extern std::string wordsFile{"words.txt"};

FILE* logfile = nullptr;

void initAll(){
  for(int i = 0; i < symbolsAmount; ++i){
    symbolsMap.insert({symbols[i],i});
  }

  initscr();

  noecho();
  cbreak();
  curs_set(0);

  X_POINT_SUBWINDOW = X_POINT_SUBWINDOW_MULT * COLS ;
  Y_POINT_SUBWINDOW = Y_POINT_SUBWINDOW_MULT * LINES;
  X_SIZE_SUBWINDOW  = X_SIZE_SUBWINDOW_MULT  * COLS ;
  Y_SIZE_SUBWINDOW  = Y_SIZE_SUBWINDOW_MULT  * LINES;

  logfile = fopen("logfile","a");
  if (logfile == nullptr){
    std::cerr << "errror of opening file" << std::endl;
    endwin();
    exit(1);
  }else{
    std::fprintf(logfile,"START TYPING INSTRUCTOR");
  }
}

const extern std::vector<std::string> menu_choices{
  "0 TEXT ",
  "1 TEXT ",
  "2 WORDS ",
  "3 WORDS ",
  "4 WORD ",
  "5 WORD ",
  "6 LETTERS "
};

extern constexpr uint32_t maxTextFromWordsSize = 100;
extern constexpr uint32_t minWordSize_forOneWordText = 4;

const extern std::vector<std::string> menu_descriptions{
  "(autochoice texts, focus on your weak points)",
  "(autochoice texts, random choice)",
  "(autochoice some words, focus on your weak points, " + std::to_string(maxTextFromWordsSize) + "+ symbols)",
  "(autochoice some words, random choice, " + std::to_string(maxTextFromWordsSize) + "+ symbols)",
  "(one word, n times, focus on your weak points, "+ std::to_string(maxTextFromWordsSize) +  "+ symbols )",
  "(one word, n times, random choice, "+ std::to_string(maxTextFromWordsSize) +  "+ symbols )",
  "(random letters, "+ std::to_string(maxTextFromWordsSize) +  " symbols )"
};

#endif // CONFIG_HXX_INCLUDED_______
