//
//  UI.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#include "includes/UI.hpp"

bool UI::update() {
  return false;
}

void UI::draw() const {
  glBegin(GL_POLYGON);
  for (int i = 0; i < _entities.size(); ++i) {
    glColor4f(_entities[i]->color.r, _entities[i]->color.g, _entities[i]->color.b, _entities[i]->color.a);
    float delta = i / 10 == 0 ? 0 : i / 10;
    glVertex2d(-0.94, 0.9 - delta);
    glVertex2d(-0.94, 0.84 - delta);
    glVertex2d(-0.4, 0.84 - delta);
    glVertex2d(-0.4, 0.9 - delta);
  }
  glEnd();
}

UI::UI(std::vector<Alive::Ptr> entities, const Color &color) : Displayable(color), _entities(entities) {}
