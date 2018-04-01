//
// Created by wilmot_g on 30/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../includes/Pellet.hpp"

template <class T>
class Entities : public Displayable {
public:
  //Typedef
  typedef std::shared_ptr<T> Ptr;

  explicit Entities(const Color &color = Color(1, 1, 1)) : _color(color) {}

  void draw() const {
    for (auto &e : _entities) {
      e->draw();
    }
  }

  void add(const T &entity) {
    if (entity) {
      _entities.push_back(entity);
    }
  }

  bool update() {
    for (auto it = _entities.begin(); it != _entities.end();) {
      if (it->get()->update()) {
        it = _entities.erase(it++);
      } else {
        ++it;
      }
    }
    return false;
  }

private:
  Color _color;
  std::vector<T> _entities;
};
