#ifndef CONFIG_HXX_INCLUDED_______
#define CONFIG_HXX_INCLUDED_______
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <curses.h>

extern const uint32_t maxTextFromWordsSize;
extern const uint32_t minWordSize_forOneWordText;
extern const uint32_t errorsInInitMaster;

extern const std::string textsFolder;
extern const std::string wordsFile;

extern const std::string letters;
extern const uint32_t lettersAmount;
extern const std::string symbols;
extern const uint32_t symbolsAmount;
extern std::unordered_map<char,double> symbolsMap;

extern const std::vector<std::string> menu_choices;
extern const std::vector<std::string> menu_descriptions;

extern FILE* logfile;

extern const std::vector<std::string> texts;

extern int Y_SIZE_SUBWINDOW;
extern int X_SIZE_SUBWINDOW;
extern int X_POINT_SUBWINDOW;
extern int Y_POINT_SUBWINDOW;

bool isAcceptWord(const std::string& word);
void initAll();

#endif // CONFIG_HXX_INCLUDED_______
