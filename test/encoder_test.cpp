#include <../3rd-party/catch.hpp>
#include "encoder.cpp"

TEST_CASE( "Translating seems to be working", "first" ) {
    Encoder* encoder = Encoder::getInstance();
    encoder->setPath("../test/resources/dictionary.json");
    CHECK_NOTHROW(encoder->validatePath());
    CHECK_NOTHROW(encoder->parseJson());
    REQUIRE( encoder->translateString(true, QString("ac")) == "#asdsomething" );
    REQUIRE( encoder->translateString(true, QString("aC")) == "#asdsomething" );
    REQUIRE( encoder->translateString(false, QString("gummybear@")) == "f$" );
    REQUIRE( encoder->translateString(false, QString("Gummybear@")) == "f$" );
}