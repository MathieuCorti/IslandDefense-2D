//
//  Alive.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#pragma once

#include "Shape.hpp"
#include "Movable.hpp"

class Alive {
  
protected:
  const int totalHealth;
  int currentHealth;

public:

  Alive(int health) : currentHealth(health), totalHealth(health) {}

  void draw() { }

  bool update() { return false; };
  
  void takeDamage(int amount) {
    const int newHealth = getCurrentHealth() - amount;
    currentHealth = newHealth < 0 ? 0 : newHealth;
  }

  int getCurrentHealth() {
    return currentHealth;
  }
  
  int getTotalHealth() {
    return totalHealth;
  }
  
  float getPercentHealthLeft() {
    return static_cast<float>(getCurrentHealth()) / static_cast<float>(getTotalHealth()) * 100.0f;
  }

};

typedef std::shared_ptr<Alive> AlivePtr;