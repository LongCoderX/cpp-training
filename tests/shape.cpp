#include <iostream>
#include "shape.h"

shape::~shape() {
    std::cout << "shape destructor called" << std::endl;
}  

circle::circle(double r) : radius_(r) {}
circle::~circle() {
    std::cout << "circle destructor called." << std::endl;
}

triangle::triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}
triangle::~triangle() { 
    std::cout << "triangle destructor called." << std::endl;
}

shape *create_shape(shape_type type) {
  switch (type) {
  case shape_type::circle:
    return new circle(2.0);
  case shape_type::triangle:
    return new triangle(1.0, 2.0, 3.0);
  }
}
