#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "bugless" ){
  {
    std::istringstream iss( "21 -22" );
    long lineNumber = 1;
    MODER moder( iss, lineNumber );
    REQUIRE( moder.card1.nin.value == 21 );
    REQUIRE( moder.card1.nout.value == -22 );
    REQUIRE( not moder.card2 );
    REQUIRE( not moder.card3List );
  }{
    std::istringstream iss(
      "1 -22 \n"
      "'my simple pendf tape'\n"
      "21 125\n"
      "0/"
      );
    long lineNumber = 1;
    MODER moder( iss, lineNumber );
    REQUIRE( moder.card1.nin.value == 1 );
    REQUIRE( moder.card1.nout.value == -22 );
    REQUIRE( moder.card2 );
    REQUIRE( moder.card2->tapeid.value == "my simple pendf tape" );
    REQUIRE( moder.card3List );
    REQUIRE( moder.card3List->size() == 1 );
    REQUIRE( moder.card3List->front().nin.value == 21 );
    REQUIRE( moder.card3List->front().matd.value == 125 );
  }
}

SCENARIO( "bugged" ){
  {
    std::istringstream iss( "21 -21" );
    long lineNumber = 1;
    REQUIRE_THROWS( MODER( iss, lineNumber ) );
  }{
    std::istringstream iss(
      "1 -22 \n"
      "'my simple pendf tape'\n"
      "0 /"
      );
    long lineNumber = 1;
    REQUIRE_THROWS( MODER( iss, lineNumber ) );
  }
}