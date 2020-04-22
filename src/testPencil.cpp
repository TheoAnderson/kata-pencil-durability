#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/pencil.hpp"

TEST_CASE("hello world") {
   REQUIRE( helloWorld() == 7 ); 
}
