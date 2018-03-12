//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

class Entity {
protected:
  double _x;
  double _y;
  double _z;

public:

  Entity() : _x(0), _y(0), _z(0) {}

  double getX() const {
    return _x;
  }

  void setX(double x) {
    Entity::_x = x;
  }

  double getY() const {
    return _y;
  }

  void setY(double y) {
    Entity::_y = y;
  }

  double getZ() const {
    return _z;
  }

  void setZ(double z) {
    Entity::_z = z;
  }
};