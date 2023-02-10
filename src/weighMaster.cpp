#include "weighMaster.hxx"
#include <random>
#include "config.hxx"

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
  std::binomial_distribution<> d(1, double(errorsInInitMaster)/(lettersAmount*lettersAmount));
  this->clear();
  for(auto& elem : weights){
    if(d(mersenne)){
      ++elem;
      ++samplesAmount;
    }
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
  memset(weights.data(),0,weights.size());
  samplesAmount = 0;
}
