//
// Created by wilmot_g on 30/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../includes/Projectile.hpp"

class Projectiles : public Displayable {
public:
  //Typedef
  typedef std::shared_ptr<Projectiles> Ptr;

  explicit Projectiles(const Color &color = Color(1, 1, 1));

  void add(const Projectile::Ptr &projectile);

  void draw() const override;

  bool update() override;

private:
  Color _color;
  std::vector<Projectile::Ptr> _projectiles;
};
