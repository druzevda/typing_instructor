#include "weighMaster.hxx"


weighMaster::weighMaster(const int width_)
  :width(width_)
{
  //2 letters in sample
  weights = std::vector<double>(width*width);
  //3 letters in sample

  //weight = std::vector<double>(width*width*width);
}
void weighMaster::makeSample(const char firstLetter, const char secondLetter){
  ++weights[width*firstLetter + secondLetter];
  ++samplesAmount;
}

std::vector<double> weighMaster::getNormalizedWeights()const{
  weighMaster resMaster = *(this);
  resMaster.normalize();
  const auto res = std::move(resMaster.weights);
  return res;
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
