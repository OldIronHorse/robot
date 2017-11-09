#ifndef VL53L0X_H
#define VL53L0X_H

class VL53L0X{
  public:
    uint16_t readRangeContinuousMillimeters(void){
      return _distance_mm;
    }
    uint16_t readRangeSingleMillimeters(void){
      return _distance_mm;
    }

    uint16_t _distance_mm;
};

#endif // VL53L0X_H
