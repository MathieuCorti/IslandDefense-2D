//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

class Entity {
protected:
  float _x;
  float _y;
  float _z;

public:

  Entity() : _x(0), _y(0), _z(0) {}

  Entity(float x, float y, float z) : _x(x), _y(y), _z(z) {}

  float getX() const {
    return _x;
  }

  void setX(float x) {
    Entity::_x = x;
  }

  float getY() const {
    return _y;
  }

  void setY(float y) {
    Entity::_y = y;
  }

  float getZ() const {
    return _z;
  }

  void setZ(float z) {
    Entity::_z = z;
  }
};