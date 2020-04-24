#include "../include/pencil.hpp"

#include <iostream>
#include <cctype>

Pencil::Pencil(unsigned int pencilDurability, unsigned int pencilLength, unsigned int eraserDurability) {
   this->initialDurability = this->durability = pencilDurability;
   this->length = pencilLength;
   this->eraserLength = eraserDurability;
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
   if (this->length == 0) {
      return;
   }
   this->length--;
   this->durability = this->initialDurability;
}

void Pencil::erase(std::string& paper, const std::string& text) {
   if (text.length() > paper.length()) {
      return;
   }
   for (int i = paper.size() - text.size(); i >= 0; i--) {
      if (text == paper.substr(i, text.length())) {
         for (int j = text.length() - 1; j >= 0; j--) {
            if (isspace(paper[i + j])) {
               continue;
            }
            if (this->eraserLength == 0) {
               return;
            }
            this->eraserLength--;
            paper[i + j] = ' ';
         }
         break;
      }
   }
}

void Pencil::edit(std::string& paper, const std::string& text, unsigned int startPosition) {
   for (int i = 0; i < text.length() and startPosition + i < paper.length(); i++) {
      if (isspace(text[i]) or paper[startPosition + i] == text[i]) {
         continue;
      }
      paper[startPosition + i] = text[i];
   }
}
