//
//  Alive.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#pragma once

class Alive : public Displayable {
  
protected:
  const int totalHealth;
  int currentHealth;

public:
  
  typedef std::shared_ptr<Alive> Ptr;

  Alive(int health, Color color) : Displayable(color), currentHealth(health), totalHealth(health) {}

  void draw() { }

  bool update() { return false; };
  
  void takeDamage(int amount) {
    const int newHealth = getHealth() - amount;
    currentHealth = newHealth < 0 ? 0 : newHealth;
  }

  int getHealth() {
    return currentHealth;
  }

};