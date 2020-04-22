#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/pencil.hpp"

TEST_CASE("Pencil class tests") {
   Pencil pencil(100);
   Pencil pencil2(100);
   Pencil tenDurPencil(10);
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

   SECTION("write capital when durabillity is one") {
      tenDurPencil.write(paper, "ABCDeF");
      REQUIRE( paper ==         "ABCDe@");
   }

   SECTION("Durability examples from documentation") {
      Pencil pen(4);
      pen.write(paper, "text");
      REQUIRE(paper == "text");
      Pencil pen2(4);
      pen2.write(paper2, "Text");
      REQUIRE(paper2 ==  "Tex ");
   }

   SECTION("Durability is set to zero") {
      Pencil pen(0);
      pen.write(paper, "Bamboozle");
      REQUIRE(paper == "         ");
   }

   SECTION("Durability with non-alphabetic characters") {
      Pencil pen(29);
      pen.write(paper, "1234567890()[]<>?~!@#$%^&*|\"-ABCDE");
      REQUIRE(paper == "1234567890()[]<>?~!@#$%^&*|\"-     ");

   }

   SECTION("Restore durability with sharpen") {
      tenDurPencil.write(paper, "ABCDEF");
      tenDurPencil.sharpen();
      tenDurPencil.write(paper, "0123456789sandwich");
      REQUIRE(paper == "ABCDE 0123456789        ");
   }

   SECTION("sharpen pencil with zero durability") {
      Pencil pen(0);
      pen.sharpen();
      pen.write(paper, "rock and");
      pen.sharpen();
      pen.write(paper, " roll");
      REQUIRE(paper == "             ");
   }

   SECTION("durability and sharpen rules persist between paper") {
      tenDurPencil.write(paper, "abcde");
      tenDurPencil.sharpen();
      tenDurPencil.write(paper2, "It's dangerous");
      tenDurPencil.write(paper, " to go alone.");
      REQUIRE( paper2 ==         "It's dange    ");
      REQUIRE( paper == "abcde             ");
   }
}
