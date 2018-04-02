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

class Movable : public Displayable {
protected:
  float _speed;

public:
  Movable(float _speed, float x, float y) : Displayable(x, y), _speed(_speed) {}

  explicit Movable(float _speed) : _speed(_speed) {}

  virtual void move(Direction direction) {
    switch (direction) {
      case UP:
        setY(getY() + getSpeed());
        break;
      case DOWN:
        setY(getY() - getSpeed());
        break;
      case LEFT:
        setX(getX() - getSpeed());
        break;
      case RIGHT:
        setX(getX() + getSpeed());
        break;
    }
  }

  void moveTo(float x, float y) {
    setX(x);
    setY(y);
  }

  float getSpeed() const {
    return _speed;
  }

  void setSpeed(int speed) {
    Movable::_speed = speed;
  }
};

