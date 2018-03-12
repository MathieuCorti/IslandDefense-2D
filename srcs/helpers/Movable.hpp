//
//  Movable.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

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
  void move(Direction direction);
  void move(double x, double y, double z);
};

