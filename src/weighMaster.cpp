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

void weighMaster::normalize(){
  std::for_each(weights.begin(), weights.end(), [this](double& value){value/=this->width;});
}
void weighMaster::clear(){
  memset(weights.data(),0,weights.size());
  samplesAmount = 0;
}
