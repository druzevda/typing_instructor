#ifndef WEIGH_MASTER_INCLUDED_HXX
#define WEIGH_MASTER_INCLUDED_HXX
#include <cstring>
#include <vector>
#include <cstdint>
class weighMaster{

  std::vector<double> weights{};
  uint32_t samplesAmount = 0;

  int width = 0;

  public:
  weighMaster(const int width_);

  void makeSample(const char firstLetter, const char secondLetter);

  void normalize();

  const std::vector<double>& getWeights()const{
    return weights;
  }

  void clear();

  int getWidth()const{
    return width;
  }
};
#endif //  WEIGHT_MASTER_INCLUDED_HXX
