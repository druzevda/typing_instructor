#ifndef MODES_HXX_INCLUDED_________________
#define MODES_HXX_INCLUDED_________________
#include "weighMaster.hxx"
void learningByErrorsTextes_mode (weighMaster& personMaster);
void randomText_mode             (weighMaster& personMaster);

void learningByErrorsWords_mode  (weighMaster& personMaster);
void randomWords_mode            (weighMaster& personMaster);

void learningByErrorsOneWord_mode(weighMaster& personMaster);
void randomWord_mode             (weighMaster& personMaster);

void randomLetters_mode          (weighMaster& personMaster);
#endif //  MODES_HXX_INCLUDED_________________
