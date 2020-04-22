#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/pencil.hpp"

TEST_CASE("Pencil class tests") {
   Pencil pencil(100);
   Pencil pencil2(100);
   std::string paper("");
   std::string paper2("");

   SECTION("test Pencil::write method") {
      pencil.write(paper, "What hath God wrought?");
      REQUIRE( paper == "What hath God wrought?");
   }

   SECTION("example from documentation") {
      std::string myPaper("She sells sea shells");
      pencil.write(myPaper, " down by the sea shore");
      REQUIRE( myPaper == "She sells sea shells down by the sea shore");
   }

   SECTION("pencil writing can handle blank paper, text") {
      pencil.write(paper, "");
      REQUIRE( paper == "");
      pencil.write(paper, "lasagna");
      REQUIRE( paper == "lasagna");
      std::string uninit;
      pencil.write(paper, uninit);
      REQUIRE( paper == "lasagna");
      std::string uninit2;
      pencil.write(uninit2, "derp");
      REQUIRE(uninit2 == "derp");
   }

   SECTION("multiple pencils writing to multiple papers") {
      pencil.write(paper, "To be ");
      pencil.write(paper2, "Four score ");
      pencil2.write(paper, "or not to be? ");
      pencil2.write(paper2, "and seven ");
      pencil.write(paper, "That is the question.");
      pencil2.write(paper2, "years ago, our fathers...");
      REQUIRE(paper == "To be or not to be? That is the question.");
      REQUIRE(paper2 == "Four score and seven years ago, our fathers...");
   }

   Pencil tenDurPencil(10);

   SECTION("durability test with no upper case, whitespace") {
      tenDurPencil.write(paper, "abcdeabcdeabcde");
      REQUIRE( paper ==         "abcdeabcde     ");
   }

   SECTION("whitepsace does not change durability") {
      tenDurPencil.write(paper, "\n     abcde\n     abcdeabcde\n");
      REQUIRE( paper ==         "\n     abcde\n     abcde     \n");
   }

   SECTION("capital letters reduce durability by two") {
      tenDurPencil.write(paper, "ALPHA OMEGA");
      REQUIRE( paper ==         "ALPHA      ");
   }
}
