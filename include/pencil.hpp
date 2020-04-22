#ifndef KATAPENCILDURABILITY_PENCIL_HPP
#define KATAPENCILDURABILITY_PENCIL_HPP

#include <string>

class Pencil {
   public:
      Pencil(unsigned int pencilDurability);
      ~Pencil();
      
      //write text to the end of paper
      void write(std::string& paper, const std::string& text);

   private:
      unsigned int durability;
};
#endif
