#ifndef KATAPENCILDURABILITY_PENCIL_HPP
#define KATAPENCILDURABILITY_PENCIL_HPP

#include <string>

class Pencil {
   public:
      Pencil(unsigned int pencilDurability, unsigned int pencilLength, unsigned int eraserDurability);
      ~Pencil();
      
      //write text to the end of paper
      void write(std::string& paper, const std::string& text);

      //restore the durability of the pencil
      void sharpen();

      //erase last example of text from paper
      void erase(std::string& paper, const std::string& text);

      //write text on paper, starting at char at startPosition
      //chars from text will only replace whitespace on paper. Other characters become ILLEGIBLE
      void edit(std::string& paper, const std::string& text, unsigned int startPosition = 0);

      const static char ILLEGIBLE = '@';

   private:
      unsigned int durability;
      unsigned int initialDurability;
      unsigned int length;
      unsigned int eraserLength;
};
#endif
