#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/pencil.hpp"

TEST_CASE("Pencil class tests") {
   Pencil pencil(100, 100, 100);
   Pencil pencil2(100, 100, 100);
   Pencil tenDurPencil(10, 3, 100);
   Pencil shortEraser(100, 2, 3);
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
      Pencil pen(4, 10, 100);
      pen.write(paper, "text");
      REQUIRE(paper == "text");
      Pencil pen2(4, 10, 100);
      pen2.write(paper2, "Text");
      REQUIRE(paper2 ==  "Tex ");
   }

   SECTION("Durability is set to zero") {
      Pencil pen(0, 10, 100);
      pen.write(paper, "Bamboozle");
      REQUIRE(paper == "         ");
   }

   SECTION("Durability with non-alphabetic characters") {
      Pencil pen(29, 10, 100);
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
      Pencil pen(0, 10, 100);
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

   SECTION("sharpen fails after pencil length runs out") {
      tenDurPencil.write(paper, "12345");
      tenDurPencil.sharpen();
      tenDurPencil.write(paper, "1234567890");
      tenDurPencil.sharpen();
      tenDurPencil.sharpen();
      tenDurPencil.write(paper, "1234567890");
      tenDurPencil.sharpen(); //excess sharpen
      tenDurPencil.write(paper, "12345");
      REQUIRE(paper == "1234512345678901234567890     ");
   }

   SECTION("pencils with zero length") {
      Pencil shorty(10, 0, 100);
      shorty.write(paper, "Who lives in a pineapple");
      shorty.sharpen();
      shorty.write(paper, " under the sea?");
      REQUIRE(paper == "Who lives i                            ");
   }

   SECTION("pencil with zero length and zero durability") {
     Pencil zero(0, 0, 0);
     zero.write(paper, "ALAMO");
     zero.sharpen();
     zero.write(paper, " FORT");
     REQUIRE(paper == "          ");
   }

   SECTION("sharpen many times") {
      for (int k = 0; k < 1000000; k++) {
         tenDurPencil.sharpen();
      }
      tenDurPencil.write(paper, "kamiwaza wanda");
      REQUIRE( paper ==         "kamiwaza wa   ");
   }

   SECTION("erase method: example from documentation") {
      std::string p("How much wood would a woodchuck chuck if a woodchuck could chuck wood?");
      pencil.erase(p, "chuck");
      REQUIRE( p ==   "How much wood would a woodchuck chuck if a woodchuck could       wood?");
      pencil.erase(p, "chuck");
      REQUIRE( p ==   "How much wood would a woodchuck chuck if a wood      could       wood?");
   }

   SECTION("erase with various whitespace") {
      std::string p("LORD\tOF\nTHE MOUNTAIN");
      pencil.erase(p, "RD\tOF\nTHE ");
      REQUIRE(p ==  "LO  \t  \n    MOUNTAIN");
   }

   SECTION("erase when substring doesn't exist") {
      std::string p ("IT'S DANGEROUS TO GO ALONE TAKE THIS");
      pencil.erase(p, "cream");
      REQUIRE(p ==   "IT'S DANGEROUS TO GO ALONE TAKE THIS");
   }

   SECTION("erase when word is at beginning or end of paper") {
      std::string p ("alpha bravo charlieECHO");
      pencil.erase(p, "alph");
      REQUIRE( p ==  "    a bravo charlieECHO");
      pencil.erase(p, "eECHO");
      REQUIRE(p ==   "    a bravo charli     ");
   }

   SECTION("erase empty substring") {
      std::string p("zard");
      pencil.erase(p, "");
      REQUIRE(p ==  "zard");
   }

   SECTION("erase with close matches") {
      std::string p("ice iceb icebergceberg ceberg ICEBERG i ceberg grebeci ");
      pencil.erase(p, "iceberg");
      REQUIRE( p == "ice iceb        ceberg ceberg ICEBERG i ceberg grebeci ");
   }

   SECTION("eraser degradation: example from documentation") {
      std::string p("Buffalo Bill");
      shortEraser.erase(p, "Bill");
      REQUIRE (p == "Buffalo B   ");            
   }   

   SECTION("zero-length eraser") {
      Pencil pen(100, 10, 0);
      std::string p("E tu, Brute?");
      pen.erase(p, "Brute");
      REQUIRE(p == "E tu, Brute?");     
   }

   SECTION("Erasing entire string") {
      std::string p("I used to be an adventurer like you.");
      pencil.erase(p, "I used to be an adventurer like you.");
      REQUIRE( p ==        "                                    ");
   }

   SECTION("Incomplete erasure with similar words") {
      std::string p("snowball nowball owball wball");
      shortEraser.erase(p, "owbal");
      REQUIRE(p ==  "snowball nowball ow   l wball");
   }

   SECTION("Blanks don't wear down eraser") {
      std::string p("lemma pie");
      shortEraser.erase(p, "");
      REQUIRE(p ==  "lemma pie");
   }

   SECTION("Edit example from documentation") {
      std::string p("An       a day keeps the doctor away");
      pencil.edit(p, "onion" , 3);
      REQUIRE(p ==  "An onion a day keeps the doctor away");
   }

   SECTION("Editing collision: example from documentation") {
      std::string p("An       a day keeps the doctor away");
      pencil.edit(p, "artichoke" , 3);
      REQUIRE(p ==  "An artich@k@ay keeps the doctor away");
   }

   SECTION("Editing obeys durability rules") {
      std::string p("I        wha  is in a wonderball?");
      tenDurPencil.edit(p, "wonder WhyY", 2);
      REQUIRE( p == "I wonder @h@@ is in a wonderball?");
      tenDurPencil.edit(p, "absolutely", 12);
      REQUIRE( p == "I wonder @h@@ is in a wonderball?");
      tenDurPencil.sharpen();
      tenDurPencil.edit(p, "WONDER", 2);
      REQUIRE( p == "I @@@@@r @h@@ is in a wonderball?");
   }

   SECTION("Editting cannot change whitespace forms") {
      std::string p("I do\tnot\nlike that_Sam-I-Am");
      pencil.edit(p, "I\ndo not\nlike\nthat_Sam-I-Am");
      REQUIRE(p ==  "I do\tnot\nlike that_Sam-I-Am");
   }

   SECTION("Edit cannot erase characters") {
      std::string p("Please Please Me");
      pencil.edit(p, "lease  \n   ", 1);
      REQUIRE(p ==  "Please Please Me");
   }

   SECTION("Edit past the end of the existing text") {
      std::string p("Congratulations [    ]");
      pencil.edit(p, "NAME], You are today's winner!", p.length() - 5);
      REQUIRE(p ==  "Congratulations [NAME], You are today's winner!");
   }

   SECTION("Editing with blank texts") {
      std::string p("");
      pencil.edit(p, "elephant");
      REQUIRE(p ==   "elephant");
      pencil.edit(p, "", 4);
      REQUIRE(p ==   "elephant");
   }

}
