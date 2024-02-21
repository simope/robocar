// robocar.h

#ifndef ROBOCAR_H
#define ROBOCAR_H

class Car {
  public:
    Car(int ENp, int FW1p, int BW1p, int FW2p, int BW2p);
    void moveFW();
    void moveBW();
    void moveL();
    void moveR();
    void stop();
    int getSpeed();
    void accelerate();
    void decelerate();

  private:
    int EN;
    int FW1;
    int FW2;
    int BW1;
    int BW2;
    int speed;
  };

#endif
