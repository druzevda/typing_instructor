#include "weighMaster.hxx"
#include <map>
#include <random>
#include "config.hxx"

void weighMaster::print()const{
  std::fprintf(logfile,"weighMaster:{\n");
  std::multimap<double,int,std::greater<double>> map;
  for(uint32_t i = 0; i < weights.size(); ++i){
    map.insert({weights[i],i});
  }
  for(const auto& [weigh,i] : map){
    const int prevIndexOfSymbol = i / symbolsAmount;
    const int nowIndexOfSymbol =  i % symbolsAmount;

    const char prevChar = symbols[prevIndexOfSymbol];
    const char nowChar = symbols[nowIndexOfSymbol];

    std::fprintf(logfile,"\tsymb:[%c][%c] idx:[%d][%d] weigh:[%lf]\n",prevChar,nowChar,prevIndexOfSymbol,nowIndexOfSymbol,weigh);
    if(weigh > 0){
    }else{
      break;
    }
  }
  std::fprintf(logfile,"}\n");
  std::fflush(logfile);
}
weighMaster::weighMaster(const int width_)
  :width(width_)
{
  //2 letters in sample
  weights = std::vector<double>(width*width);
  //3 letters in sample

  //weight = std::vector<double>(width*width*width);
}
void weighMaster::makeSample(const int firstLetter, const int secondLetter){
  ++weights[width*firstLetter + secondLetter];
  ++samplesAmount;
}

std::vector<double> weighMaster::getNormalizedWeights()const{
  weighMaster resMaster = *(this);
  resMaster.normalize();
  const auto res = std::move(resMaster.weights);
  return res;
}

void weighMaster::randomize(){
  std::mt19937 mersenne(std::random_device{}());
  std::uniform_int_distribution<> unif(0,lettersAmount);

  this->clear();

  for(int i = 0; i < errorsInInitMaster; ++i){
    const auto prevpos = unif(mersenne);
    const auto nowpos = unif(mersenne);
    this->makeSample(prevpos,nowpos);
  }
}
void weighMaster::normalize(){
  const uint32_t normCoeff = (this->getSamplesAmount()==0?1:this->getSamplesAmount());
  if(normCoeff == 1)
    return;

  std::for_each(weights.begin(), weights.end(),
      [normCoeff](double& value){
        value/=normCoeff;
      }
  );
}
void weighMaster::clear(){
  std::for_each(weights.begin(),weights.end(),[](auto& elem){elem = 0.0;});
  samplesAmount = 0;
}
