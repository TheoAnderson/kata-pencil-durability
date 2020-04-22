#include "../include/pencil.hpp"
#include <iostream>

Pencil::Pencil(unsigned int pencilDurability) {
   this->durability = pencilDurability;
}

Pencil::~Pencil() {}

void Pencil::write(std::string& paper, const std::string& text) {
   paper += text;
}
