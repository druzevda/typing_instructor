#ifndef CONSTRUCT_FUNCTIONS_INCLUDED_HXX_______
#define CONSTRUCT_FUNCTIONS_INCLUDED_HXX_______

#include <vector>
#include <string>

std::string scanTextToString(const std::string& currentTextName);
std::vector<std::string> scanWordsToString(const std::string& currentTextName);

int findBetterText(const std::vector<double>& userWeighs, const std::vector<std::string>& texts);
std::string findBetterWord(const std::vector<double>& userWeighs, const std::vector<std::string>& words);

std::string constructBetterWords(const std::vector<double>& userWeighs, const std::vector<std::string>& words);
std::string constructTextFromWords(const std::vector<std::string>& buff);
std::string constructTextFromWord(const std::string& word);
std::string constructRandomLettersText();

#endif // CONSTRUCT_FUNCTIONS_INCLUDED_HXX_______

