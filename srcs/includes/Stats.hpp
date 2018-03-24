//
// Created by wilmot_g on 23/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Stats : public Displayable {
private:

public:
  bool update() override { return false; }

  void draw() const override;
};