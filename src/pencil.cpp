#include "../include/pencil.hpp"

#include <iostream>
#include <cctype>

Pencil::Pencil(unsigned int pencilDurability) {
   this->durability = pencilDurability;
}

Pencil::~Pencil() {}

void Pencil::write(std::string& paper, const std::string& text) {
   std::string newText(text);
   for (unsigned int k = 0; k < text.size(); k++) {
      if (isspace(text[k])) {
         continue;
      }
      if (this->durability > 0) {
         this->durability--;
      }
      else {
         newText[k] = ' ';
      }
   }
   paper += newText;
}
