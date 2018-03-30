//
//  UI.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#include <utility>

#include <iostream>
#include "includes/UI.hpp"

bool UI::update() {
  return false;
}

void UI::draw() const {
  for (int i = 0; i < _entities.size(); ++i) {
    glBegin(GL_POLYGON);
    glColor4f(_entities[i]->color.r, _entities[i]->color.g, _entities[i]->color.b, _entities[i]->color.a);
    float delta = i / 10.0f == 0 ? 0 : i / 10.0f;
    double barLength = -1 * (0.4 + 5 * ((100 - _entities[i]->getPercentHealthLeft()) / 1000));
    glVertex2d(-0.94, 0.9 - delta);
    glVertex2d(-0.94, 0.84 - delta);
    glVertex2d(barLength, 0.84 - delta);
    glVertex2d(barLength, 0.9 - delta);
    glEnd();
  }
}

UI::UI(std::vector<Alive::Ptr> entities, const Color &color) : Displayable(color), _entities(std::move(entities)) {}
