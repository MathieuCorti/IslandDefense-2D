//
//  Color.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

struct Color {
  float r;
  float g;
  float b;
  float a;

  Color(int r, int g, int b, int a = 1) : r(r / 255), g(g / 255), b(b / 255), a(a) {}

  void setColor(int r, int g, int b, int a = 1) {
    this->r = r / 255;
    this->g = g / 255;
    this->b = b / 255;
    this->a = a;
  }
};