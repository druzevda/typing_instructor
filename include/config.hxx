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
  "my_day.txt",
    "my_name_is_john.txt",
    "my_wonderful_family.txt"
};

std::string textsFolder{"./texts/"};

#endif // CONFIG_HXX_INCLUDED_______
