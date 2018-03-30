//
//  UI.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#pragma once


#include "../helpers/Displayable.hpp"
#include "../helpers/DisplayableShape.hpp"
#include "../helpers/Alive.hpp"

class UI : public Displayable {

private:
  std::vector<Alive::Ptr> _entities;
  
public:
  UI(std::vector<Alive::Ptr> entities, const Color &color = Color(0, 0, 0));

  bool update() override;

  void draw() const override;

};

