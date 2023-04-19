#ifndef WaterLevelSensor_h
#define WaterLevelSensor_h

#include <Arduino.h>

class WaterLevelSensor {
  public:
    WaterLevelSensor(int analogPin);
    void begin();
    void update();
    bool isError();
    float getCurrentLevel();
    
  private:
    int _analogPin;
    int _sensorValue;
    bool _error;
    float _currentLevel;
};

#endif
