#include "../include/pencil.hpp"
#include <iostream>

Pencil::Pencil() {}

Pencil::~Pencil() {}

void Pencil::write(std::string& paper, const std::string& text) {
   paper += text;
}
