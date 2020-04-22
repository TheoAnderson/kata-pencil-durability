#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/pencil.hpp"

TEST_CASE("Pencil class tests") {
   Pencil pencil;
   std::string paper("");

   SECTION("test Pencil::write method") {
      pencil.write(paper, "What hath God wrought?");
      REQUIRE( paper == "What hath God wrought?");
   }
}
