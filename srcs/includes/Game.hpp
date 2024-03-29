//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "../helpers/Glut.hpp"

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>

#include "../helpers/Displayable.hpp"
#include "../helpers/Movable.hpp"
#include "Boat.hpp"
#include "Waves.hpp"
#include "Entities.hpp"
#include "Config.hpp"

#define SPEED 3

class Game {

// TYPEDEFS
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;
  typedef std::map<std::string, Displayable::Ptr> EntityList;

public:
  static Game &getInstance() {
    static Game instance;
    return instance;
  }

  int start(int argc, char **argv);

  void draw();

  void keyboard(unsigned char key, int x, int y) const;

  const float getTime() const;

  const float &getDeltaTime() const;

  const float &getFrameRate() const;
  
  const EntityList &getEntities() const;

  Game(const Game &) = delete;

  Game &operator=(const Game &) = delete;

private:
  KeyboardMap _keyboardMap;
  EntityList _entities;
  float _time, _lastTime, _deltaTime = 0.0;
  float _lastFrameRateT, _frameRateInterval, _frameRate, _frames;

  void initDrawCallback() const;

  void initKeyboardCallback() const;

  void initKeyboardMap();

  void initGlut();

  void initEntities();

  void update();

  void updateTime();

  static void idleFunc();

  // Helpers

  void move(const std::string &entityName, Direction direction) {
    std::dynamic_pointer_cast<Movable>(_entities[entityName])->move(direction);
  }

  template<class T>
  void changeCannonPower(const std::string &entityName, float delta) {
    std::dynamic_pointer_cast<T>(_entities[entityName])->getCannon()->speed(delta);
  }

  template<class T>
  void changeCannonDirection(const std::string &entityName, float delta) {
    std::dynamic_pointer_cast<T>(_entities[entityName])->getCannon()->rotation(delta);
  }

  template<class T>
  void fire(const std::string &entityName) {
    std::shared_ptr<Entities<Projectile::Ptr>> p = std::dynamic_pointer_cast<Entities<Projectile::Ptr>>(_entities[entityName + "_projectiles"]);
    p->add(std::dynamic_pointer_cast<T>(_entities[entityName])->getCannon()->blast());
  }

  template<class T>
  void defend(const std::string &entityName) {
    std::shared_ptr<Entities<Pellet::Ptr>> p = std::dynamic_pointer_cast<Entities<Pellet::Ptr>>(_entities[PELLETS]);
    p->add(std::dynamic_pointer_cast<T>(_entities[entityName])->getCannon()->defend());
  }

  void toggleTangeants(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleTangeants();
  }

  void toggleNormals(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleNormals();
  }

  void toggleWireframe(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleWireframe();
  }

  void toggleAnimate(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleAnimate();
  }

  void doubleVertices(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->doubleVertices();
  }

  void halveSegments(const std::string &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->halveSegments();
  }

  // Singleton
  Game() : _frameRateInterval(0), _time(0), _lastTime(0), _lastFrameRateT(0), _frameRate(0), _frames(0) {}

  ~Game() = default;

  bool gameOver() const;
};

// Extern C
extern "C" {
static void drawCallback();
static void keyboardCallback(unsigned char key, int x, int y);
}