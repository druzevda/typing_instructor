#ifndef CONFIG_HXX_INCLUDED_______
#define CONFIG_HXX_INCLUDED_______

#include <string>
#include <vector>
#include <unordered_map>

constexpr uint32_t lettersAmount = 43;
constexpr char letters[43]={" abcdefghijklmnopqrstuvwxyz!?\"$\'1234568790"};
std::unordered_map<char,double> lettersMap{ };

enum class trainingMode{
  FIX_WEAK_POINTS,
  CHECK_WEAK_POINTS,
};

std::vector<std::string> texts{
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

int X_SIZE_WINDOW=0;
int Y_SIZE_WINDOW=0;

std::string textsFolder{"./texts/"};

#endif // CONFIG_HXX_INCLUDED_______
