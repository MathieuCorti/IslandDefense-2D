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
  Direction _direction;
  float _speed;

public:
  Movable(float _speed, float x, float y) : Displayable(x, y), _speed(_speed) {}

  Movable(float _speed) : _speed(_speed) {}

  void move(Direction direction) {
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

  Direction getDirection() const {
    return _direction;
  }

  void setDirection(Direction direction) {
    Movable::_direction = direction;
  }

  float getSpeed() const {
    return _speed;
  }

  void setSpeed(int speed) {
    Movable::_speed = speed;
  }
};

