//
//  Movable.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "Entity.hpp"

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Movable: public Entity {
protected:
  Direction direction;
  int speed;

public:
  void move(Direction direction) {
    switch(direction) {
      case UP:
        setY(getY() + getSpeed());
        break;
      case DOWN:
        setY(getY() - getSpeed());
        break;
      case LEFT:
        setX(getX() + getSpeed());
        break;
      case RIGHT:
        setX(getX() - getSpeed());
        break;
    }
  }

  void moveTo(double x, double y) {
    setX(x);
    setY(y);
  }

  Direction getDirection() const {
    return direction;
  }

  void setDirection(Direction direction) {
    Movable::direction = direction;
  }

  int getSpeed() const {
    return speed;
  }

  void setSpeed(int speed) {
    Movable::speed = speed;
  }
};

