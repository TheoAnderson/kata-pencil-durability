#include "../include/pencil.hpp"

#include <iostream>
#include <cctype>

Pencil::Pencil(unsigned int pencilDurability) {
   this->initialDurability = this->durability = pencilDurability;
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
         if (text[k] >= 'A' and text[k] <= 'Z') {
            if (this->durability  > 0) {
               this->durability--; //second decrement;
            }
            else {
               newText[k] = Pencil::ILLEGIBLE;
            }
         }
      }
      else {
         newText[k] = ' ';
      }
   }
   paper += newText;
}

void Pencil::sharpen() {
   this->durability = this->initialDurability;
}
