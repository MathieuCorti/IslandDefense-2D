//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

class Entity {
protected:
  double x;
  double y;
  double z;

public:
  double getX() const {
    return x;
  }

  void setX(double x) {
    Entity::x = x;
  }

  double getY() const {
    return y;
  }

  void setY(double y) {
    Entity::y = y;
  }

  double getZ() const {
    return z;
  }

  void setZ(double z) {
    Entity::z = z;
  }
};