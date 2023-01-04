#ifndef CONFIG_HXX_INCLUDED_______
#define CONFIG_HXX_INCLUDED_______

#include <string>
#include <vector>
#include <unordered_map>
#include <curses.h>

constexpr uint32_t lettersAmount = 43;
constexpr char letters[lettersAmount]={" abcdefghijklmnopqrstuvwxyz!?\"$\'1234568790"};
std::unordered_map<char,double> lettersMap{ };

enum class trainingMode{
  FIX_WEAK_POINTS,
  CHECK_WEAK_POINTS,
};

const std::vector<std::string> texts{
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

const std::string textsFolder{"./texts/"};
const std::string wordsFile{"words.txt"};

void initAll(){

  for(int i = 0; i < lettersAmount; ++i){
    lettersMap.insert({letters[i],i});
  }

  initscr();

  noecho();
  cbreak();
  curs_set(0);

  X_POINT_SUBWINDOW = X_POINT_SUBWINDOW_MULT * COLS ;
  Y_POINT_SUBWINDOW = Y_POINT_SUBWINDOW_MULT * LINES;
  X_SIZE_SUBWINDOW  = X_SIZE_SUBWINDOW_MULT  * COLS ;
  Y_SIZE_SUBWINDOW  = Y_SIZE_SUBWINDOW_MULT  * LINES;
}

const std::vector<std::string> menu_choices{
  "0 TEXT",
  "1 WORDS",
  "2 WORD",
  "3 WORD",
};

constexpr uint32_t maxTextFromWordsSize = 100;

const std::vector<std::string> menu_descriptions{
  "(autochoice texts, focus on your weak points)",
  "(autochoice some words, focus on your weak points, " + std::to_string(maxTextFromWordsSize) + "+ letters)",
  "(one word, n times, focus on your weak points, "+ std::to_string(maxTextFromWordsSize) +  "+ letters )",
  "(one word, n times, random choice, "+ std::to_string(maxTextFromWordsSize) +  "+ letters )"
};

#endif // CONFIG_HXX_INCLUDED_______
