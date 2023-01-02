#ifndef CONFIG_HXX_INCLUDED_______
#define CONFIG_HXX_INCLUDED_______

#include <string>
#include <vector>
#include <unordered_map>
#include <curses.h>

constexpr uint32_t lettersAmount = 43;
constexpr char letters[43]={" abcdefghijklmnopqrstuvwxyz!?\"$\'1234568790"};
std::unordered_map<char,double> lettersMap{ };

enum class trainingMode{
  FIX_WEAK_POINTS,
  CHECK_WEAK_POINTS,
};


const std::vector<std::string> words{
  "simpleWords_0.txt",
    "simpleWords_1.txt",
    "simpleWords_2.txt",
    "simpleWords_3.txt",
    "simpleWords_4.txt",
    "simpleWords_5.txt",
    "simpleWords_6.txt",
    "simpleWords_7.txt",
    "simpleWords_8.txt",
    "simpleWords_9.txt"
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

constexpr double X_SIZE_SUBWINDOW_MULT  = 2.0 / 5.0;
constexpr double Y_SIZE_SUBWINDOW_MULT  = 2.0 / 5.0;
constexpr double X_POINT_SUBWINDOW_MULT = 1.0 / 5.0;
constexpr double Y_POINT_SUBWINDOW_MULT = 1.0 / 5.0;

int X_POINT_SUBWINDOW =0;
int Y_POINT_SUBWINDOW =0;
int X_SIZE_SUBWINDOW  =0;
int Y_SIZE_SUBWINDOW  =0;

const std::string textsFolder{"./texts/"};

void initsizes(){
  X_POINT_SUBWINDOW = X_POINT_SUBWINDOW_MULT * COLS ;
  Y_POINT_SUBWINDOW = Y_POINT_SUBWINDOW_MULT * LINES;
  X_SIZE_SUBWINDOW  = X_SIZE_SUBWINDOW_MULT  * COLS ;
  Y_SIZE_SUBWINDOW  = Y_SIZE_SUBWINDOW_MULT  * LINES;
}

const std::vector<std::string> menu_choices{
  "random texts",
  "simple words",
};
#endif // CONFIG_HXX_INCLUDED_______
