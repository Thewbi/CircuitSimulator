#include "pch.h"

#include "../Cappuchini/CircuitDescriptionParser.h"

// For this test to work, follow https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/test/unit-testing-existing-cpp-applications-with-test-explorer?view=vs-2015#objectRef
// If you want to test the class CircuitDescriptionParser, you have to add CircuitDescriptionParser.obj to 
// Linker > Input > AdditionalInput in the test project! Otherwise you get unresolved external symbols.

TEST(ParseDiodeTest, ParseDiode) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/diode.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 2);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).id, "D1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).type, "D");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeA, "10");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeB, "20");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).scaleFactor, 1);
}

TEST(ParseDiodeTest, ParseDiodeWithScaleFactor) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/diode.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 2);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).id, "D1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).type, "D");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeA, "10");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeB, "20");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).scaleFactor, 17.3);
}