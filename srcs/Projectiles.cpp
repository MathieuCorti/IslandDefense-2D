//
// Created by wilmot_g on 30/03/18.
//

#include "includes/Projectiles.hpp"

Projectiles::Projectiles(const Color &color) : Displayable(color) {}

void Projectiles::draw() const {
    for (const Projectile::Ptr &p : _projectiles) {
      p->draw();
    }
}

void Projectiles::add(const Projectile::Ptr &projectile) {
  if (projectile) {
    _projectiles.push_back(projectile);
  }
}

bool Projectiles::update() {
  for (auto it = _projectiles.begin(); it != _projectiles.end();) {
    if (it->get()->update()) {
      it = _projectiles.erase(it++);
    } else {
      ++it;
    }
  }
  return false;
}
