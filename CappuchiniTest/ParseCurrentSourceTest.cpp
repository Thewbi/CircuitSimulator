#include "pch.h"

#include "../Cappuchini/CircuitDescriptionParser.h"

// For this test to work, follow https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/test/unit-testing-existing-cpp-applications-with-test-explorer?view=vs-2015#objectRef
// If you want to test the class CircuitDescriptionParser, you have to add CircuitDescriptionParser.obj to 
// Linker > Input > AdditionalInput in the test project! Otherwise you get unresolved external symbols.

TEST(ParseCurrentSourceTest, ParseCurrentSource) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/currentsource.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 2);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).id, "I1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).type, "I");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeA, "4");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeB, "8");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).value, 0.001);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).scaleFactor, 1);
}

TEST(ParseCurrentSourceTest, ParseCurrentSourceWithGroup) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/currentsource.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 2);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).id, "I1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).type, "I");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeA, "4");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeB, "8");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).value, 0.001);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).group, "GROUP1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).scaleFactor, 1);
}